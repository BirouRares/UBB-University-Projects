%min([],_).
%min([H|T],R) :- H = R,
%    min(T,R).
%min([H|T],R) :- H > R,  !,
%    min(T,R).
%min([H|T],H):-  H < R,
%    min(T,R).

min([H|T], Min) :-
    min(T, H, Min).

min([], Min, Min).

min([H|T], CurrentMin, Min) :-
    H < CurrentMin,
    min(T, H, Min).

min([H|T], CurrentMin, Min) :-
    H >= CurrentMin,
    min(T, CurrentMin, Min).

fi([],[]).

fi(V,R) :-
    min(V,Min),
    del(V,Min,R).

del([],_,[]).

del([H|T],H,T) .

del([H|T],Min,[H|R]):-
    H\=Min,
    del(T,Min,R).



/*
 maxi(A,B)=
     a, a>b
     b, a<=b

    */


maxi(A,B,A)  :- A>B.
maxi(A,B,B) :- A=<B.


/*

*/


maxLis([],0).
maxLis([H],H).
maxLis([H1,H2|T],R) :-
    maxi(H1,H2,Maxi),
    maxLis([Maxi|T],R).


% d([],[]) = [] if list is empty
%          = l1*2 U (l2,l3,l4,...ln) other
d([],[]).
d([H|T],[NewH|R]) :-
    NewH is H*2,
    d(T,R).

%2 liste - Max de la ambele
%1 lista cu valorile *2
%1 lista cu valorile dublate- 1 = 1 1

double([],[]).
double([H|T],[H,H|R]) :- double(T,R).

w([],[],[],[]).
w(L1,L2,R1,R2) :-
    maxLis(L1,M1),
    maxLis(L2,M2),
    write('primu max:  '), write(M1), nl,
    write('al2lea max:  '), write(M2), nl,
    d(L1,R1),
    double(L2,R2).











keepEven([],[]).
keepEven([H|T],[H|R])  :- number(H),
    NewH is H mod 2,
    NewH =:= 0,
    keepEven(T,R).
keepEven([H|T],R) :-
    (atom(H); number(H), NewH is H mod 2, NewH =:=1),
    keepEven(T,R).



gcd(A,0,A) :- !.
gcd(0,B,B) :- ! .
gcd(A,B,R) :- A >=B,
    R1 is A mod B,
    gcd(R1,B,R),!.
gcd(A,B,R) :- A<B,
    R11 is B mod A,
    gcd(A,R11,R),!.


gcdList([],1).    % AI GRIJA LA ASTA
gcdList([H],H).
gcdList([H1,H2|T],R) :-
    gcd(H1,H2,M),
    gcdList([M|T],R).

pro([],0).
pro([H],H).
pro([H1,H2|T],R) :-
    P is H1*H2,
    pro([P|T],R).

prod([],1).
prod([H|T],R) :-
    prod(T,P),
    R is H*P.


wrap(L,R) :-
    keepEven(L,R),
    prod(R,P),
    gcdList(R,G),
    Rf is P/G,
    write('cmmdc is :  '), write(Rf),nl.



/*Input: lista
 * numar par de elemnte fara sa numere(true sau false)
 * min il sterge de maxim 3 ori( de la inceput)
 * de cate ori apare maximul
 * adauga dupa fiecare numar impar, dublul lui
 * sterge un numar dat de user
    */


even_list([]).
even_list([_, _|T]):- even_list(T).



mini(A,B,A) :- A =<B.
mini(A,B,B) :- A > B.

minList([],0).
minList([H],H).
minList([H1,H2|T],R) :-
    mini(H1,H2,M),
    minList([M|T],R).



nrAp([],_,0).
nrAp([H|T],H,R) :-
    nrAp(T,H,NewR),
    R is NewR+1.
nrAp([H|T],E,R) :-
    H \= E,
    nrAp(T,E,R).




insert([],[]).
insert([H|T],[H,D|R])  :-
    Rest is H mod 2,
    Rest =:= 1,
    D is H*2,
    insert(T,R).
insert([H|T],[H|R]) :-
    Rest is H mod 2,
    Rest =:= 0,
    insert(T,R).



deleten([],_,[]).
deleten([H|T],N,R) :-
    H =:= N,
    delete(T,N,R).
deleten([H|T],N,[H|R]) :-
    H =\= N,
    delete(T,N,R).




minDel([],_,_,[]).
minDel([H|T],N,C,R) :-
    H =:= N,
    C =< 3,
    NewC is C+1,
    minDel(T,N,NewC,R).

minDel([H|T],N,C,[H|R]) :-
    H =:=N,
    C>3,
    minDel(T,N,C,R).
minDel([H|T],N,C,[H|R]) :-
    H =\= N,
    minDel(T,N,C,R).



w3(L,N,Res1,Res2,Res3) :-
    evenList(L),
    maxLis(L,Max),
    nrAp(L,Max,Res),
    write('aparitii maxim:  '), write(Res),nl,
    insert(L,Res1),

    minList(L,Min),
    minDel(L,Min,1,Res2),

    deleten(L,N,Res3).

