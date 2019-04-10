
(define (main)
    (setPort (open (getElement ScamArgs 1) 'read))
    (define printcount (readExpr))
    (define nvalue (readExpr))
    (define stream twinPrimes)
    (stream-display printcount (twinPrimes nvalue))
    (println)

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

(define (repeat x) 
    (cons-stream x (repeat x))
)

(define (stream-keep p? s)
    (if (p? (stream-car s))
        (cons-stream (stream-car s) (stream-keep p? (stream-cdr s)))
        (stream-keep p? (stream-cdr s))
    )
)

(define (stream-add s t)
    (cons-stream (+ (stream-car s) (stream-car t)) (stream-add (stream-cdr s) (stream-cdr t)))
)

(define cNums
  (cons-stream 1 (stream-add (repeat 1) cNums))
)

(define (divisible? a b) (= (% a b) 0))

(define (sieve stream)
    (cons-stream (stream-car stream) (sieve (stream-keep (lambda (x) (not (divisible? x (stream-car stream)))) (stream-cdr stream))))
)

(define primes (begin cNums (sieve (stream-cdr  cNums))))

(define (pair stream temp n)

    (if (<= (- (stream-car (stream-cdr temp)) (stream-car stream)) n)
        (cons-stream (list (stream-car stream) (stream-car (stream-cdr temp))) (pair stream (stream-cdr temp) n))
        (begin
            (pair (stream-cdr stream) (stream-cdr stream) n)
        )
    )
)

(define (twinPrimes n) (pair primes primes n))
