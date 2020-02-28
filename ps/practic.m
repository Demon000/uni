display("Running.")

function y=solve_practic(u1_default, u2_default)
  u1 = u1_default(:);
  u2 = u2_default(:);
  
  u1_len = length(u1);
  u1_ball = randsample(u1, 1);

  u2 = [u2; u1_ball];
  u2_ball = randsample(u2, 1);
  
  y = u2_ball;
endfunction

function solve_practic_sim(n)
  u1_default = [1, 1, 2, 2, 2, 3, 3, 4];
  u2_default = [1, 1, 2, 3, 4];

  y_values = [];
  for i = 1 : n
    y = solve_practic(u1_default, u2_default);
    y_values(i) = y;
  endfor
    
  hist(y_values);
  bar(1:4, histc(y_values, 1:4) / n);
  
  mean(y_values)
  
endfunction
