function A=aprox_trapez(f,a,b,n)
  l=(b-a)/n;
  x=a+l:l:b-l;
  A=(sum(f(x))*2+f(a)+f(b))*l/2;
  endfunction