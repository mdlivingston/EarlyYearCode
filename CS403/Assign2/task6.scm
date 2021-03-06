(define (main)
	(setPort (open (getElement ScamArgs 1) 'read))
	(define op (readExpr))
	(define args (readExpr))
	(println (apply map+ (cons (eval op this) args)))
)

(define (map+ func @)
	(define (map-iter cur arglist)
		(cond 
			((nil? (car arglist)) cur)
			(else
			 (map-iter (append cur (list (apply func (map (lambda (l) (car l)) arglist))))
				   (map (lambda(l) (cdr l)) arglist))
			)
		)
	)
	(map-iter '() @)
)
