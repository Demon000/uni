function L = generate_runge(a, b, m, type)
    syms X;
    x = gen_nodes(a, b, m, type);
    f = ones(1, m);
    for i = 1:m
        f(i) = 1 / (1 + x(i) ^ 2);
    endfor
    L = lagrange_baricentrica(x, f, X, type);
endfunction
