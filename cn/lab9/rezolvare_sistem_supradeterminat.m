function [c, err] = rezolvare_sistem_supradeterminat(A, f)
  [Q, R] = qr(A);
  m = size(A, 2)
  b = Q' * f;
  c = R(1:m, :) \ b(1:m);
  err = norm(b(m + 1:end));
endfunction
