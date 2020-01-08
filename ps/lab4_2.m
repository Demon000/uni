disp("Running");

function out=get_random_bit(p_for_one)
  out = rand() <= p_for_one;
endfunction

function out=get_six_digit_bayes_number()
  b1 = get_random_bit(0.8);
  
  if b1 == 1
    b2 = get_random_bit(0.9);
  else
    b2 = get_random_bit(0.6);
  endif
  
  if b2 == 1 && b1 == 1
    b3 = get_random_bit(0.6);
  elseif b2 == 1 && b1 == 0
    b3 = get_random_bit(0.2);
  elseif b2 == 0 && b1 == 1
    b3 = get_random_bit(0.9);
  else
    b3 = get_random_bit(0.4);
  endif
  
  if b3 == 1
    b4 = get_random_bit(0.3);
  else
    b4 = get_random_bit(0.5);
  endif
  
  if b3 == 1
    b5 = get_random_bit(0.5);
  else
    b5 = get_random_bit(0.8);
  endif
  
  if b5 == 1 && b4 == 1
    b6 = get_random_bit(0.5);
  elseif b5 == 1 && b4 == 0
    b6 = get_random_bit(0.3);
  elseif b5 == 0 && b4 == 1
    b6 = get_random_bit(0.8);
  else
    b6 = get_random_bit(0.5);
  endif

  out = bin2dec(num2str([b6, b5, b4, b3, b2, b1]));
endfunction

function generate_histogram(n)
  values = [];
  for i = 1:n
    values(i) = get_six_digit_bayes_number();
  endfor
  
  hist(values);
  bar(0:64, histc(values, 0:64) / n);
  grid on;
  set(gca, 'XLim', [0, 64], 'XTick', 0:2:64);
endfunction
