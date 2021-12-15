function x=backward_sub(A,b)
##  x(i)=(b(i)-A(i,n)*x(n)-...-A(i,i+1)*x(i+1))/A(i,i)
  x=b;
  for i=length(b):-1:1
    x(i) = (b(i) - A(i,i+1:end)*x(i+1:end)) / A(i,i);
  endfor
endfunction