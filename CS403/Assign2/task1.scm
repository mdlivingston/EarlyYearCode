(define (main)
  (setPort (open (getElement ScamArgs 1) 'read))
  (n-loop (eval (readExpr) this) (car (readExpr)))
  ;(n-loop (lambda (x) (print x)) '(0 1))
 ; (n-loop (lambda (x) (print x)) '(8 21))
  ;(n-loop (lambda (x) (print x)) '(8 25))
  ;(n-loop (lambda (x) (print x)) '(9 20))
  ;(n-loop (lambda (x) (print x)) '(4 21))
  ;(n-loop (lambda (a b c d e f g h i j) (print j i h g f e d c b a)) '(10 12) '(9 11) '(8 9) '(7 8) '(6 7) '(5 6) '(4 6) '(3 4) '(2 4) '(1 3))
 ; (n-loop (lambda (a b c d e f g h i j) (print j i h g f e d c b a)) '(10 12) '(9 10) '(8 9) '(7 8) '(6 7) '(5 6) '(4 6) '(3 5) '(2 4) '(1 2))
)


(define (n-loop func @)
  ;(inspect func)
  ;(inspect(length  @))
 ; (inspect @)
  (define (levelOut lis)
    (inspect lis)
    (if (== (length lis) 1)
	lis
	(levelOut (list lis))
	)
    )
  
  ;(inspect (levelOut @))
   (define (getStart pair)
		(car pair)
	)

   (define (getStop pair)
		(car (cdr pair))
	)
	
   (define (h lists anslist) 
	  (if (= (length lists) 1)
		(if (< (getStart (car lists)) (getStop (car lists)))
			(begin
			       (apply func (append anslist (list (getStart (car lists)))))
			       (h (list (list (+ (getStart (car lists)) 1) (getStop (car lists)))) anslist)
			   )
				;else do nothing
		    )
			
		(if (< (getStart (car lists)) (getStop (car lists)))
			  (begin 
				  (h (cdr lists) (append anslist (list (getStart (car lists)))))
				  (h (append (list (list (+ (getStart (car lists)) 1) (getStop (car lists)))) (cdr lists)) anslist)
				)
				;else do nothing
			)
		)
	)

	 (h (car (list @)) '())
)
					
					
