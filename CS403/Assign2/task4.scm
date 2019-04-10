(define (main)
	(setPort (open (getElement ScamArgs 1) 'read))
	(println (if2cond (readExpr)))
	(println (cond2if (readExpr)))
)

(define (if2cond expr)
	(cond
		(
			(or (eq? (type expr) 'SYMBOL) (eq? (type expr) 'INTEGER))
			expr
		)
		(
			(eq? (car expr) 'if)
			(list 'cond (list (if2cond (cadr expr)) (if2cond (caddr expr))) (list 'else (if2cond (cadddr expr))))
		)
		(else
			expr
		)
	)
)

(define (cond2if expr)
	(define (caadr expr)
		(car (cadr expr))
	)
	
	(define (cdadr expr)
		(cadr (cadr expr))
	)
	
	(cond
		(
			(or (eq? (type expr) 'SYMBOL) (eq? (type expr) 'INTEGER) (eq? (type expr) 'STRING))
			expr
		)
		(
			(eq? (car expr) 'cond)
			(if (> (length expr) 3)
				(list 'if (cond2if (caadr expr)) (cond2if (cdadr expr)) (cond2if (cons 'cond (cddr expr))))
				(list 'if (cond2if (caadr expr)) (cond2if (cdadr expr)) (cond2if (caddr expr)))
			)
		)
		(
			(eq? (car expr) 'else)
			(cond2if (cadr expr))
		)
		(else
			expr
		)
	)
)
