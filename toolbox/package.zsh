find . | grep '^\./\([^./]*\)/\1$' | xargs -l rm -f
find . -maxdepth 1 | grep '^\./' | sed 's|^\./||' | grep '\.tar\.gz$' | xargs -l rm -f
find . -maxdepth 1 | grep '^\./' | sed 's|^\./||' | grep -v '\.' | sed 's|^\(.*\)$|\1.tar.gz \1|' | xargs -l tar -czf
