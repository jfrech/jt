#! /bin/zsh

jt_local_tool="$(realpath "$(dirname "$0")")"

Zprh_source="$(realpath "$1")"
[ ! -f "$Zprh_source" ] && echo "Could not find source file '$Zprh_source'." \
    && exit 1

uuid="$(uuidgen)"
mkdir -p "$jt_local_tool/.exec/"
cp -r "$jt_local_tool/Zprh-repository/stdlib" "$jt_local_tool/.exec/$uuid"
cp "$Zprh_source" "$jt_local_tool/.exec/$uuid/src.zprh"
"$jt_local_tool/Zprh-repository/Zprh" "$jt_local_tool/.exec/$uuid/src.zprh"
