(defun del-even-length-sublists (lst)
  (cond
    ((null lst) nil)
    ((atom (car lst))
     (cons (car lst) (del-even-length-sublists (cdr lst))))
    ((evenp (length (car lst)))
     (del-even-length-sublists (cdr lst)))
    (t
     (cons (del-even-length-sublists (car lst))
           (del-even-length-sublists (cdr lst))))))

;; Example usage:
;(setq input-list '((2 3 4) (6 (7 8) ((7 9) 8)) (6 8) 9))
;(print (del-even-length-sublists input-list)) ; Output: ((2 3 4) (6 (8)) 9)


(format T "~%~%----------------------------------------------------------------------------------------~%~%The result: ~a~%~%" (del-even-length-sublists '((2 3 4) (6 (7 8) ((7 9) 8)) (6 8) 9)))