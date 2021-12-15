function omega=omega_optim(A)
  %RELOPT - determina valoarea optima a parametrului
  % relaxarii
  M=diag(diag(A)); %determin matricea Jacobi
  N=M-A;
  T=M \ N;
  e=eig(T);
  rt=max(abs(e)); %raza spectrala a matricei Jacobi
  omega=2/(1+sqrt(1-rt^2));
endfunction
