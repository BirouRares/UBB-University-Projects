%comb(l1..ln,k)= l1 if k=1
%                comb(l2...ln,k)
%                l1 +0  comb(l2..ln, k-1) if k>1.




comb([H | _], 1, [H]).
comb([_ | T], K, C) :-
    comb(T, K, C).
comb([H | T], K, [H | C]) :-
    K > 1,
    K1 is K-1,
    comb(T, K1, C).

wrapper(L,K,R):-
    findall(X,comb(L,K,X),R).
