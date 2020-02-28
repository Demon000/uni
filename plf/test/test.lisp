(defun find_last_element(l)
	(cond
		((null (cdr l))
			(cond
				((atom (car l)) (car l))
				((listp (car l)) (find_last_element (car l)))
			)
		)
		(t (find_last_element (cdr l)))
	)
)

(defun replace_inner_lists(l)
	(cond
		((null l) ())
		(t (mapcar (lambda (x)
			(cond
				((listp x) (find_last_element x))
				(t x)
			)
		) l))
	)
)

(write (replace_inner_lists '(a (b (c (d) e)) f (g) h (i j (k)))))
