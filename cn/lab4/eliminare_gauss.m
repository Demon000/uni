function x=eliminare_gauss(A,b)
  A=[A,b]; ...concatenare - pune coloana b la final
  for k=1:length(b)-1
    [val,index] = max(abs(A(k:n,k)));
    index = index + k - 1;
    if(index!=k)
      A([k,index],k:end)=A([index,k],k:end);
    endif
    for i=k+1:length(b)
      m=A(i,k)/A(k,k); ...A(k,k) != 0, pt ca det != 0
      A(i,k:end)=A(i,k:end)-A(k,k:end)*m;
    endfor
  endfor
  
endfunction