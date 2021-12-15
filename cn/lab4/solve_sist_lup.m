function x = solve_sist_lup(A, b)
[L, U, P] = lup(A);
rhs = P * b;
y = forward_sub(L, rhs);
x = backward_sub(U, y);
endfunction
