function x = solve_sist_cholesky(A, b)
R = cholesky(A);
y = forward_sub(R',b);
x = backward_sub(R, y);
endfunction
