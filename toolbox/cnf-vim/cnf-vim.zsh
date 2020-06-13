#! /bin/zsh

tool_dir="$(realpath "$(dirname "$0")")"
dot_jt="$(realpath "$tool_dir/../..")"
jt="$dot_jt/jt"


newlines_file="$tool_dir/newlines.txt"
colorscheme_shell="$("$tool_dir/create_colorscheme" "${@:1}")"

"$jt" safe rmf "$HOME/.vimrc"
< "$tool_dir/vimrc" | eval "$colorscheme_shell" \
    | sed "s|%newlines_file|$newlines_file|g" > "$HOME/.vimrc"

mkdir -p "$HOME/.vim/colors"
"$jt" safe rmf "$HOME/.vim/colors/j.vim"
< "$tool_dir/j.vim.pre" | eval "$colorscheme_shell" > "$HOME/.vim/colors/j.vim"

mkdir -p "$HOME/.vim/undo"
