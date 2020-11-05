#! /bin/zsh

jt="$(realpath "$(dirname "$0")/../../jt")"
fail () { "$jt" internal fail $@ ; exit 1 }
"$jt" internal require uuidgen racket

jt_local_tool="$(realpath "$(dirname "$0")")"

miniKanren_source="$(realpath "$1")"
[ ! -f "$miniKanren_source" ] \
    && fail "could not find source file: $miniKanren_source"

exec_file="$jt_local_tool/.exec/$(uuidgen)"
mkdir -p "$(dirname "$exec_file")"
printf '#lang racket\n(require (file "%s"))\n\n' \
    "$jt_local_tool/implementation.rkt" > "$exec_file"
cat "$miniKanren_source" >> "$exec_file"
racket "$exec_file"
rm -f "$exec_file"
