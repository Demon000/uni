f = @(x) sin(1 - x .^ 2) .* exp(-x .^ 2);

format long;

# Jacobi
I0 = gauss_quad_num('Jacobi', f, 1, aa = - 2 / 3, bb = - 1 / 3);
I1 = gauss_quad_num('Jacobi', f, 2, aa = - 2 / 3, bb = - 1 / 3);
n = 2;
while abs(I0 - I1) >= 1e-10 && n < 50
    I0 = I1;
    n = n + 1;
    I1 = gauss_quad_num('Jacobi', f, n, aa = - 2 / 3, bb = - 1 / 3);
end
nr_noduri_Gauss_Jacobi = n
Gauss_Jacobi = I1

w = @(x) (1 - x) .^ (- 2 / 3) .* (1 + x) .^ (- 1 / 3);
fw = @(x) f(x) .* w(x);
cuad_cu_quad = quad(fw, - 1, 1)

error_Gauss_Jacobi = abs(Gauss_Jacobi - cuad_cu_quad)
disp('')

# Cebisev 1
I0 = gauss_quad_num_ceb1(f, 1);
I1 = gauss_quad_num_ceb1(f, 2);
n = 2;
while abs(I0 - I1) >= 1e-10 && n < 50
    I0 = I1;
    n = n + 1;
    I1 = gauss_quad_num_ceb1(f, n);
end
nr_noduri_Gauss_ceb1 = n
Gauss_ceb1 = I1

w = @(x) (1 - x .^ 2) .^ (-1 / 2);
fw = @(x) f(x) .* w(x);
cuad_cu_quad = quad(fw, -1, 1)

error_Gauss_ceb1 = abs(Gauss_ceb1 - cuad_cu_quad)
disp('')

# Legendre
I0 = gauss_quad_num('Legendre', f, 1);
I1 = gauss_quad_num('Legendre', f, 2);
n = 2;
while abs(I0 - I1) >= 1e-10
    I0 = I1;
    n = n + 1;
    I1 = gauss_quad_num('Legendre', f, n);
end
nr_noduri_Gauss_Legendre = n
Gauss_Legendre = I1

cuad_cu_quad = quad(f, -1, 1)

error_Gauss_Legendre = abs(Gauss_Legendre - cuad_cu_quad)
disp('')

# Cebisev 2
I0 = gauss_quad_num('Cebisev2', f, 1);
I1 = gauss_quad_num('Cebisev2', f, 2);
n = 2;
while abs(I0 - I1) >= 1e-10 && n < 50
    I0 = I1;
    n = n + 1;
    I1 = gauss_quad_num('Cebisev2', f, n);
end
nr_noduri_Gauss_ceb2 = n
Gauss_ceb2 = I1

w = @(x) (1 - x .^ 2) .^ (1 / 2);
fw = @(x) f(x) .* w(x);
cuad_cu_quad = quad(fw, -1, 1)

error_Gauss_ceb2 = abs(Gauss_ceb2 - cuad_cu_quad)
disp('')

# Hermite
I0 = gauss_quad_num('Hermite', f, 1);
I1 = gauss_quad_num('Hermite', f, 2);
n = 2;
while abs(I0 - I1) >= 1e-10 && n < 50
    I0 = I1;
    n = n + 1;
    I1 = gauss_quad_num('Hermite', f, n);
end
nr_noduri_Gauss_Hermite = n
Gauss_Hermite = I1

w = @(x) exp(-x .^ 2);
fw = @(x) f(x) .* w(x);
cuad_cu_quad = quad(fw, -Inf, Inf)
error_Gauss_Hermite = abs(Gauss_Hermite - cuad_cu_quad)
disp('')

# Laguerre
aa = 0;
I0 = gauss_quad_num('Laguerre', f, 1, aa);
I1 = gauss_quad_num('Laguerre', f, 2, aa);
n = 2;
while abs(I0 - I1) >= 1e-10 && n < 50
    I0 = I1;
    n = n + 1;
    I1 = gauss_quad_num('Laguerre', f, n, aa);
end
nr_noduri_Gauss_Laguerre = n
Gauss_Laguerre = I1

w = @(x) x .^ (aa) .* exp(-x);
fw = @(x) f(x) .* w(x);
cuad_cu_quad = quad(fw, 0, Inf)
error_Gauss_Laguerre = abs(Gauss_Laguerre - cuad_cu_quad)
disp('')
