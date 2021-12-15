function [alpha, beta] = orto_coef_num(k, u)
n = length(k);
alpha = zeros(1, n);
beta = [];
for i = 1:n
    if k(i) == 0
        beta(i) = gamma(u + 1 / 2);
    elseif mod(k(i), 2) == 0
        beta(i) = k(i) / 2;
    elseif mod(k(i), 2) != 0
        beta(i) = k(i) / 2 + u;
    endif
endfor
endfunction
