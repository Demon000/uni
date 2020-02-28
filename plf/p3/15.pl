listn(N, N, [N]).
listn(I, N, [I|R]) :- I < N, IN is I + 1, listn(IN, N, R).
listn(N, R) :- listn(1, N, R).

sumlist([], 0).
sumlist([H|T], R) :- sumlist(T, NR), R is NR + H.

consecutivelist([_]).
consecutivelist([H1, H2|T]) :-
    H2M is H2 - 1,
    H1 = H2M,
    consecutivelist([H2|T]).

gensublists(_, [], []).
gensublists(N, [LH|LT], [LH|RT]) :- gensublists(N, LT, RT).
gensublists(N, [_|LT], RT) :- gensublists(N, LT, RT).
gensublist(N, L, R) :- gensublists(N, L, R), sumlist(R, N), consecutivelist(R).

genconsecutivesumlistn(N, R) :- listn(N, L), findall(SL, gensublist(N, L, SL), R).
