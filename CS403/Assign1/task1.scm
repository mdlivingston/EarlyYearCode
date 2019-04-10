(define (main)
        (setPort (open (getElement ScamArgs 1) 'read))
        (println (apply zeno (readExpr)))
        )

(define (zeno d n c)
  (define ratio (/ (real 1.0)  (real 12.0)))
  (define t 0.0)
  (define (iter d n c total)
    (define halfed( / (real d) 2.0))
    (define logP (/ (log (real halfed)) (log 2.0))) ;log 2 distance
    (define charge (expt c logP))  ;c^logP
    (cond
     ((< n 2)
      (define logD (/ (log (real d)) (log 2.0))) ;log 2 distance
       (define cha (expt c logD))  ;c^logP
       (* ratio cha)
      )
     ((== n 2)
       (* ratio( + total (* 2.0 charge)))
      )
     (else (iter halfed (- n 1) c (+ total charge )))
     )
    )
  (iter d n c t)
)
