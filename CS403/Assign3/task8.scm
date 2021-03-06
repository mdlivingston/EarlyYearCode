(define (main)
        (setPort (open (getElement ScamArgs 1) 'read))
        (define Printer (readExpr))
        (define x (real (readExpr)))
        (define y (real (readExpr)))
        (print "sum returns ")
        (stream-display Printer (sum x y))
        (println)
        (print "psum returns ")
        (stream-display Printer (psum x y))
        (println)
        (print "acc-psum returns ")
        (stream-display Printer (acc-psum x y))
        (println)
        (print "super-acc-psum returns ")
        (stream-display Printer (super-acc-psum x y))
        (println)

)
(define scons cons-stream)
(define scar stream-car)
(define scdr stream-cdr)
(define (scadr s) (scar (scdr s)))
(define (scddr s) (scdr (scdr s)))
(define (scaddr s) (scar (scddr s)))
(define (scdddr s) (scdr (scddr s)))
(define (stream-map f s) (scons (f (scar s)) (stream-map f (scdr s))))
(define ints (scons 1 (stream-add ones ints)))
(define ones (scons 1 ones))

(define (stream-add s t)
    (scons (+ (scar s) (scar t)) (stream-add (scdr s) (scdr t)))
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

(define (acc s)
        (define stream0 (scar s))
        (define stream1 (scar (scdr s)))
        (define stream2 (scar (scdr (scdr s))))
        (define denom (+ stream0 (* -2 stream1) stream2))
        (cond
            ((= denom 0) (scons stream0 (acc (scdr s))))
            (else
                (scons (- stream2 (/ (* (- stream2 stream1) (- stream2 stream1)) denom)) (acc (scdr s)))
            )
        )
)

(define (sum x y)
    (define (helper x y ints)
        (scons (* (^ -1.0 (+ (scar ints) 1.0)) (/ (real x) (^ (real y) (scar ints)))) (helper x y (scdr ints)))
    )
    (helper x y ints)
)

(define (psum x y)
    (scons (scar (sum x y)) (stream-add (psum x y) (scdr (sum x y))))
)

(define (acc-psum x y)
        (acc (psum x y))
)

(define (super-acc-psum x y)
        (define (table s accel)
                (scons (scar s) (table (accel s) accel))
        )
        (table (psum x y) acc)
)
