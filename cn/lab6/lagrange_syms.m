function f = lagrange_syms(xvalues, yvalues)
    syms x;
    m = length(xvalues);
 
    p = prod(x - xvalues(1:m));
    f = sym(0);
    for i = 1:m
        fn = p / (x - xvalues(i));
        f += yvalues(i) * fn / subs(fn, i);
    endfor
 
    f = expand(f);
endfunction
