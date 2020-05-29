#! /bin/zsh

jt_repository="https://raw.githubusercontent.com/jfrech/jt/master"
jt_local="$HOME/.jt"


[ -d "$jt_local" ] \
    && echo "Cannot install jt; '$jt_local' already exists." && exit 1

require () {
    [ -z "$(command -v $1)" ] && echo "Please install '$1'." && exit 1 }
require curl
require sed

mkdir -p "$jt_local"
curl --silent --fail "$jt_repository/jt" \
    | sed "s|^jt_repository=\"[^\"]*\"\$|jt_repository=\"$jt_repository\"|" \
    > "$jt_local/jt" \
    || echo "Could not curl '$jt_repository/jt'." \
    && rm "$jt_local/jt" && rmdir "$jt_local" && exit 1

chmod +x "$jt_local/jt"
echo "Please add '$jt_local' to your PATH."
