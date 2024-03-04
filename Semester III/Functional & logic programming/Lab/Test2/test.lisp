;Mathematical model:
;gcd(a,b) = a if b = 0
;         = gcd(b, a mod b) otherwise

;euclid algorithm
(defun gcdd(a b) ;function to calculate the gcd of two numbers
  (if (= b 0) ;if b is 0
      a ;return a
      (gcdd b (mod a b)))) ;else return the gcd of b and the remainder of a/b



;Mathematical model:
;lcmm(a,b) = 0 if a = 0 
;         = (a * b) / gcd(a, b) otherwise
(defun lcmm(a b)
  (if (zerop a) 0 (* (/ (* a b) (gcdd a b))))) ; if a is 0 return 0 else return the lcm of a and b


;Mathematical model:
;sm(list)= 1 if the list is empty
;        = if list1 is a number -> calculate lcm(list1, sm(list2,list3,.....listn))
;        = if list1 is not a number -> sm(list2,list3,.....listn)
(defun sm (lst)
  (if (null lst); if the list is null
      1
      (if (numberp (car lst)) ; if the first elemnt is a number
          (lcmm (car lst) (sm(cdr lst))) ;calculate the lcm of the first element and the recursive call for the rest of the list
          (sm (cdr lst)))))


(format T "~%~%----------------------------------------------------------------------------------------~%~%The result: ~a~%~%" (sm '(1 a 2 3 p 6 5)))


