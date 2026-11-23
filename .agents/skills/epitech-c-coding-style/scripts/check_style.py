#!/usr/bin/env python3
"""Check first-party C files using physical source and Clang's JSON AST."""

import argparse
from bisect import bisect_right
from dataclasses import asdict, dataclass
import json
from pathlib import Path
import re
import subprocess
import sys


TOKEN = re.compile(
    rb'(?P<comment>//[^\r\n]*|/\*[\s\S]*?(?:\*/|\Z))'
    rb'|(?P<literal>"(?:\\[\s\S]|[^"\\])*"|\'(?:\\[\s\S]|[^\'\\])*\')'
    rb'|(?P<word>[A-Za-z_][A-Za-z_0-9]*)|(?P<symbol>[^\s])'
)
DIRECTIVE = re.compile(rb'^\s*#\s*([a-z]+)\b(.*)$')
CONTROL = {'IfStmt', 'ForStmt', 'WhileStmt', 'DoStmt', 'SwitchStmt'}
TERNARY = {'ConditionalOperator', 'BinaryConditionalOperator'}
SNAKE_CASE = re.compile(r'[a-z][a-z0-9]*(?:_[a-z0-9]+)*\Z')


@dataclass(order=True)
class Diagnostic:
    file: str
    line: int
    column: int
    rule: str
    message: str


class Source:
    def __init__(self, path):
        self.path = path
        self.data = path.read_bytes()
        self.lines = self.data.split(b'\n')
        self.starts = [0, *(match.end() for match in re.finditer(b'\n', self.data))]
        self.tokens = list(TOKEN.finditer(self.data))
        self.token_ends = [token.end() for token in self.tokens]
        self.diagnostics = set()

    def location(self, offset):
        index = bisect_right(self.starts, offset) - 1
        prefix = self.data[self.starts[index]:offset]
        return index + 1, len(prefix.decode('utf-8', 'replace').expandtabs(4)) + 1

    def report(self, offset, rule, message):
        line, column = self.location(offset)
        self.diagnostics.add((line, column, rule, message))

    def results(self):
        return [Diagnostic(str(self.path), *item) for item in sorted(self.diagnostics)]

    def previous_token(self, offset):
        index = bisect_right(self.token_ends, offset) - 1
        while index >= 0:
            token = self.tokens[index]
            if token.lastgroup != 'comment':
                return token
            index -= 1
        return None

    def check_text(self):
        physical = self.lines[:-1] if self.data.endswith(b'\n') else self.lines
        if self.data and not self.data.endswith(b'\n'):
            self.report(len(self.data), 'C-A3', 'End the file with a newline.')
        if self.data and not physical[0].strip():
            self.report(0, 'C-G8', 'Remove the blank line at the start of the file.')
        if self.data and not physical[-1].strip() and len(physical) > 1:
            self.report(self.starts[len(physical) - 1], 'C-G8',
                        'Remove blank lines at the end of the file.')
        for index, raw in enumerate(physical):
            self.check_line(raw, self.starts[index])
        self.check_directives()

    def check_line(self, raw, start):
        carriage = raw.find(b'\r')
        if carriage >= 0:
            self.report(start + carriage, 'C-G6', 'Use Unix line endings.')
        line = raw.rstrip(b'\r')
        trailing = len(line.rstrip(b' \t'))
        if trailing < len(line):
            self.report(start + trailing, 'C-G7', 'Remove trailing whitespace.')
        if line.endswith(b'\\') and self.data[start + len(raw):start + len(raw) + 1] == b'\n':
            self.report(start + len(line) - 1, 'C-G6', 'Avoid line continuations.')
        displayed = line.decode('utf-8', 'replace').expandtabs(4)
        if len(displayed) > 80:
            column = 0
            for index, char in enumerate(line.decode('utf-8', 'replace')):
                column += 4 - column % 4 if char == '\t' else 1
                if column > 80:
                    prefix = line.decode('utf-8', 'replace')[:index]
                    self.report(start + len(prefix.encode()), 'C-F3',
                                'Keep the line within 80 columns.')
                    break

    def check_directives(self):
        clean = bytearray(self.data)
        for token in self.tokens:
            if token.lastgroup == 'comment':
                clean[token.start():token.end()] = re.sub(rb'[^\r\n]', b' ', token.group())
        significant = []
        continued = False
        for index, line in enumerate(clean.split(b'\n')):
            if continued:
                continued = line.endswith(b'\\')
                continue
            if not line.strip():
                continue
            directive = DIRECTIVE.match(line)
            significant.append(directive)
            if not directive:
                continue
            name, value = directive.groups()
            continued = line.endswith(b'\\')
            if name == b'define' and continued:
                self.report(self.starts[index], 'C-H3', 'Keep the macro on one line.')
            if name == b'include' and re.match(
                rb'\s*["<][^">]+\.(?:c|cc|cpp|o|a)[">]', value
            ):
                self.report(self.starts[index], 'C-G5', 'Include a header file.')
        if self.path.suffix == '.h' and not has_guard(significant):
            self.report(0, 'C-H2', 'Wrap the header in a matching include guard.')


def has_guard(lines):
    if len(lines) < 3 or not lines[0] or not lines[1]:
        return False
    opening, variable = lines[0].groups()
    definition, value = lines[1].groups()
    if opening != b'ifndef' or definition != b'define':
        return False
    name = variable.strip()
    if not re.fullmatch(rb'[A-Za-z_]\w*', name) or value.split()[:1] != [name]:
        return False
    depth = 0
    for index, directive in enumerate(lines):
        if not directive:
            continue
        kind = directive[1]
        if kind in {b'if', b'ifdef', b'ifndef'}:
            depth += 1
        elif kind in {b'else', b'elif'} and depth == 1:
            return False
        elif kind == b'endif':
            depth -= 1
            if depth == 0:
                return index == len(lines) - 1
    return False


def children(node):
    return node.get('inner', ())


def direct_offset(location):
    if not location or 'includedFrom' in location:
        return None
    return location.get('offset')


def edge(node, side='begin'):
    return direct_offset(node.get('range', {}).get(side))


def mutable_object(node):
    info = node.get('type', {})
    spelling = info.get('desugaredQualType', info.get('qualType', ''))
    if not spelling or '(' in spelling:
        return False
    object_type = spelling.split('[', 1)[0].rsplit('*', 1)[-1]
    return 'const' not in object_type.split()


class AstCheck:
    def __init__(self, source):
        self.source = source
        self.data = source.data
        self.report = source.report

    def check(self, root):
        definitions = []
        for node in children(root):
            loc = node.get('loc', {})
            offset = direct_offset(loc)
            if offset is None or node.get('isImplicit'):
                continue
            if 'file' in loc and Path(loc['file']).resolve() != self.source.path.resolve():
                continue
            if node['kind'] == 'VarDecl' and mutable_object(node):
                self.report(offset, 'C-G4', 'Use an immutable file-scope object.')
            if node['kind'] == 'FunctionDecl':
                body = next((item for item in children(node)
                             if item['kind'] == 'CompoundStmt'), None)
                self.function(node, body, offset)
                if body and edge(node) is not None and edge(body, 'end') is not None:
                    definitions.append((node, body))
        if self.source.path.suffix == '.c':
            self.function_limits(definitions)
        for (_, before), (after, _) in zip(definitions, definitions[1:]):
            end, start = edge(before, 'end') + 1, edge(after)
            gap = self.data[end:start]
            if end <= start and not gap.strip() and gap.count(b'\n') != 2:
                self.report(start, 'C-G2', 'Separate definitions with one blank line.')

    def function_limits(self, definitions):
        public = [pair for pair in definitions if pair[0].get('storageClass') != 'static']
        for entries, limit in ((definitions, 10), (public, 5)):
            if len(entries) > limit:
                scope = 'non-static ' if limit == 5 else ''
                self.report(edge(entries[limit][0]), 'C-O3',
                            f'Use at most {limit} {scope}function definitions per .c file.')

    def function(self, node, body, offset):
        name = node['name']
        if not SNAKE_CASE.fullmatch(name):
            self.report(offset, 'C-F2', 'Use a snake_case function name.')
        params = sum(child['kind'] == 'ParmVarDecl' for child in children(node))
        if params + bool(node.get('variadic')) > 4:
            self.report(offset, 'C-F5', 'Use at most four parameters.')
        name_end = offset + node['loc'].get('tokLen', len(name))
        end = edge(body) if body else edge(node, 'end')
        if end is not None and not params and re.match(rb'\s*\(\s*\)', self.data[name_end:end + 1]):
            self.report(offset, 'C-F6', 'Write (void) for an empty parameter list.')
        if body:
            self.body(body)

    def body(self, body):
        start, end = edge(body), edge(body, 'end')
        if start is None or end is None:
            return
        first, _ = self.source.location(start)
        last, _ = self.source.location(end)
        if last - first - 1 > 20:
            self.report(start, 'C-F4', 'Limit the function body to 20 lines.')
        line_start = self.source.starts[first - 1]
        if self.data[line_start:start].strip():
            self.report(start, 'C-L4', 'Put the function opening brace on its own line.')
        token_index = bisect_right(self.source.token_ends, start)
        for token in self.source.tokens[token_index:]:
            if token.start() >= end:
                break
            if token.lastgroup == 'comment':
                self.report(token.start(), 'C-F8', 'Move the comment outside the function.')
        self.indentation(first, last)
        self.local_declarations(body)
        for child in children(body):
            offset = edge(child)
            if offset is not None and child['kind'] != 'LabelStmt':
                line, _ = self.source.location(offset)
                prefix = self.data[self.source.starts[line - 1]:offset]
                if line > first and not prefix.strip() and len(prefix) % 4 == 0:
                    if b'\t' not in prefix and prefix != b'    ':
                        self.report(offset, 'C-L2', 'Indent direct statements by four spaces.')
            self.statement(child)

    def indentation(self, first, last):
        for line in range(first + 1, last):
            raw = self.source.lines[line - 1]
            indent = raw[:len(raw) - len(raw.lstrip(b' \t'))]
            if not raw.strip() or raw.lstrip().startswith((b'#', b'*', b'//')):
                continue
            offset = self.source.starts[line - 1]
            if b'\t' in indent or len(indent) % 4:
                self.report(offset, 'C-L2', 'Indent using groups of four spaces.')

    def local_declarations(self, body):
        seen_statement = False
        for child in children(body):
            if child['kind'] == 'DeclStmt':
                self.declarations(child, seen_statement)
            else:
                seen_statement = True

    def declarations(self, node, misplaced):
        variables = [item for item in children(node) if item['kind'] == 'VarDecl']
        offset = edge(node)
        if not variables or offset is None:
            return
        if misplaced:
            self.report(offset, 'C-L5', 'Move variable declarations to the function start.')
        if len(variables) > 1:
            self.report(offset, 'C-L5', 'Use one variable declaration per instruction.')

    def statement(self, root):
        stack = [(root, 0, None, False)]
        while stack:
            node, nesting, parent, inside_ternary = stack.pop()
            kind = node.get('kind')
            offset = edge(node)
            if kind in CONTROL:
                nesting += 1
            if offset is not None:
                if kind in TERNARY and inside_ternary:
                    self.report(offset, 'C-C2', 'Use a ternary without nested or chained ternaries.')
                if kind in CONTROL and nesting >= 3:
                    self.report(offset, 'C-C1', 'Reduce control-flow nesting below three levels.')
                if kind in {'GotoStmt', 'IndirectGotoStmt'}:
                    self.report(offset, 'C-C3', 'Replace goto with structured control flow.')
                if kind in {'GCCAsmStmt', 'MSAsmStmt'}:
                    self.report(offset, 'C-G10', 'Remove inline assembly.')
                if kind == 'DeclStmt' and parent is not None:
                    self.declarations(node, True)
                if kind == 'CompoundStmt' and parent in CONTROL:
                    previous = self.source.previous_token(offset)
                    if previous and self.source.location(previous.start())[0] != self.source.location(offset)[0]:
                        self.report(offset, 'C-L4', 'Put the control opening brace on the same line.')
            for child in reversed(children(node)):
                if child.get('kind'):
                    stack.append((child, nesting, kind, inside_ternary
                                  or (kind in TERNARY and offset is not None)))


def clang_ast(path, args):
    command = ['clang', '-x', 'c', '-std=c11', '-fsyntax-only', '-fno-color-diagnostics',
               *args, '-Xclang', '-ast-dump=json', str(path.resolve())]
    completed = subprocess.run(command, capture_output=True, text=True, timeout=60)
    if completed.returncode:
        raise ValueError(completed.stderr.strip() or f'Clang exited {completed.returncode}')
    return json.loads(completed.stdout)


def input_files(path):
    if path.is_dir():
        return sorted(item for item in path.rglob('*')
                      if item.suffix in {'.c', '.h'} and not item.is_symlink() and item.is_file())
    if path.is_file() and path.suffix in {'.c', '.h'}:
        return [path]
    raise ValueError('Expected a directory or a .c or .h file.')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('path', type=Path)
    parser.add_argument('--json', action='store_true', help='emit a JSON report')
    parser.add_argument('--strict', action='store_true', help='fail if any file cannot be analyzed')
    parser.add_argument('--clang-arg', action='append', default=[], help='pass a Clang flag')
    args = parser.parse_args()
    diagnostics = []
    errors = []
    invalid_input = False
    try:
        files = input_files(args.path)
    except (OSError, ValueError) as error:
        files = []
        invalid_input = True
        errors.append({'file': str(args.path), 'message': str(error)})

    for path in files:
        try:
            source = Source(path)
            source.check_text()
        except (OSError, ValueError) as error:
            errors.append({'file': str(path), 'message': str(error)})
            invalid_input = True
            continue
        try:
            AstCheck(source).check(clang_ast(path, args.clang_arg))
        except (OSError, ValueError, subprocess.TimeoutExpired) as error:
            errors.append({'file': str(path), 'message': str(error)})
        diagnostics.extend(source.results())

    if args.json:
        print(json.dumps({'diagnostics': [asdict(item) for item in diagnostics],
                          'analysis_errors': errors}, indent=2))
    else:
        for item in diagnostics:
            print(f'{item.file}:{item.line}:{item.column}: {item.rule}: {item.message}')
        for error in errors:
            print(f"{error['file']}: analysis incomplete: {error['message']}", file=sys.stderr)
    if invalid_input or (args.strict and errors):
        return 2
    return int(bool(diagnostics))


if __name__ == '__main__':
    sys.exit(main())
