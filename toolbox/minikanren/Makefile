minikanren:
	../../jt internal require curl

	printf '#lang racket\n(provide (all-defined-out))\n\n' > implementation.rkt
	curl --silent --fail 'https://raw.githubusercontent.com/TheReasonedSchemer2ndEd/CodeFromTheReasonedSchemer2ndEd/master/trs2-impl.scm' >> implementation.rkt
	mv minikanren.sh minikanren
