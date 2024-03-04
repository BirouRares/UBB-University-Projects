% a

% Model matematic:
% a(l1...ln, r1...rm) =
%	l1...ln, m = 0
%	r1...rn, n = 0
%	l1 U a(l2...ln, r1...rm), l1 < r1
%	r1 U a(l1...ln, r2...rm), l1 > r1
%	a(l1...ln, r2...rm), l1 = r1

% a(L:list, R:list, R:list)
% flow model: a(input, input, output)


%HL-head of the left list
%HR-head of the right list
%TL-tail of the left list
%TR-tail of the right list
a(L, [], L).  %base case
a([], R, R).  %base case

a([HL|TL], [HR|TR], [HL|R]) :- HL < HR, %in this case we take HL and put it in R
    a(TL, [HR|TR], R).%recursive call with the TL and the right list, with the result in R

a([HL|TL], [HR|TR], [HR|R]) :- HL > HR,%in this case we take HR and put it in R
    a([HL|TL], TR, R).%recursive call with the left list and TR, with the result in R

a([HL|TL], [HR|TR], R) :- HL = HR,% in this case we do not add any elemnts to the result
   a([HL|TL], TR, R).%continue with the remaining elemnts







% b

% Model matematic:
% b(l1...ln) =
%	[], n = 0
%	a(l1, b(l2...ln)), is_list(l1) = True
%	b(l2...ln), otherwise

% b(L:list, R:list)
% flow model: b(input, output)

b([], []).%base case

% is_list check if the head is a list
% ! - is used to cut which means that we do not have other alternatives
% in this part of the code
b([H|T], R) :- is_list(H), !,
    b(T, RH),  %recursively processes the tail of the input list and store the result in RH(Result head)
    a(H, RH, R). %use a) to merge the sublist H  and RH in order to get R

b([_|T], R) :-%when the head is not a list we skip the elements
    b(T, R).
