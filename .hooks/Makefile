.PHONY: hooks
hooks:
	mkdir -p "$$(realpath "$$(pwd)/../.git/hooks")"
	printf '#! /bin/zsh\n\n"$$(realpath "$$(dirname "$$0")/../../toolbox/package.zsh")"\n' \
	    > "$$(realpath "$$(pwd)/../.git/hooks/pre-commit")"
	chmod +x "$$(realpath "$$(pwd)/../.git/hooks/pre-commit")"
