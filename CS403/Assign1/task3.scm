(define (main)
   (define (printNumbers x y t)
     (define i (resistance x y t))
     (println i " "(mred i t)" "(mgreen i t) " "(mblue i t))
     ;(println (mblue 22 23))
     ;(println (mblue 83 84))
    ; (println (mblue 93 94))
     ;(println (mgreen 6 13))
     ;(println (mgreen 22 23))
    ; (println (mred 23 48))
     ;(println (mblue 0 27))
     )
  (setPort (open (getElement ScamArgs 1) 'read))
  (apply printNumbers (readExpr))
 )

(define pi 3.14159265358979323846)

(define (mred i t)
  ;(inspect i)
  ;(inspect t)
  (cond
   ((== i t) 0 )
   ((== i (- t 1)) 0)
   ((== i 0) 255 )
   ((== i (/ (- t 1) (real 2))) 180)
   (else
    (define offset ( * ( * (/ (/ 180.0 (- t 1)) 2) i) (/ pi 180))  )
    (define red ( cos offset) )
     (integer (+ (* 255.0 red) 0.5 ))
    )
   )
  )
(define (mblue i t)
  (cond
   ((== i t) 0 )
   ((== i 0) 0 )
   ((== i (- t 1)) 255 )
   ((== i (/ (- t 1) (real 2))) 180)
   (else
    (define offset ( * ( * (/ (/ 180.0 (- t 1)) 2) i) (/ pi 180))  )
    (define blue (sin offset) )
    (integer (+ (* 255 blue) 0.5 ))
    )
   )
  )
(define (mgreen i t)
  
  (cond
   ((== i t) 0 )
   ((== i 0) 0 )
   ((== i (- t 1)) 0 )
   ((== i (/ (- t 1) (real 2))) 255)
   (else
    (define offset ( * ( * (/  180.0 (- t 1)) i) (/ pi 180))  )
    (define green (sin offset) )
    (integer (+ (* 255 green) 0.5))
    )
   )
  )

(define (resistance x y t)
 
  (define (mandelbrot threshold)
  
  (lambda (x y)
   
    (define (iter r s t)
   
      (if (= t threshold)
	  t
	 
        (if (< 2 (sqrt (+ (* r r) (* s s))))
	   ;if diverges, return
	    t
	  
     	 ; otherwise, iterate 
          (iter 
            ; r value
            (+ x (- (* r r) (* s s)))
            ; s value
            (+ y (* r s 2))
            ; t value
            (+ 1 t)
            )
          )
        )
      )
    ; call with default values 0.0 for r and 0.0 for s
    (iter 0.0 0.0 0)
    )
  )
  (define mandelbrotResistance (mandelbrot t))
   (mandelbrotResistance x y)
 )
