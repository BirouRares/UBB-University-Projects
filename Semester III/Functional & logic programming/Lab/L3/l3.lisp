;Write a function that returns the sum of numeric atoms in a list, at any level.

;sum(lis)=
    ;lis , if list is a number
    ;0 , is lis is an atom
    ;sum(lis1)+sum(lis2)+....+(sum(lisn), otherwise if lis is a nested list



(defun sum(lis)
    (cond
        ((numberp lis) lis) ;check if number => add the hole list to the sum
        ((atom lis) 0)   ; check if atom => add 0 to the sum
        (T (apply '+(mapcar #'sum lis))) ;if neither of the above are true
        ;use mapcar to apply the function sum (#'sum) recursively to each element 
        ;then we use apply in order to sum up the elements using '+'
        
    )
)

(format T "~%~%----------------------------------------------------------------------------------------~%~%The result: ~a~%~%" (sum '(1 2 3 4 5 6 7 8 9 10)))


(format T "The result: ~a~%~%----------------------------------------------------------------------------------------~%~%" (sum  '(1 2 3 a (4 3) 4  (3 a))))
