#! /bin/zsh

cd "$(dirname "$0")"

# 'make' will already have run on install
make > /dev/null
./create_colorscheme "${@:1}" | zsh

cp "vimrc" "$HOME/.vimrc"
mkdir -p "$HOME/.vim/colors"
cp "j.vim" "$HOME/.vim/colors/j.vim"
