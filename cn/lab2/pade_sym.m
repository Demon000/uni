function R=pade_sym(f,m,k,x)
  if k==0
    R=taylor(...,...,...);
  else
    c=sym(zeros(1,k)); r=c; d=c';
   %c vectorul valorilor de pe prima coloana din matricea Toeplitz
   %r vectorul valorilor de pe prima linie din matricea Toeplitz
   %d e coloana termenilor liberi din sistemul de ecuatii
  for i=0:k-1
    c(i+1)=...;
    r(i+1)=...;
    d(i+1)=-...;
  endfor
   C=toeplitz(c,r);
   b=C\d;%b=solutia sistemului cu matricea C si coloana libera d
   b=[1; b];
   a=sym(zeros(m+1,1));
  for j=0:m
    for l=0:min([j,k])
      a(j+1)=a(j+1)+...;
    endfor
  endfor
   R=(x.^(0:m)*a)/(x.^(0:k)*b);
  endif
endfunction
