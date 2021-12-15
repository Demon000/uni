 function [I,i]=romberg_rec(f,a,b,err=1e-13,NrmaxIter=25)
  T=zeros(2);
  i = 1;
  while true
    if (i > 2&& abs(T(end-1,end-1) - T(end,end)) < err)||i>NrmaxIter
      I=T(end,end);
      return;
    endif
    T(i,1) = aprox_trapez(f,a,b,2^(i-1));
    for j = 2:i
      T(i,j) = (T(i-1,j-1) - 4 ^ (j - 1)*T(i,j-1)) / (1-4^(j - 1));
    endfor
    i = i + 1;
  endwhile
endfunction
