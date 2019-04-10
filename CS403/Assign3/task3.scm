
(define (main)
	(setPort (open (getElement ScamArgs 1) 'read))
	(define insertList (readExpr))
	(define (insert-iter tree list)
		(if (null? list)
			tree
			(begin
				(insert-iter (tree 'insert (caar list) (cadr (car list))) (cdr list))
			)
		)
	) 

	(define (walk-main tree)
		(define (walk-iter)
			(define value (tree 'next))
				(if (eq? nil value)
					()
					(begin
						(println value)
						(walk-iter)
					)
				)
		)
		(if (eq? nil (tree 'root))
			()
			(begin
				(println (tree 'walk))
				(walk-iter)
			)
		)
	)   

	(define tree (bst <))
	(insert-iter tree insertList)
	(println "First walk:")
	(walk-main tree)
	(tree 'delete (tree 'root) equal?)
	(println "Second walk:")
	(walk-main tree)
)

(define (Queue)
	(define front (list 'head))
	(define back nil)
	(define (this msg @)
		(cond
			((eq? msg 'enqueue) (enqueue @))
			((eq? msg 'dequeue) (dequeue))
			((eq? msg 'empty?) (empty?))
			(else 
				(error "queue message not understood: " msg))
		)
	)
	(define (enqueue x)
		(set-cdr! back (list x))
		(set! back (cdr back))
	)

	(define (dequeue)
		(define tmp (cadr front))
		(set-cdr! front (cddr front))
		(if (null? (cdr front))
			(set! back front)
		)
		tmp
	)
	(define (empty?)
		(eq? (cdr front) nil)
	)

	(set! back front)
	this
)

(define (setKey x val) (set-car! x val))
(define (setValue x val) (set-car! (cdr x) val))
(define (setLeftChild x val) (set-car! (cddr x) val))
(define (setRightChild x val) (set-car! (cdddr x) val))
(define (getKey list) (car list))
(define (getValue list) (cadr list))
(define (getLeftChild list) (car (cddr list)))
(define (getRightChild list) (car (cdddr list)))

(define bstree nil)
(define (bst comparator)
	(define queue (Queue))
	(define (insert key value)
		(define (insert-helper tree)
			(if (comparator key (getKey tree))
				(if (null? (getLeftChild tree))
				  	(setLeftChild tree (list key value nil nil))
				  	(insert-helper (getLeftChild tree))
				)
				(if (null? (getRightChild tree))
				  	(setRightChild tree (list key value nil nil))
				  	(insert-helper (getRightChild tree))
				)
			)
		)

		(if (null? bstree)
		  	(set! bstree (list key value nil nil))
		  	(insert-helper bstree)
		)

		(bst comparator)
	)


	(define (size)
		(define (size-iter tree total)
		  	(if (null? tree)
				0
				(+ 1 (size-iter (getLeftChild tree) (+ total 1)) (size-iter (getRightChild tree) (+ total 1)))
		  	)
		)
		(if (null? bstree)
		  	0
		  	(size-iter bstree 0)
		)
	)

	(define (find key comp)
		(define (find-iter tree)
		  	(if (null? tree)
				nil
				(if (comp (getKey tree) key)
			  		(getValue tree)
			  		(if (comparator key (getKey tree))
						(find-iter (getLeftChild tree))
						(find-iter (getRightChild tree))
			  		)
				)
		  	)
		)
		(find-iter bstree)
	)

	(define (delete key comp)
		(define (min-value parent node)
		  	(define (min-iter p n)
				(if (valid? (getLeftChild n))
			  		(min-iter n (getLeftChild n))
			  		(begin
						(define returnValue (list (getKey n) (getValue n)))
						(setLeftChild p nil)
						returnValue
			  		)
				)
		  	)
		  	(if (null? (getLeftChild (getRightChild node)))
				(begin
			  		(define returnValue (list (getKey (getRightChild node)) (getValue (getRightChild node))))
			  		(setRightChild node nil)
			  		returnValue
				)
				(min-iter node (getRightChild node))
		  	)
		)

		(define (parent-pointer node)
		
			(if (eq? nil (getLeftChild node) (getRightChild node))
				nil
				(if (eq? nil (getLeftChild node))
					(getRightChild node)
					(if (eq? nil (getRightChild node))
						(getLeftChild node)
						node
					)
				)
			)

		
		)

		(define (delete-helper parent node flag)
			(define temp (parent-pointer node))
		  	(cond
			        
				((= flag -1)
			  		(if (not (eq? temp node))
						(begin
				  			(set! bstree temp)
						)		
						(begin
				  			(define temp2 (min-value parent node))
				  			(setKey bstree (car temp2))
				  			(setValue bstree (cadr temp2))
						)
			  		)
				)
		        
				((= flag 0)
			  		(if (not (eq? temp node))
						(begin
				  			(setLeftChild parent temp)
				  		)
						(begin
				  			(define temp2 (min-value parent node))
				  			(setKey node (car temp2))
				  			(setValue node (cadr temp2))
						)
			  		)
				)
		        
				((= flag 1)
			  		(if (not (eq? temp node))
						(begin
				  			(setRightChild parent temp)
				  		)
						(begin
				  			(define temp2 (min-value parent node))
				  			(setKey node (car temp2))
				  			(setValue node (cadr temp2))
						)
			  		)
				)
		  	)
		)

	
		(define (delete-iter tree)
		  	(if (null? tree)
				nil
				(cond
			  		((and (valid? (getLeftChild tree)) (comp (getKey (getLeftChild tree)) key)) (delete-helper tree (getLeftChild tree) 0))
			  		((and (valid? (getRightChild tree)) (comp (getKey (getRightChild tree)) key)) (delete-helper tree (getRightChild tree) 1))
			  		(else
						(if (comparator key (getKey tree))
				  			(delete-iter (getLeftChild tree))
				  			(delete-iter (getRightChild tree))
						)
			  		)
				)
		  	)
		)

		(if (null? bstree)
			nil
			(if (comp (getKey bstree) key)
			  	(delete-helper bstree bstree -1)
			  	(delete-iter bstree)
			)
		)
	)

	
	(define (walk)
	        
		(define (walk-iter tree)
	        
			(if (valid? (getLeftChild tree))
				(walk-iter (getLeftChild tree))
				()
		  	)
		 
		  	((queue 'enqueue) (getValue tree))
		  	(if (valid? (getRightChild tree))
				(walk-iter (getRightChild tree))
				()
		  	)
		)

		(if (null? bstree)
		 	nil
		  	(begin
				(walk-iter bstree)
				((queue 'dequeue))
		  	)
		)
	)

	(define (root)
		(if (null? bstree)
		  	nil
		  	(getKey bstree)
		)
	)

	(define (next)
		(if ((queue 'empty?))
			nil
			((queue 'dequeue))
		)
	)

  	(define (dispatch op @)
		(cond
	  		((eq? op 'size) (size))
	  		((eq? op 'insert) (apply insert @))
	  		((eq? op 'find) (apply find @))
	  		((eq? op 'delete) (apply delete @))
	  		((eq? op 'root) (root))
	  		((eq? op 'walk) (walk))
	  		((eq? op 'next) (next))
	  		(else
				(error "UNKNOWN BST OPERATION" op))
		)
  	)
  	dispatch
)
