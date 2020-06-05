#! /bin/zsh

jt="$(realpath "$(dirname "$0")/../../jt")"
fail () { "$jt" internal fail $@ ; exit 1 }
"$jt" internal require uuidgen

jt_local_tool="$(realpath "$(dirname "$0")")"

Zprh_source="$(realpath "$1")"
[ ! -f "$Zprh_source" ] && fail "Could not find source file '$Zprh_source'."

uuid="$(uuidgen)"
mkdir -p "$jt_local_tool/.exec/"
cp -r "$jt_local_tool/Zprh-repository/stdlib" "$jt_local_tool/.exec/$uuid"
cp "$Zprh_source" "$jt_local_tool/.exec/$uuid/src.zprh"
"$jt_local_tool/Zprh-repository/Zprh" \
    "$jt_local_tool/.exec/$uuid/src.zprh" "${@:2}"
rm -rf "$jt_local_tool/.exec/$uuid"
