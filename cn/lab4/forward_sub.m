function x=forward_sub(A,b)
##  x(i)=(b(i)-A(i,n)*x(n)-...-A(i,i+1)*x(i+1))/A(i,i)
  x=b;
  for i=1:length(b)
    x(i) = (b(i) - A(i,1:i-1)*x(1:i-1)) / A(i,i);
  endfor
endfunction