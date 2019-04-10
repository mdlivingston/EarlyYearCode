(define (main)
  (define (run input)
    (println "ramanujan returns " (ramanujan input))
    (println "iramanujan returns " (iramanujan input))
    (println "$3$")
    )
  (setPort (open (getElement ScamArgs 1) 'read))
  (apply run (readExpr))
)

(define (ramanujan depth)
  (define (h x) 
    (if (< (- x 1) (+ depth 1))
      (* x                       
        (sqrt                    
          (+ 1                   
            (h (+ x 1))           
            )
          )
	)
      0.0                           
      )
    )
  (if (!= depth 0)
      (h 1)
      0.0
      )
)


(define (iramanujan depth)
  (define (iter store src)                
    (if (> src 0)                         
      (iter                               
        (* src (sqrt (+ 1 store)))
        (- src 1)                         
        )
      store                               
      )
    )
  (if (!= depth 0)
      (iter 0.0  ( + 1 depth))
      0.0
      )
  
  )
