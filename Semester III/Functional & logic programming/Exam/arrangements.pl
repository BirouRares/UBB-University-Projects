%  Generate the list of all arrangements of K elements of a given list.
% Eg: [2, 3, 4] K=2 => [[2,3], [3,2], [2,4], [4,2], [3,4], [4,3]] (not necessary in this order)

% insert(l1l2...ln, elem) =
% = {elem} U l1l2...ln
% = {l1} U insert(l2...ln, elem)

% insert(L:list, E:element, R:list)
% (i,i,o)


insert(L,E,[E|L]).
insert([H|T],E,[H|R]):-
    insert(T,E,R).



% arr(l1l2...ln, k) =
% = l1, if k = 1
% = arr(l1l2...ln, k), if k >= 1
% = insert(l1, arr(l2...ln, k - 1)), if k > 1

% arr(L:list, K:number, R:list)
% (i,i,o)



arr([H|_],1,[H]).
arr([_|T],K,R):-
    arr(T,K,R).

arr([H|T],K,Res):-
    K>1,
    K1 is K-1,
    arr(T,K1,R),
    insert(R,H,Res).


product([],1).
product([H|T],P):-
    product(T,P1),
    P is P1*H.


cal(L,K,P,R):-
    findall(RPartial,(arr(L,K,RPartial),product(RPartial,P)),R).
