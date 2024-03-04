; 8. Return the list of nodes of a tree of type (2) accessed inorder.



; myAppend(list11...list1n, list21...list2m) = 
;   = list21...list2m, if n = 0
;   = {list11} U myAppend(list11...list1n, list21...list2m), otherwise

(defun myAppend (list1 list2)  ; this function appends 2 lists together
  (cond
    ((null list1) list2) ; base case when the first list is empty, retunrs the second one
    (T (cons (car list1) (myAppend (cdr list1) list2)))
    ;construct the new list 
  )
)

; inorder(l1...ln) = 
;   = nil, if n = 0 
;   = myAppend(inorder(l2), myAppend(list(l1), inorder(l3))), otherwise

;This function computes the inorder traversal of a binary tree represented as a nested list.
(defun inorder(lis)
  (cond
    ((null lis) nil)  ; base case, if lis is empty return nil
    (t (myAppend (inorder (cadr lis)) (myAppend (list (car lis)) (inorder (caddr lis)))))
    ;firstly take the left child then the parent and then the right child in order to do an inorder traversal.
  )
)
;(car lis) -> the first element of the list => the root
;(cadr lis) -> the second element of the list => the left subtree
;(caddr lis) -> the third elemnt of the list => the right subtree

(format t "~%~%----------------------------------------------------------------------------------------~%~%The result for the given tree 1: ~a~%~%"  (inorder '(A (B) (C (D) (E)))))



(format t "The result for the given tree 2: ~a~%~%----------------------------------------------------------------------------------------~%~%"  (inorder '(A(B(D(E(F(G)(H(J)(K))))))(C(L(N)(Q(P)(R)))(M)))))

