Zprh:
	"$$(realpath "$$(dirname "$$0")/../../jt")" internal require git
	
	git clone https://www.github.com/jfrech/Zpr-h.git Zprh-repository \
	    2> /dev/null
	make --silent -C Zprh-repository test=skip
	mv Zprh.zsh Zprh
