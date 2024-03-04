f([], []).
f([H|T], [H|S]) :- f(T, S).
f([H|T], S) :- H mod 2 =:= 0, f(T, S).


p(1).   q(1).   r(1).

s:-
    !,
    p(X),
    q(Y),
    r(Z),
    write(X,Y,Z),
    nl.

