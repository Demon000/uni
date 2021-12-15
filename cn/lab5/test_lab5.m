format long;

#A = rand(10, 10)
#A = A * A'

#A = spdiags(rand(10, 1), 0, 10, 10);
#A = full(A);

A = rand(10, 10);
A = A + eye(10) * 10;

b = rand(10, 1);

A
b

[SGS, ni, rho] = gauss_seidel(A, b, 1e-10, 1);
ASGS = A * SGS
ni
rho

[JS, ni, rho] = jacobi(A, b, 1e-10, 1);
AJS = A * JS
ni
rho

omega = omega_optim(A)
[SS, ni, rho] = sor(A, b, omega, 1e-10, 1);
ASS = A * SS
ni
rho
