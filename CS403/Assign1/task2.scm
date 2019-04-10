(define (main)
        (setPort (open (getElement ScamArgs 1) 'read))
        (println (apply minMaxSum (readExpr)))
	;(println (minMaxSum 1 2 3))
	;(println (minMaxSum 35 74 113))
	;(println (minMaxSum -93 -170 -247))
	;(println (minMaxSum -93 -247 -170) )
	;(println (minMaxSum -170 -93 -247))
	;(println (minMaxSum -170 -247 -93))
	;(println (minMaxSum -247 -93 -170))
	;(println (minMaxSum -247 -170 -93))
	;(println (minMaxSum 2147483647 -2147483648 -2147483646))
	;(println (minMaxSum 2147483647 -2147483646 -2147483648))
	;(println (minMaxSum -2147483648 2147483647 -2147483646))
	;(println (minMaxSum -2147483648 -2147483646 2147483647) )
	;(println (minMaxSum -2147483646 2147483647 -2147483648) )
	;(println (minMaxSum -2147483646 -2147483648 2147483647))
	;(println (minMaxSum 2147483647 -2147483648 2147483645))
	;(println (minMaxSum 2147483647 2147483645 -2147483648) )
	;(println (minMaxSum -2147483648 2147483647 2147483645) )
	;(println (minMaxSum -2147483648 2147483645 2147483647) )
	;(println (minMaxSum 2147483645 2147483647 -2147483648))
	;(println (minMaxSum 2147483645 -2147483648 2147483647))
        )

;(define  old< <)
;(define count 0)
;(define (< x y)
;  (++ count)
;  (old< x y)
;  )

(define (minMaxSum a b c)
  (cond
   ((< a b)
     (cond
      ((< b c)
        (+ a c))
      (else
       (cond
	((< a c)
	 (+ a b))
	(else
	 (+ c b))))))
     (else
      (cond
       ((< a c)
        (+ b c))
      (else
       (cond
	((< b c)
	 (+ a b))
	(else
	 (+ a c)))))))
    
  )

;(inspect (minMaxSum 1 2 3))
;(inspect (minMaxSum 1 3 2))
;(inspect (minMaxSum 2 1 3))
;(inspect (minMaxSum 2 3 1))
;(inspect (minMaxSum 3 2 1))
;(inspect (minMaxSum 3 1 2))
;(inspect count)
