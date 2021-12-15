function [nodes, coefs, pin] = gauss_quad_sym(n, u)
    syms t;
    a = -sym(Inf);
    b = sym(Inf);
    w = t ^ (2 * u) * exp(-t ^ 2);
    pi0 = sym(0);
    pi1 = sym(1);
    [alpha, beta] = orto_coef_sym(sym(0:n - 1), u);
    for k = 1:n
        pin = (t - alpha(k)) * pi1 - beta(k) * pi0;
        pi0 = pi1;
        pi1 = pin;
    endfor
    pin = expand(pin);
    nodes = simplify(solve(pin == 0)')
    coefs = sym([]);

    for k = 1:n
        coefs(k) = simplify(int(prod(t - nodes([1:k - 1, k + 1:n])) * w, a, b) / subs(diff(pin), nodes(k)));
    endfor
endfunction
