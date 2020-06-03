krrp:
	"$$(realpath "$$(dirname "$$0")/../../jt")" internal require \
	    git clang ln
	
	git clone https://www.github.com/jfrech/krrp.git krrp-repository \
	    2> /dev/null
	make --silent -C krrp-repository
	ln krrp-repository/krrp krrp
