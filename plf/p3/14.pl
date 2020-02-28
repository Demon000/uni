gens([], []).
gens([_|LT], RT) :- gens(LT, RT).
gens([LH|LT], [LH|RT]) :- gens(LT, RT).

sumlist([], 0).
sumlist([H|T], R) :- sumlist(T, NR), R is NR + H.

gensublists(_, [], []).
gensublists(N, [LH|LT], [LH|RT]) :- gensublists(N, LT, RT).
gensublists(N, [_|LT], RT) :- gensublists(N, LT, RT).
gensublist(N, L, R) :- gensublists(N, L, R), sumlist(R, N).

gensumlistn(L, S, R) :- listn(N, L), findall(SL, gensublist(N, L, SL), R). 
