#!/bin/sh
set -eu

binary=$1
sandbox=$(mktemp -d)
trap 'rm -rf "$sandbox"' EXIT

mkdir "$sandbox/work"
cd "$sandbox/work"

run_shell() {
    status=0
    "$binary" < "$sandbox/input" > "$sandbox/out" 2> "$sandbox/err" ||
        status=$?
    test "$status" -eq "$1"
}

cat > "$sandbox/input" <<'INPUT'
/usr/bin/printf '<%s>\n' "a b" 'semi;colon' a\ b ''
echo first; echo second
exit 7
echo unreachable
INPUT
run_shell 7
cat > "$sandbox/expected" <<'EXPECTED'
<a b>
<semi;colon>
<a b>
<>
first
second
EXPECTED
diff -u "$sandbox/expected" "$sandbox/out"
test ! -s "$sandbox/err"

cat > "$sandbox/input" <<'INPUT'
setenv PONGSH_TEST value
/usr/bin/printenv PONGSH_TEST
unsetenv PONGSH_TEST
/usr/bin/printenv PONGSH_TEST
exit
INPUT
run_shell 1
test "$(cat "$sandbox/out")" = value
test ! -s "$sandbox/err"

mkdir nested
{
    printf 'setenv HOME "%s/work/nested"\n' "$sandbox"
    printf '%s\n' 'cd' '/bin/pwd' 'cd -' '/bin/pwd'
} > "$sandbox/input"
run_shell 0
printf '%s\n' "$sandbox/work/nested" "$sandbox/work" "$sandbox/work"     > "$sandbox/expected"
diff -u "$sandbox/expected" "$sandbox/out"

printf '%s\n' '#!/bin/sh' 'echo local' > pongsh-test-command
chmod +x pongsh-test-command
printf '%s\n' 'setenv PATH ""' 'pongsh-test-command' > "$sandbox/input"
run_shell 0
test "$(cat "$sandbox/out")" = local
test ! -s "$sandbox/err"

printf '%s\n' 'pongsh-missing-test-command' > "$sandbox/input"
run_shell 127
grep -q 'command not found' "$sandbox/err"

printf '%s\n' 'echo "unterminated' > "$sandbox/input"
run_shell 2
test ! -s "$sandbox/out"
grep -q 'invalid syntax' "$sandbox/err"

printf '%s\n' 'echo blocked; echo "unterminated' > "$sandbox/input"
run_shell 2
test ! -s "$sandbox/out"

printf '%s\n' 'echo blocked | /bin/cat' > "$sandbox/input"
run_shell 2
test ! -s "$sandbox/out"

printf '%s\n' "/bin/sh -c 'kill -TERM \$\$'" > "$sandbox/input"
run_shell 143

printf '%s\n' '/bin/cat' 'the child reads this' > "$sandbox/input"
run_shell 0
test "$(cat "$sandbox/out")" = 'the child reads this'

long_word=$(awk 'BEGIN { for (i = 0; i < 512; i++) printf "x" }')
printf '/bin/echo %s\n' "$long_word" > "$sandbox/input"
run_shell 0
test "$(cat "$sandbox/out")" = "$long_word"

printf '%s' '/bin/echo no-newline' > "$sandbox/input"
run_shell 0
test "$(cat "$sandbox/out")" = no-newline

printf '%s\n' 'pongsh integration tests passed'
