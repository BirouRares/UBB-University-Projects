%test


%mathematical model=
%insertn(E,L,R)={ [E]if L is empty
%               { E U l1.....ln if E <= l1
%               { l1...ln U insertn(E,l2....ln)

%flow model insertn(E:i, L:i, R:o)
%insertn(E:number, L: list, R:list).

insertn(E, [], [E]). % base case
insertn(E, [H|T], [E, H|T]) :-   % if the elemnt E is less or <=  H
    E =< H. % we add it before H.
insertn(E, [H|T], [H|R]) :-
    E > H,  % if the elemnt does not fit the insert rule( is greater the H) we do not add it to the result yet.
    insertn(E, T, R).  % recursivly call the function, skiping H and going to the next element






%mathematical model:
%isort(L,R)  =% [] if the list is empty
             %  ln U insertn(l1,   l2.....ln)


%flow model isort(L: input, R: output)
%isort(L: list, R:List).


isort([], []). %base case is the input list is empty
isort([H|T], R) :- % we cycle to the list.
    isort(T, STail), %recursivly call the isort for the tail having as a result the sorted tail.
    insertn(H, STail, R).  % insert the  H if it fits the position in order for the list to be sorted.

% what we bassicly have here is a recursive call of a function until the
% last elemnt and then take




