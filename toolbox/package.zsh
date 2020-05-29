#! /bin/zsh

jt_local_toolbox="$(realpath "$(dirname "$0")")"
cd "$jt_local_toolbox"

find . | grep '^\./\([^./]*\)/Makefile$' \
    | sed 's|^\./\([^./]*\)/Makefile$|./\1/\1|' | xargs -l rm -f
find . -maxdepth 1 | grep '^\./' | sed 's|^\./||' | grep '\.tar\.gz$' \
    | xargs -l rm -f
find . -maxdepth 1 | grep '^\./' | sed 's|^\./||' | grep -v '\.' \
    | sed 's|^\(.*\)$|\1.tar.gz \1|' | xargs -l tar -czf

find . -mindepth 2 | grep -o '^\./[^./]*/' | sed 's|^\./||; s|/$||' \
    | uniq | sort > tools.txt
