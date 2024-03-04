%Subsets
%subset(l1l2..l1) = {}  if list empty
%                   subset(l2l3..ln)
%                   l1  U subset(l2l3...ln).
%subset(L:list,R:list) Flow model:subset(L:i, R:O).


subset([],[]).
subset([_|T],S):-
    subset(T,S).
subset([H|T],[H|S]):-
    subset(T,S).

sum_list1([], 0).
sum_list1([H | T], Sum) :-
    sum_list1(T, RestSum),
    Sum is H + RestSum.

sumDiv(L):-
    sum_list1(L,S),
    0 is S mod 3,
    S =\=0.


wrapper(L,R):-
    findall(X,(subset(L,X),sumDiv(X)),R).
