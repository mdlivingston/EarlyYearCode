(include "pretty.lib")

(define (main)
    (setPort (open (getElement ScamArgs 1) 'read))
    (define function (eval (readExpr) this))
    (compile function)
    (pretty function)
)

(define (compile function)
    (define dd (get '__context function))
    (define body (get 'code function))
    (define parameters (get 'parameters function))
    (define (compile-iter x)
        (if (member? x parameters)
            x
            (if (eq? 'begin x)
                x
                (if (pair? x)
                    (if (eq? (car x) 'quote) 
                        (cons (compile-iter (car x)) (cdr x))
                        (cons (compile-iter (car x)) (compile-iter (cdr x)))
                    )
                    (if (not (symbol? x))
                        nil
                        (begin
                            (define temp (catch (eval x dd)))
                           
                            (cond 
                                ((error? temp) x)
                                ((closure? temp) (compile temp ) temp)
                                (else 
                                    temp))
                        )
                    )
                )
            )
        )
    )
    (define new (compile-iter body))
    (set-car! body (car new))
    (set-cdr! body (cdr new))
)
