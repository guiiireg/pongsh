#!/bin/sh
set -eu

binary=$1
sandbox=$(mktemp -d)
trap 'rm -rf "$sandbox"' EXIT
export LC_ALL=C
unset BLOCK_SIZE BLOCKSIZE LS_BLOCK_SIZE POSIXLY_CORRECT

mkdir "$sandbox/files"
cd "$sandbox/files"
mkdir -p tree/sub
touch tree/.hidden tree/b tree/a tree/sub/nested ./-named
touch -t 202001010000 tree/a
touch -t 202201010000 tree/b
ln -s sub tree/link
ln -s .. tree/sub/back
ln -s absent tree/dangling

compare() {
    ls -1 "$@" > "$sandbox/expected"
    "$binary" "$@" > "$sandbox/actual"
    diff -u "$sandbox/expected" "$sandbox/actual"
}

compare
compare tree
compare -a tree
compare -r tree
compare -t tree
compare -rt tree
compare -aR tree
compare -d tree
compare -drt tree tree/a tree/b
compare tree/sub tree tree/b
compare -- -named
compare tree/link
"$binary" -l tree > "$sandbox/actual"
grep -Eq '^total [0-9]+$' "$sandbox/actual"
grep -Eq '^l[rwxstST-]{9} .* link -> sub$' "$sandbox/actual"
grep -Eq '^l[rwxstST-]{9} .* dangling -> absent$' "$sandbox/actual"
grep -Eq '^-[rwxstST-]{9} .* 2020 a$' "$sandbox/actual"
"$binary" -ld tree > "$sandbox/actual"
grep -Eq '^d[rwxstST-]{9} .* tree$' "$sandbox/actual"

status=0
"$binary" absent tree/a > "$sandbox/actual" 2> "$sandbox/errors" || status=$?
test "$status" -eq 1
test "$(cat "$sandbox/actual")" = 'tree/a'
grep -q absent "$sandbox/errors"

status=0
"$binary" -q > "$sandbox/actual" 2> "$sandbox/errors" || status=$?
test "$status" -eq 2
test ! -s "$sandbox/actual"
grep -q 'invalid option' "$sandbox/errors"

printf '%s\n' 'my_ls integration tests passed'
