"""Run checker fixtures against Clang through the public CLI."""

import json
from pathlib import Path
import subprocess
import tempfile
import unittest


SCRIPT = Path(__file__).resolve().parents[1] / 'scripts' / 'check_style.py'
CLEAN = 'int identity(int value)\n{\n    return value;\n}\n'

VIOLATIONS = {
    'long_body': ('C-F4', 'void example(void)\n{\n' + '    (void)0;\n' * 21 + '}\n'),
    'long_line': ('C-F3', '/* ' + ('x' * 76) + ' */\n' + CLEAN),
    'parameters': ('C-F5', 'void example(int a, int b, int c, int d, int e)\n{\n}\n'),
    'functions': ('C-O3', '\n'.join(
        f'static void example_{i}(void)\n{{\n}}\n' for i in range(11)
    )),
    'public_functions': ('C-O3', '\n'.join(
        f'void example_{i}(void)\n{{\n}}\n' for i in range(6)
    )),
    'indent': ('C-L2', 'int example(void)\n{\n  return 0;\n}\n'),
    'unindented': ('C-L2', 'int example(void)\n{\nreturn 0;\n}\n'),
    'late_variable': ('C-L5', 'int example(void)\n{\n    (void)0;\n    int x = 0;\n    return x;\n}\n'),
    'comment': ('C-F8', 'int example(void)\n{\n    /* inline */\n    return 0;\n}\n'),
    'jump': ('C-C3', 'void example(void)\n{\n    goto end;\nend:\n    return;\n}\n'),
    'nesting': ('C-C1', '''void example(int a)
{
    if (a) {
        while (a) {
            if (a)
                return;
        }
    }
}
'''),
    'else_if': ('C-C1', '''void example(int a)
{
    if (a == 1) {
        return;
    } else if (a == 2) {
        return;
    } else if (a == 3) {
        return;
    }
}
'''),
    'control_brace': ('C-L4', 'void example(int a)\n{\n    if (a)\n    {\n    }\n}\n'),
    'declarations': ('C-L5', 'void example(void)\n{\n    int a, b;\n}\n'),
    'missing_guard.h': ('C-H2', 'int example(void);\n'),
    'unguarded_code.h': ('C-H2', '#ifndef EXAMPLE_H\n#define EXAMPLE_H\n#endif\nint example(void);\n'),
    'global': ('C-G4', 'int global;\n' + CLEAN),
    'mutable_pointer': ('C-G4', 'const int *global_pointer;\n' + CLEAN),
    'empty_parameters': ('C-F6', 'int example()\n{\n    return 0;\n}\n'),
    'spacing': ('C-G2', CLEAN + 'void next(void)\n{\n}\n'),
    'ternary': ('C-C2', 'int example(int a, int b)\n{\n    return a ? b ? 1 : 2 : 3;\n}\n'),
    'assembly': ('C-G10', 'void example(void)\n{\n    __asm__("nop");\n}\n'),
    'trailing_space': ('C-G7', CLEAN.replace('value;\n', 'value; \n')),
    'line_endings': ('C-G6', CLEAN.replace('\n', '\r\n')),
    'blank_end': ('C-G8', CLEAN + '\n'),
    'missing_newline': ('C-A3', CLEAN.rstrip('\n')),
    'continued_macro': ('C-H3', '#define TEST \\\n    0\n' + CLEAN),
    'function_name': ('C-F2', CLEAN.replace('identity', 'returnValue')),
    'include_source': ('C-G5', '#if 0\n#include "another.c"\n#endif\n' + CLEAN),
}


def run(path, *args):
    return subprocess.run([str(SCRIPT), str(path), *args], capture_output=True, text=True)


class CheckerTests(unittest.TestCase):
    def test_violations(self):
        with tempfile.TemporaryDirectory() as directory:
            for name, (rule, content) in VIOLATIONS.items():
                with self.subTest(name=name):
                    path = Path(directory) / (name if name.endswith('.h') else name + '.c')
                    path.write_bytes(content.encode())
                    result = run(path, '--json', '--strict')
                    self.assertEqual(1, result.returncode, result.stdout + result.stderr)
                    report = json.loads(result.stdout)
                    self.assertFalse(report['analysis_errors'])
                    rules = {item['rule'] for item in report['diagnostics']}
                    self.assertIn(rule, rules)
                    self.assertNotIn('C-G1', rules)

    def test_accepts_file_without_epitech_banner(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'identity.c'
            path.write_text(CLEAN)
            result = run(path, '--strict')
            self.assertEqual((0, '', ''), (result.returncode, result.stdout, result.stderr))

    def test_ignores_comment_markers_in_literals_and_included_declarations(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'external.h').write_text('extern int mutable_external;\n')
            source = root / 'example.c'
            source.write_text('''#include "external.h"

static const int CONSTANT = 1;

const char *text(void)
{
    return "/* not a comment */";
}
''')
            result = run(source, '--strict', '--json')
            self.assertEqual(0, result.returncode, result.stdout + result.stderr)
            self.assertEqual([], json.loads(result.stdout)['diagnostics'])

    def test_recursive_scan_and_text_report(self):
        with tempfile.TemporaryDirectory() as directory:
            nested = Path(directory) / 'nested'
            nested.mkdir()
            (nested / 'good.h').write_text('#ifndef GOOD_H\n#define GOOD_H\n#endif\n')
            (nested / 'bad.h').write_text('int example(void);\n')
            (nested / 'notes.txt').write_text('ignore me')
            result = run(directory, '--strict')
            self.assertEqual(1, result.returncode, result.stderr)
            self.assertRegex(result.stdout, r'bad\.h:1:1: C-H2: .+\n\Z')
            self.assertEqual(1, len(result.stdout.splitlines()))

    def test_strict_analysis_and_clang_flags(self):
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / 'example.c'
            source.write_text('#if !defined(READY)\n#error missing define\n#endif\n' + CLEAN)
            incomplete = run(source, '--json')
            self.assertEqual(0, incomplete.returncode)
            self.assertTrue(json.loads(incomplete.stdout)['analysis_errors'])
            self.assertEqual(2, run(source, '--strict').returncode)
            self.assertEqual(0, run(source, '--strict', '--clang-arg=-DREADY').returncode)

    def test_invalid_path(self):
        with tempfile.TemporaryDirectory() as directory:
            result = run(Path(directory) / 'missing.c', '--json')
            self.assertEqual(2, result.returncode)
            self.assertTrue(json.loads(result.stdout)['analysis_errors'])


if __name__ == '__main__':
    unittest.main()
