% Generate the list of all arrangements of K elements of a given list.
% Eg: [2, 3, 4] K=2 => [[2,3], [3,2], [2,4], [4,2], [3,4], [4,3]] (not necessary in this order)


% inserare(l1...ln, e) =
%	[e], n = 0
%	e U l1...ln, n >= 1
%	l1 U inserare(l2...ln, e), otherwise

% inserare(L:list, E:number, R:list)
% inserare(i, i, o)

1 2 3 4% Excludes H.The result R is then [H, ...] with E inserted at some
% position in the rest of the list.
inserare([], E, [E]).
inserare([H|T], E, [E,H|T]).
inserare([H|T], E, [H|R]) :-
         inserare(T, E, R).

% combinari([1,2,3], 2, R) will generate all combinations of size 2 from
% [1,2,3] in R.
% inserare([2,3], 1, R) will generate all lists by inserting 1 into [2,3]
% at various positions in R.



% permutari(l1...ln) =
%	[], n = 0
%	inserare(permutari(l2...ln), l1), otherwise

% permutari(L:list, R:list)
% permutari(i, o)
%
%permutari([1,2,3], R) will generate all permutations of [1,2,3] in R.

permutari([], []).
permutari([H|T], R) :-
    permutari(T, RP),
    inserare(RP, H, R).
%Recursively generate permutations for the tail of the list (T) and insert the head (H) into each permutation.




% combinari(l1...ln, k) =
%	[], k = 0
%	l1 U combinari(l2...ln, k - 1), k > 0
%	combinari(l2...ln, k), k > 0

% combinari(L:list, K:number, R:list)
% combinari(i, o)

combinari(_, 0, []).
combinari([H|T], K, [H|R]) :-
    %the combination size is greater than 0, include the head in the combination and recursively generate combinations for the tail with size K-1

    K > 0,
    NK is K - 1,
    combinari(T, NK, R).
combinari([_|T], K, R) :-
    %Exclude the head and recursively generate combinations for the tail with the same size.
    K > 0,
    combinari(T, K, R).







% aranjamente(L:list, K:number, R:list)
% aranjamente(i, i, o)

aranjamente(L, K, R) :-
    combinari(L, K, RC),
    permutari(RC, R).
%Generate combinations of size K from the list L and then generate permutations for each combination.





% allsolutions(L:list, N:number, R:list)
% allsolutions(i, i, o)

sol(L, N, R) :-
    findall(RPartial, aranjamente(L, N, RPartial), R).
%Find all solutions for arranging N elements from the list L and collect them in the list R.









