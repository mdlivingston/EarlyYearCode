(define (main)
        (setPort (open (getElement ScamArgs 1) 'read))
        (println (apply root12 (readExpr)))
        )

(define (root12 x)
  
  (define (root number degree tolerance)
  (define (good-enough? next guess)
    (< (abs (- next guess)) tolerance))
  (define (improve guess)
    (/ (+ (* (- degree 1) guess) (/ number (expt guess (- degree 1)))) degree))
  (define (*root guess)
    (let ((next (improve guess)))
      (if (good-enough? next guess)
          guess
          (*root next))))
  
  (*root 1.0))
  (if (== x 0)
      0.0
      (root x 12 0.0000000000001)
      )
  
 )
