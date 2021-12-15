hold on; grid on;
m = 15;
a = -5;
b = 5;
fh = @(x) 1./(1 + x.^2);

X=a:0.01:b;
plot(X,fh(X));
L = {'Real'};

type = 'echidistante';
x = gen_nodes(a, b, m, type);
Lg = lagrange_baricentrica(x, fh(x), X, type);
plot(X,Lg);
L{end + 1} = ['Runge ' type];

type = 'Cebisev1';
x = gen_nodes(a, b, m, type);
Lg = lagrange_baricentrica(x, fh(x), X, type);
plot(X,Lg);
L{end + 1} = ['Runge ' type]; 

type = 'Cebisev2';
x = gen_nodes(a, b, m, type);
Lg = lagrange_baricentrica(x, fh(x), X, type);
plot(X,Lg);
L{end + 1} = ['Runge ' type]; 

legend(L);