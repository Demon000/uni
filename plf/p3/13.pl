genallvalues(I, N, R) :- R is I; I \= N, NI is I + 1, genallvalues(NI, N, R).
genallvalues(N, R) :- genallvalues(1, N, R).

notsameconsecutivelist([_]).
notsameconsecutivelist([H1, H2|T]) :-
    H1 \= H2,
    notsameconsecutivelist([H2|T]).

genlistvaluess(I, N, C, [HC|R]) :- genallvalues(C, HC), NI is I + 1, NI \= N, genlistvaluess(NI, N, C, R).
genlistvaluess(I, N, C, [HC]) :- genallvalues(C, HC), NI is I + 1, NI = N.
genlistvalues(N, C, R) :- genlistvaluess(0, N, C, R), notsameconsecutivelist(R).

gencountrycolors(N, M, RL) :- findall(R, genlistvalues(N, M, R), RL). 
