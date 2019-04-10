(define (main)
  (define (run input)
  (println "mystery returns " (mystery input))
  (println "imystery returns " (imystery input))
  (println "$\\sqrt{e}$")
  ;(println (imystery 696))
  )
  (setPort (open (getElement ScamArgs 1) 'read))
  (apply run (readExpr))
)

(define (mystery n)
  (define (helper depth add)               
    (if (<= depth n)                  
      (/ 1.0                             
        (+ add                           
          (/ 1.0                          
            (+ 1.0              
              (/ 1.0                      
		 (+ 1.0
		    (helper (+ depth 1.0) (+ add 4))  
                  )
                )
              )
            )
          )
        )
      0                                 
      )
    )
  (+ 1.0 (helper 1.0 1.0))
 )

(define (imystery n)
  (define (cont-frac n d k)
    
    (define number  (d 1))
    
    (define (cont-frac-iter i result num)
      (if (< i 2) 
         (/ (n i) (+ num  (/ 1.0
			     (+ 1.0              
			      (/ 1.0                      
				 (+ 1.0 result))))))
	 
         (cont-frac-iter (- i 1) 
			 (/ (n i) (+ num  (/ 1.0
			     (+ 1.0              
			      (/ 1.0                      
			       (+ 1.0 result)))))) 
			 (- num  4.0)))) 
      (cont-frac-iter k 0.0 number)
    )

  (define (e-euler k)
   
    (define num (+ 1.0 (* 4 (- k 1))))
      (+ 1.0 (cont-frac (lambda (i) 1) 
                     (lambda (i) num)
                     k))
   )
   (if (== n 0)
       1.0

       (e-euler n)
   )

  
 )


