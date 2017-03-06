(car '(abc def ghi))
(cons 'abd '(1 2 3))
(cons 'a 'b)
(cons (car '(a b c d)) (cddr '(a b c d)))
(cons (cadr '(a b c d)) (caddr '(a b c d)))

(define (two-thirds L)
	(if (list? L)
		(if (< (length L) 3)
			L
			(cons (car L) (cons (cadr L) (two-thirds (cdddr L))))
		)
		'()
	)
)

(two-thirds '(a b c 1 2 3 x y z 7 8 9))
