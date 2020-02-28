(defun nextnode(l)
    (cond
        ((= 2 (cadr l)) (nextnode (nextnode (cddr l))))
        ((= 1 (cadr l)) (nextnode (cddr l)))
        (t (cddr l))
    )
)

(defun levels(l)
    (cond
        ((= 2 (cadr l)) (+ 1 (max (levels (cddr l)) (levels(nextnode(cddr l))))))
        ((= 1 (cadr l)) (+ 1 (levels (cddr l))))
        (t 1)
    )
)
