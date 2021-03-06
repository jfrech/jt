#! /bin/zsh

jt_local_toolbox="$(realpath "$(dirname "$0")")"
cd "$jt_local_toolbox"

find . | grep '^\./\([^./]*\)/Makefile$' \
    | sed 's|^\./\([^./]*\)/Makefile$|./\1/\1|' | xargs -l rm -f
find . -maxdepth 1 | grep '^\./' | sed 's|^\./||' | grep '\.tar\.gz$' \
    | xargs -l rm -f
find . -maxdepth 1 | grep '^\./' | sed 's|^\./||' | grep -v '\.' \
    | sed 's|^\(.*\)$|\1.tar \1|' | xargs -l \
    tar --sort=name -cf
find . -maxdepth 1 | grep '^\./[a-zA-Z-]\+\.tar$' | xargs -l \
    gzip --no-name --best

find . -mindepth 2 | grep -o '^\./[^./]*/' | sed 's|^\./||; s|/$||' \
    | uniq | sort > tools.txt
