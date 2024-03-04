

;(format T"The result: ~a~%~%--------------------" (replace-even-values '(1 s 4 (2 f (7)))) )


(DEFUN G(L)
    (MAPCON #'LIST L)
)

(print(APPLY #'APPEND (MAPCAR #'G '(1 2))))