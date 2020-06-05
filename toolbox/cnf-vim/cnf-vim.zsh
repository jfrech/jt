#! /bin/zsh

cd "$(dirname "$0")"

# 'make' will already have run on install
make > /dev/null

colorscheme_shell="$(./create_colorscheme "${@:1}")"

< vimrc | eval "$colorscheme_shell" > "$HOME/.vimrc"

mkdir -p "$HOME/.vim/colors"
< j.vim.pre | eval "$colorscheme_shell" > "$HOME/.vim/colors/j.vim"
