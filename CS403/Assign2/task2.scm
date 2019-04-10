(define (main)
        (setPort (open (getElement ScamArgs 1) 'read))
	(define f (readExpr))
        (define first (readExpr))
        (define second (readExpr))
        (define third (cons first second))
	(println (pfa (eval f this) first second))
;	(inspect ((pfa (lambda (a b c) (+ a b c)) 68) -22 56) )
;	(inspect (catch ((pfa (lambda (a b c) (+ a b c)) 74) -17 -79 74)))
;	(inspect (catch ((pfa (lambda (a b c) (+ a b c)) 74) -17)))
   ;	(inspect ((pfa (lambda nil 1))))
        )

(define (flatten x)
  (cond ((null? x) '())
        ((pair? x) (append (flatten (car x)) (flatten (cdr x))))
        (else (list x))))

(define (printFew)
   (throw 'MALFORMED_FUNCTION_CALL "too few arguments")
    )
(define (printMany)
    (throw 'MALFORMED_FUNCTION_CALL "too many arguments")
    )

(define (pfa @)
    ; Checks if the arg is the function itself or if it is nested further down
    (if (is? (car @) 'CONS)
        ; If it is nested call the nested part L
        (define L (car @))
        ; Otherwise call the whole thing L
        (define L @)
	)
    ; Define need as the amount of parameters needed for the function in L
    (define (need) (length (get 'parameters (car L))))
    (if (< (length (cdr L)) (need))
        ; Make a lambda that recalls the function with a more flattened list
	(cond
	 ((and (== nil (cdr L)) (== nil (get 'parameters (car L))))
	 ; (apply (car L) (flatten (cdr L))))
	  (printFew))
	 ((== (cdr @) nil)
	   (printFew))
	 (else
	  (lambda (@) (pfa (append L @))))
	     )
	; Else, apply the function to the rest of the list.
	(cond
	 ((> (length (cdr L)) (need))
	  (printMany))
	 (else
	  (apply (car L) (flatten (cdr L)))))
	)
    )
