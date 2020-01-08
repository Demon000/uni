display("Running.");

function [m1, m2]=CI_mean(x, a, s)
  n = length(x);
  z = norminv(1 - a / 2, 0, 1);
  m1 = mean(x) - z * s / sqrt(n);
  m2 = mean(x) + z * s / sqrt(n);
endfunction

function [m1, m2]=CI_mean2(x, a)
  n = length(x);
  t = tinv(1 - a / 2, n - 1);
  s = std(x);
  xn = mean(x);
  m1 = xn - t * s / sqrt(n);
  m2 = xn  + t * s / sqrt(n);
endfunction

function [p1, p2]=CI_proportion(x, a)
  n = length(x);
  z = norminv(1 - a / 2, 0, 1);
  xn = mean(x);
  s = sqrt(xn * (1 - xn));
  p1 = xn - z * s / sqrt(n);
  p2 = xn + z * s / sqrt(n);
endfunction

function [v1, v2]=CI_var(x, a)
  n = length(x);
  c1 = chi2inv(1 - a / 2, n - 1);
  c2 = chi2inv(a / 2, n - 1);
  s2 = var(x);
  v1 = (n - 1) * s2 / c1;
  v2 = (n - 1) * s2 / c2;
endfunction
