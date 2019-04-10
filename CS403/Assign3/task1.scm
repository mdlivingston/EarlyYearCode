(define (main)
  (setPort (open (getElement ScamArgs 1) 'read))
  (define function (readExpr))
  (define  functionCall (readExpr))
  (eval function this)
  (eval functionCall this)
)

(define (getSS scope)
	(define nSCO (cadr  (caddr scope)))
	(cond
	    ((not (null? nSCO))
	    (begin 
		(println (car nSCO))
		(+ 1 (getSS nSCO )))
		)
		(else
		 (+ 0 0)
		)
	)
)

(define (staticScope levels scope)
	(define (staticScope-iter levels scope counter)
		(define (printValues vars vals)
			(cond
				((not (null? vars))					
					(begin
						(print "    " (car vars) " : ") 
						(println (car vals)) 
						(printValues (cdr vars) (cdr vals))
					)
				)
				(else
					nil
				)
			)
		)
		(define currentLevel (caddr (caddr scope)))
		(define vars (cdr (cddddr (cadr scope))))
		(define vals (cdr (cddddr (caddr scope))))
		(define nScope (cadr  (caddr scope)))
	 
		(if (not (= 0 levels))
			(begin
				(print "#[environment L" counter) (println "]")
				(printValues vars vals)
				(staticScope-iter (- levels 1) nScope (+ counter 1))
			)
			nil
		)
	)
	(staticScope-iter levels scope 0)
)
