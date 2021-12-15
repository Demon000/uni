format long;

f = @(x) (cos(x) .^ 2) ./ (x .^ 2 - x + 1);
a = -1
b = 10
n = 10
points = a:0.001:b;
plot(points, f(points));

cuadratura_adaptiva = adquad2(f, a, b)
cuadratura = quad(f, a, b)
[rom, iter] = romberg_rec(f, a, b)
