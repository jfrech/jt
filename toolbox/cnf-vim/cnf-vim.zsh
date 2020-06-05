#! /bin/zsh

cd "$(dirname "$0")"
newlines_file="$(realpath "$(dirname "$0")/newlines.txt")"

colorscheme_shell="$(./create_colorscheme "${@:1}")"

< vimrc | eval "$colorscheme_shell" \
    | sed "s|%newlines_file|$newlines_file|g" > "$HOME/.vimrc"

mkdir -p "$HOME/.vim/colors"
< j.vim.pre | eval "$colorscheme_shell" > "$HOME/.vim/colors/j.vim"
