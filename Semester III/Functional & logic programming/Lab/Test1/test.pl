%test


%Mathematical model.

sortn([],[],[]).  %the base case
sortn([H1|T1],[H2|T2],[H1,H2|R]) :-
    H1 > H2,
    sortn(T1,T2,R).
sortn([H1|T1],[H2|T2],[H2,H1|R]) :-
    H1 =< H2,
    sortn(T1,T2,R).

insert(



