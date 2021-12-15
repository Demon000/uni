syms x

xvalues = -5:5;

f_real = 1 / (x ^ 2 + 1)
fh_real = function_handle(f_real)
yvalues_real = subs(f_real, xvalues)

fplot(fh_real);

f_interpolated = lagrange_syms(xvalues, yvalues_real)
yvalues_interpolatd = subs(f_interpolated, xvalues)
fh_interpolated = function_handle(f_interpolated)

fplot(fh_interpolated)
