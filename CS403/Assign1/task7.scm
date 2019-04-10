(define (main)
        (setPort (open (getElement ScamArgs 1) 'read))
        (println (apply zarp (readExpr)))
        )

(define (zarp i)
  (if (< i 3) i
    (begin
      (define (iter n p1 p2 p3)
        (if (<= n i)
          (iter                            
            (+ 1 n)                         
            (- (+ p1 (* 2 p2)) p3) 
            p1                         
            p2                                                
            )
          p1
          )
        )
      (iter 3 2 1 0)
      )
    ) 
  )
