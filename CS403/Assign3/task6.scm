
(define (main)
    (setPort (open (getElement ScamArgs 1) 'read))
    (define outPrint (readExpr))
    (define factor (readExpr))
    (stream-display outPrint (pfs factor))
    (println)

)


(define scons cons-stream)
(define scar stream-car)
(define scdr stream-cdr)
(define (stream-scale number stream)
    (scons (* number (scar stream)) (stream-scale number (scdr stream)))
) 

(define (stream-merge stream1 stream2)
    (cond
        ((< (scar stream1) (scar stream2)) (scons (scar stream1) (stream-merge (scdr stream1) stream2)))
        ((> (scar stream1) (scar stream2)) (scons (scar stream2) (stream-merge stream1 (scdr stream2))))
        (else
            (scons (scar stream1) (stream-merge (scdr stream1) (scdr stream2))))
    )
)

(define (stream-display n s)
    (define (stream-helper t c)
        (if (= c 0)
            'OK
            (begin
                (print (stream-car t) " ")
                (stream-helper (stream-cdr t) (- c 1))
            )
        )
    )
    (print "(")
    (stream-helper s n)
    (print "...)")
)


(define (pfs @)
        (define (iterative currentS rList)
                (cond
                    ((not (null? rList)) (stream-merge (stream-scale currentS s) (iterative (car rList) (cdr rList))))
                    (else 
                        (stream-scale currentS s))
                )
        )
        (scdr (define s (scons 1 (iterative (car @) (cdr @)))))
)
