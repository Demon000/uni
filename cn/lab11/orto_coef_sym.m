function [alpha, beta] = orto_coef_sym(k, u)
n = length(k);
alpha = sym(zeros(1, n));
beta = sym([]);
for i = 1:n
    if k(i) == 0
        beta(i) = gamma(u + sym(1) / sym(2));
    elseif mod(k(i), 2) == 0
        beta(i) = k(i) / 2;
    elseif mod(k(i), 2) != 0
        beta(i) = k(i) / 2 + u;
    endif
endfor
endfunction
