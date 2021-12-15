function [x, ni, rho] = sor(A, b, omega, err = 1e-10, p = Inf)
M = (1 / omega) * diag(diag(A)) + tril(A, - 1);
N = M - A;
T = M \ N;
c = M \ b;
rho = max(abs(eig(T)));
while norm(T, p) >= 1
    p = input("Dati alt p a.i. norm(T,p)<1:");
endwhile
factor = norm(T, p) / (1 - norm(T, p));
x_old = zeros(size(b));
x = x_old;
ni = 1;
while true
    x = T * x_old + c;
    if norm(x - x_old, p) * factor <= err
        return;
    else
        ni = ni + 1;
        x_old = x;
    end
end
