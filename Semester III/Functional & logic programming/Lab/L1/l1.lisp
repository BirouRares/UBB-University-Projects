 #|(print "Input your name :")
(defvar *nam*(read))
(defun ciao (*nam*)
    (format t "Hello ~a! ~%~%" *nam*) ;t stands for 'to terminal'
)

;(setq *print-case* :capitalize)   or :uppercase  or :downcase

(ciao *nam*)



(defvar *number* 0)  ; define a variable
(setf *number* 2)    ; change the value of a variable



    |#
    
    
    
    
    
    
;a) Write a function to return the n-th element of a list, or NIL if such an element does not exist.



#|
(defun recursive_for (l n i)
  (if (null l)
      nil
      (if (= n i)
          (car l)
          (progn
            (setq l (cdr l))
            (setq i (+ i 1))
            (recursive_forl n i)))))


|#

#|
Mathematical model

recursive_for(l1....ln, n, i):
    l1 if i=n
    nil if n=0
    recursive_for(l2...ln, n,i+1)
    
|#


(defun recursive_for (lis n i)
    (cond  
        
        ((= n i) (car lis)) 
        ; if we are at the n-th element return the first elemnt in the list
        ((null lis) nil) ; if we did not find => list is empty
        
        (T (recursive_for (cdr lis) n (+ i 1))) 
        ;always evaluate the recursive funct.
        
    ))
  
(defun a (lis poz)
    (recursive_for lis poz 1))  ;call the function starting from 1

;printing the result
(format T "~%~%----------------------------------------------------------------------------------------~%~%The result for a: ~a~%~%" (a '(1 2 3 4 5 6 7 8 9 10)' 9))





;b) Write a function to check whether an atom E is a member of a list which is not necessarily linear.



#|
Mathematical model
b(l1...ln, x):
    nil if n=0
    True if atom(l1)->true and l1==x
    b(l2...ln, x) if atom(l1)->true and l1!=x
    b(l1, x) U b(l2...ln, x)  if l1 is a list
|#



(defun b(lis x)
    (cond
        ((null lis) nil) ; if the list is empty
        ((and (atom (car lis)) (equal (car lis) x)) T) 
        ;if l1 is an atom and it is = to x return true(t)
        ((atom (car lis)) (b (cdr lis) x))
        ;if l1 is an atom but it is !=x return the recursive call
        ((listp (car lis)) (or (b(car lis) x) (b (cdr lis) x ))) 
        ;if l1 is a list => call the function for the list l1 and then for the rest of the list and U the results using OR
    )
)

;printing the result: T(true) or NIL
(format T "The result for b: ~a~%~%" (b '(1 2 (3 (20 3 2 b) (3 (a b c) 5) (6 7)) 8 (9 10)) ' 10 ))
        


        
        
#|c) Write a function to determine the list of all sublists of a given list, on any level. 
 A sublist is either the list itself, or any element that is a list, at any level. Example: 
 (1 2 (3 (4 5) (6 7)) 8 (9 10)) => 5 sublists :
 ( (1 2 (3 (4 5) (6 7)) 8 (9 10)) (3 (4 5) (6 7)) (4 5) (6 7) (9 10) )  |#
 

 
#|
Mathematical model
c(l1....ln(list)):
    nil if the list is formed only by atoms
    list U (each element of list if it is a list) 
 
(defun c (lis)
    (cond
        ((atom lis) nil) ; if l1 is not a list we return nill
        (T (apply 'append (list lis) (mapcar 'c lis)))
        ;If none of the prvs conditions is true (T is a catch-all for true), execute this
        ;(list lis)- creates a list which contains only 'lis'
        ;mapcar applies the function c to each element of the list l and returns a list of the results.
        ;apply 'append -> appends the result from mapcar with the list from (list lis)
        ; the ' -> do not calculate 
        
    )
)
|#


#|
Mathematical model
c(l1...ln)
    nill if n=0
    c(l2..ln) if l1 is an atom
    {l1} U (c(l1) U c(l2...ln)), in the other case when l1 is a list
|#

(defun app(list1)

       (append (list list1) (c list1))
)

(defun c (lis)
    (cond
        ((null lis) nil) ;base case
        ((atom (car lis)) (c (cdr lis))); skipping the atom
        ((listp (car lis)) (append (list (car lis)) (append (c (car lis)) (c (cdr lis)))))
    )
)


(format T "The result for c: ~a~%~%" (app '(1 2 (3 (4 5) (6 7)) 8 (9 10))))
 
               
        
        
;d) Write a function to transform a linear list into a set.        
        
#|
Mathematical model
rm_app(l1....ln,x)
    nill if the list is empty
    rm_app(l2...ln,x) if l1=x
    l1 U rm_app(l2...ln,x) if l1!=x
|#
        
(defun rm_app (lis x)
    (cond
        ((null lis) nil) ; if the list is empty
        ((equal (car lis) x) (rm_app (cdr lis) x)) 
        ;if l1=x call recursive without x
        (T(cons(car lis) (rm_app(cdr lis) x)))
        ;If none of the above conditions is true => construct a final list in which we add l1
    )
)

#|
Mathematical model
d(l1...ln)
    nill if the list is empty
    l1 U d(rm_app(l2....ln,l1)), otherwise
|#

(defun d (lis)
    (cond
        ((null lis) nil)
        (T (cons (car lis) (d(rm_app(cdr lis) (car lis)))))
        ;construct a final list with l1 and with the result list after removing duplicates of l1
    )
)

(format T "The result for d: ~a~%~%----------------------------------------------------------------------------------------~%~%" (d  '(1 2 3 4 2 4 5 2 3 3 3 3 4 4 5 7 7 100)))

        
        
        
        
        
        
