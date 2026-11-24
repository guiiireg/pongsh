#!/bin/sh
set -eu

binary=$1
sandbox=$(mktemp -d)
trap 'rm -rf "$sandbox"' EXIT
export LC_ALL=C TZ=UTC
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
grep -Eq '^l[rwxstST-]{9} .*  link -> sub$' "$sandbox/actual"
grep -Eq '^l[rwxstST-]{9} .*  dangling -> absent$' "$sandbox/actual"
grep -Eq '^\.[rwxstST-]{9} .* 1 janv\.  2020  a$' "$sandbox/actual"
"$binary" -ld tree > "$sandbox/actual"
grep -Eq '^d[rwxstST-]{9} - .*  tree$' "$sandbox/actual"

mkdir -p display/include
truncate -s 69 display/.gitignore
truncate -s 4600 display/AGENTS.md
truncate -s 12450 display/Makefile
truncate -s 999500 display/README.md
touch display/my_ls
chmod 755 display/include display/my_ls
chmod 644 display/.gitignore display/AGENTS.md display/Makefile \
    display/README.md
touch -t 202001230000 display/include display/.gitignore display/AGENTS.md \
    display/Makefile display/README.md display/my_ls
owner=$(id -un)
{
    printf '.rw-r--r-- %4s %s 23 janv.  2020 󰊢 .gitignore\n' 69 "$owner"
    printf '.rw-r--r-- %4s %s 23 janv.  2020  AGENTS.md\n' 4,6k "$owner"
    printf '.rw-r--r-- %4s %s 23 janv.  2020  Makefile\n' 12k "$owner"
    printf '.rw-r--r-- %4s %s 23 janv.  2020 󰂺 README.md\n' 1,0M "$owner"
    printf 'drwxr-xr-x %4s %s 23 janv.  2020  include\n' '-' "$owner"
    printf '.rwxr-xr-x %4s %s 23 janv.  2020 󰡯 my_ls\n' 0 "$owner"
} > "$sandbox/expected"
compare_long_names() {
    "$binary" "$@" display > "$sandbox/short"
    "$binary" -l "$@" display > "$sandbox/long"
    awk '{print $NF}' "$sandbox/long" > "$sandbox/names"
    diff -u "$sandbox/short" "$sandbox/names"
}

compare_long_names
compare_long_names -a
compare_long_names -r
compare_long_names -t
compare_long_names -rt
"$binary" -l tree/link > "$sandbox/actual"
grep -q ' nested$' "$sandbox/actual"
"$binary" -ld tree/link > "$sandbox/actual"
grep -q ' tree/link -> sub$' "$sandbox/actual"
"$binary" -la display > "$sandbox/all"
awk '$NF != "." && $NF != ".."' "$sandbox/all" > "$sandbox/actual"
diff -u "$sandbox/expected" "$sandbox/actual"
"$binary" -ld display/include/ > "$sandbox/actual"
grep -q ' display/include/$' "$sandbox/actual"

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
