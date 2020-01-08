disp("Running");

function Y=ivtdiscret(x, p, N)
  Y = zeros(1, N);
  q = cumsum(p);
  for i = 1:N
    U = unifrnd(0, 1);
    Y(i) = x(find(U <= q, 1));
  endfor
endfunction

function solve_one(n)
  clf;
  hold on;
  
  x = ivtdiscret([-1 2 3], [4/6 1/6 1/6], n);
  count = histc(x, [-1 2 3]);
  bar([-1 2 3], count / n, 0.9, "FaceColor", "y");
  bar([-1 2 3], [4/6 1/6 1/6], "FaceColor", "b");
  media_simulari = mean(x)
  media_teoretica = (3 + 2 - 4) / 6
endfunction

function solve_second(n)
  clf;
  hold on;
  
  x = normrnd(165, 10, 1, n);
  wbin = (max(x) - min(x)) / 10;
  bins = min(x):wbin:max(x);
  count = histc(x, bins);
  bar(bins, count / (n * wbin), "histc");
  f = @(x) normpdf(x, 165, 10);
  fplot(f, [min(x), max(x)], 'r');
  media_simulari = mean(x)
  media_teoretica = mean(160 <= x & x <= 170)
  proportia_teoretica = normcdf(170, 165, 10) - normcdf(160, 165, 10)
endfunction

function solve_third(n)
  x = zeros(n, 2);
  
  for i = 1:n
    k = unidrnd(8);
    if k <= 2
      x(i, :) = [-1 -1];
    elseif k == 3
      x(i, :) = [-1 1];
    elseif k == 4
      x(i, :) = [-1 2];
    elseif k == 5
      x(i, :) = [1 -1];
    elseif k >= 5 && k <= 7
      x(i, :) = [1 1];
    elseif k == 8
      x(i, :) = [1 1];
    endif
  endfor
  
  probab_sim = mean(x(:, 1) .* x(:, 2) >= 1)
  probab_teor = 2/8 + 2/8 + 1/8
  media_sim = mean(x(:, 1) .* x(:, 2))
  media_teor = -2 * 1/8 - 1 * 2/8 + 1 * 4/8 + 2 * 1/8
endfunction

function solve_forth(n)
  x = exprnd(15, 1, n);
  y = unifrnd(5, 15, 1, n);
  I = (15 <= x) & (x <= 10 + y);
  probab_sim = mean(I)
  probab_teor = (3 * exp(-5/3) - exp(-1)) / 2
endfunction
