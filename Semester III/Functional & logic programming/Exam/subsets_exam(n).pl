
subset([],[]).
subset([_|T],S):-
    subset(T,S).
subset([H|T],[H|S]):-
    subset(T,S).

generate_list(1,[1]).
generate_list(N,L):-
    N>1,
    helpere(1,N,L).

helpere(I,N,[I|T]):-
    I<N,
    Next is I+1,
    helpere(Next,N,T).
helpere(N,N,[N]).

sumList([],0).
sumList([H|T],S):-
    sumList(T,Rsum),
    S is H+Rsum.

checkSum(L,N):-
    sumList(L,FinalSum),
    FinalSum =:=N.


is_prime(2) :- !.
is_prime(3) :- !.
is_prime(N) :-
    N > 3,
    N mod 2 =\= 0,
    \+ has_factor(N, 3).

has_factor(N, Factor) :-
    Factor * Factor =< N,
    (N mod Factor =:= 0 ; NextFactor is Factor + 2, has_factor(N, NextFactor)).

checkPrime([]).
checkPrime([H|T]):-
    is_prime(H),
    checkPrime(T).

wrapper(N,R):-
    generate_list(N,L1),
    findall(X,(subset(L1,X),checkSum(X,N),checkPrime(X)),R).
