%Write a predicate to remove all occurrences of a certain atom from a list.



%rm(L-List, E-atom, R-Result)
%flow model (i,i,o)

rmo([],_,[]).
rmo( [H|T],E,[H|R] ) :-
    H=\=E,
    rmo(T,E,R).

rmo([H|T],E,R):-
    H=:=E,
    rmo(T,E,R).


%cnt(L-List, E - elemnt , R-Result)
%Flow model(i,i,o)

cnte([],_,0).
cnte([H|T],E,R):-
    H=:=E,
    cnte(T,E,R1),
    R is R1+1.
cnte([H|T],E,R):-
    H=\=E,
    cnte(T,E,R).



cntatm([],[]).

cntatm([H|T],[[H,RC]|R]):-
    cnte([H|T],H,RC),
    rmo(T,H,RR),
    cntatm(RR,R).

%p(1).   q(1).   r(1).
%p(2).   q(2).   r(2).
s:-
    !,
    p(X),
    q(Y),
    r(Z),
    write(X,Y,Z),
    nl.









