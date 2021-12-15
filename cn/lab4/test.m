function [x,xx]=test()
  A=spd(6);
  b=[12;43;54;17;40;12];
  x=solve_sist_cholesky(A,b);
  
  xx=solve_sist_lup(A,b);

endfunction