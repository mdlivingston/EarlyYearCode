(define (main)
    (setPort (open (getElement ScamArgs 1) 'read))
    (define args (readExpr))
    (stream-display args (ramanujan))
    (println)
)


(define scons cons-stream)
(define scar stream-car)
(define scdr stream-cdr)
(define (scadr s) (scar (scdr s)))
(define (scddr s) (scdr (scdr s)))
(define (scdddr s) (scdr (scddr s)))


(define (stream-add s t)
    (scons
        (+ (scar s) (scar t))
        (stream-add (scdr s) (scdr t))
    )
)

(define (stream-display n s)
    (define (helper t c)
        (if (= c 0)
            'OK
            (begin
                (print (stream-car t) " ")
                (helper (stream-cdr t) (- c 1))
            )
        )
    )
    (print "(")
    (helper s n)
    (print "...)")
)

(define (stream-map f s) (scons (f (scar s)) (stream-map f (scdr s))))

(define (ramanujan)
    (define (helper streamNum)
        (define curr (scar streamNum))
        (define nxt (scadr streamNum))
        (define guess (SumSumSum curr))
        (cond
            ((== guess (SumSumSum nxt)) (scons guess (helper (scddr streamNum))))
            (else
                (helper (scdr streamNum)))
        )
    )
    (helper (weighted-pairs ints ints SumSumSum))
)

(define (cube x) (* x x x))
(define (SumSumSum x) (+ (cube (car x)) (cube (cadr x))))
(define ints (scons 1 (stream-add ones ints)))
(define ones (scons 1 ones))
(define (merge-weighted stream1 stream2 weight)
    (if (<= (weight (scar stream1)) (weight (scar stream2)))
        (scons (scar stream1) (merge-weighted (scdr stream1) stream2 weight))
        (scons (scar stream2) (merge-weighted stream1 (scdr stream2) weight))
    )
)

(define (weighted-pairs stream t weight)
    (scons (list (scar stream) (scar t)) (merge-weighted (stream-map (lambda (x) (list (scar stream) x)) (scdr t)) (weighted-pairs (scdr stream) (scdr t) weight) weight))
)
