(defun multiply_lists(a b)
	(cond
		((null a) ())
		((null b) ())
		(t (cons (* (car a) (car b)) (multiply_lists (cdr a) (cdr b))))
	)
)

(defun depth_list(l)
	(cond
		((null l) 0)
		((atom (car l)) (depth_list (cdr l)))
		((listp (car l)) (max (+ 1 (depth_list (car l))) (depth_list (cdr l))))
	)
)

(defun insert_in_sorted_set(e l)
	(cond
		((null l) (list e))
		((= e (car l)) l)
		((< e (car l)) (cons e l))
		(t (cons (car l) (insert_in_sorted_set e (cdr l))))
	)
)

(defun _sort_list(l r)
	(cond
		((null l) r)
		(t (_sort_list (cdr l) (insert_in_sorted_set (car l) r)))
	)
)

(defun sort_list(l)
	(_sort_list l ())
)

(defun is_in_list(e l)
	(cond
		((null l) nil)
		((= e (car l)) t)
		(t (is_in_list e (cdr l)))
	)
)

(defun intersect_sets(a b)
	(cond
		((null a) ())
		((null b) ())
		((is_in_list (car a) b)  (cons (car a) (intersect_sets (cdr a) b)))
		(t (intersect_sets (cdr a) b))
	)
)
