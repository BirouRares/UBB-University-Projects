% a

% Mathematical model:
% gcd(a, b) =
%		a, b = 0
%		b, a = 0
%		gcd(a % b, b), a >= b
%		gcd(a, b % a), a < b

% gcd(A:nr, B:nr, R:nr)

gcd(0, B, B) :- !.
gcd(A, 0, A) :- !.
% The ! at the end of the rule is a cut, which means that no further rule should be considered after this one succeeds.
gcd(A, B, R) :- A >= B,
    A1 is A mod B,
    gcd(A1, B, R), !.
gcd(A, B, R) :- A < B,
    B1 is B mod A,
    gcd(A, B1, R), !. %The ! is again used to stop further rule evaluation.

%gcd(A:input,B:input,R:output) -> flow model


% Mathematical model:
% lcm(a, b) = a * b / gcd(a, b)

% lcm(A:nr, B:nr, R:nr)


lcm(A, B, R) :-
    gcd(A, B, RGCD),  %compute the GCD of A and B -> the result is in RGCD
    R is A * B / RGCD.  % the final result is in R
%lcd(A:input, B:input, R:output)  -> flow model


lcmlist([], _, R, R). % Base case when the list is empty, return the final result R.
lcmlist([H|T], I, Acc, R) :-
    New_index is I + 1,
    lcm(H, Acc, Rnew),  % Calculate the LCM of the head element with the accumulator and store it in Rnew.
    lcmlist(T, New_index, Rnew, R). % Recursively call lcmlist with the tail of the list and the updated accumulator Rnew.

%Mathematical model:
	%0, if v=[]
	%lcmlist(l2,....,ln,index+1,lcm(l1,Acc))

%lcmlist(V-list,I-nr,Acc-nr, R-nr).
%lccmlist(V-i,I-i,Acc-i, R-o).




% b

% Model matematic:
% insert_pow(l1...ln, v, pos, index) =
%	[], n = 0
%	l1 + v + insert_pow(l2...ln, v, pos * 2, index + 1), index = pos
%	l1 + insert_pow(l2...ln, v, pos, index + 1), pos != index

% insert_pow(L:list, V:nr, POS:nr, INDEX:nr, R:list)
% insert_pow(L:input, V:input, POS:input, INDEX:i, R:output)-> flow
% model


insert_pow([], _, _, _, []).  %When the input list  is empty, there's nothing to insert, so the resulting list R is also empty.
insert_pow([H|T], V, POS, INDEX, [H, V|R]) :- POS =:= INDEX, %checks if the current position INDEX is = to the specified position POS.

    %[H|T] matches the input list L, where H is the head of the list, and T is the tail.
    %constructs the resulting list R by inserting V after H.
    New_pos is POS * 2, %update the next inserting position
    New_index is INDEX + 1,  %i++, go to the next position
    insert_pow(T, V, New_pos, New_index, R). %apply the recursive call

insert_pow([H|T], V, POS, INDEX, [H|R]) :- POS =\= INDEX, % checks if the current position INDEX is not = to the specified position POS

    New_index is INDEX + 1,  % in this case we simply go to the next position
    insert_pow(T, V, POS, New_index, R). %apply the recursive call

% insert(L:list, V:number, R:list)
% insert(V:input, V:input, R:output)-> flow model


insert(L, V, R) :- insert_pow(L, V, 1, 1, R),!.
%This is the insert predicate. It calls insert_pow with the initial position values (1 for both POS and INDEX) to insert the value V at the specified position in the list L.





