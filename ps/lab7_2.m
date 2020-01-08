display("Running.");

m = 160;
sigma = 10;
n = 300;
x = normrnd(m, sigma, 1, n);
[m1, m2] = CI_mean(x, 0.05, 10)
[m1, m2] = CI_mean2(x, 0.05)
[v1, v2] = CI_var(x, 0.05)
[p1, p2] = CI_proportion(155 < x & x < 165, 0.05)
