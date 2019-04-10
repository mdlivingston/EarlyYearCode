 (define (main)
        (setPort (open (getElement ScamArgs 1) 'read))
        ;(define arg (readExpr))
	;(define arg1 (car arg))
		;(inspect arg1)
	;(define arg2 (cdr arg))
		;(inspect arg2)
	(define arg1 (readExpr))
		;(inspect arg1)
	(define arg2 (readExpr))
	;(inspect arg2)
        (println (extract arg1 arg2))
        )

(define (extract instructions target)
  (define (distill str li)
    (cond 
      ((null? str) li)
      ((equal? "h" (car str))		 ; h = take the car target
        (distill (cdr str) (car li))) ; and advance instruction string
      ((equal? "t" (car str))
        (distill (cdr str) (cdr li))) ; t = take the cdr of target
      )
    )
  (distill (string instructions) target)
  )