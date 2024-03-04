;b) Write a function to check whether an atom E is a member of a list which is not necessarily linear.
;Mathematical model: member(E, L) = false, if L = []; true, if E = L; member(E, L), otherwise.

(defun b (E L)
    (cond
        ((null L) nil)
        ((equal E (car L)) t)
        (t (b E (cdr L)))
    )
)

;(format T "The result for b: ~a~%~%" (b '(1 2 (3 (20 3 2 b) (3 (a b c) 5) (6 7)) 8 (9 10)) ' 10 ))
(print 10)