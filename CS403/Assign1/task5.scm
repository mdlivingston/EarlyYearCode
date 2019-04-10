(define (main)
        (setPort (open (getElement ScamArgs 1) 'read))
        (println (apply pt (readExpr)))
        )

(define (pt level)
  
  (define (buildPascal left right levels)
    
   (define (pad spaces)
    (if (> spaces 0)     
	(begin
        (print " ")    
        (pad (- spaces 1)) 
        )
      )
    )

   (define (adjuster level column)
    
     ;(inspect level)
      (cond
       ((= column 0) left)
       ((= level column) right)
       (else                  
        (+ 
          (adjuster (- level 1) (- column 1))
          (adjuster (- level 1) column)      
          ) 
        )
       
      )
      )
   
   (define (printlvl level)
     (if (== levels -1)
	 nil
    (if (<= level levels)                      
      (begin 
      (pad (- levels level))                   
        (define (printcol col)
          (if (< col level)                   
	      (begin
              (print (adjuster level col) " ")  
              (printcol (+ col 1))             
              )
	      )
	   (if (= col level)                   
	      (begin
              (print (adjuster level col))  
              (printcol (+ col 1))             
              )
            )
          )
	(printcol 0)
	;(println)
        (if (!= level levels)
	    (println)
	  )  
	 (if (== level levels)
	      nil
	    (printlvl (+ level 1))
	    )
	 
        )
      )
    )
    )

  (printlvl 0)
  )
  (buildPascal 1 1 (- level 1) )
)


