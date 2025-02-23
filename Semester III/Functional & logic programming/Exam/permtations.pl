insert(E,L,[E|L]).
insert(E,[H|T],[H|R]):-
    insert(E,T,R).

%perm(l1..ln)= [] is l is empty
%              insert(l1, perm(l2..ln)) otherwise
perm([],[]).
perm([H|T],R):-
    perm(T,L),
    insert(H,L,R).

diff([]).
diff([_]).
diff([H1,H2|T]):-
    abs(H1-H2) =< 3,
    diff([H2|T]).

wrapper1(L,R):-
    findall(X,(perm(L,X),diff(X)),R).
