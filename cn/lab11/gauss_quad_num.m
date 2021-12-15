function [I, x, A] = gauss_quad_num(f, n, u)
[alpha, beta] = orto_coef_num(0:n - 1, u);
J = diag(sqrt(beta(2:end)), - 1) + diag (alpha) + diag(sqrt(beta(2:end)), 1);
[V, x] = eig(J, 'vector');
A = beta(1) * V(1, :) .^ 2;
I = A * f(x);
endfunction
