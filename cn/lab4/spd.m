%genereaza o matrice simetrica pozitiv definita de nxn
function A=spd(n)
  B=magic(n);
  if det(B) == 0
  	print('det(B) = 0')
  endif
  A=B'*B;
endfunction
##AA=[25,15,-5;15,18,0;-5,0,11]
##R=cholesky(AA)
##R=5   3  -1
##  0   3   1
##  0   0   3
