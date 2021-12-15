function ccos=cosred(x)
ccos=0;
u=1;
n=0;
while u
   ccos=ccos+u;
   n++;
   u=-u*x^2/((2*n-1)*(2*n));
end
end