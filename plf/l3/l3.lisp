(defun any_true(l)
	(cond
		((null l) nil)
		((car l) t)
		(t (any_true (cdr l)))
	)
)

(defun member_any_level(e l)
	(cond
		((null l) nil)
		((atom l) (cond
			((equal l e) t)
			(t nil)
		))
		((listp l) (any_true (mapcar (lambda (x)
			(member_any_level e x)
		) l)))
	)
)

(write (member_any_level -1 '(())))
(write (member_any_level -1 '(-1)))
(write (member_any_level 'a '(a 2 3 (6 7 8 ((((-1 ))))) 4 5)))
