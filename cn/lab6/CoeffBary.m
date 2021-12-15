function w=CoeffBary(x,type='none')
  w=x;m=length(x)-1;
  switch type
    case 'none'
      for j=0:m
       w(j+1)=1/prod(x(j+1)-x([1:j,j+2:end]));
      endfor
    case 'echidistante'
      for j=0:m
       w(j+1)=(-1)^j*nchoosek(m,j);
      endfor
    case 'Cebisev1'
      for j=0:m
       w(j+1)=(-1)^j*sin((2*j+1)*pi/(2*m+2));
      endfor
  case 'Cebisev2'
      w(1)=1/2;w(m+1)=(-1)^m/2;
      for j=1:m-1
       w(j+1)=(-1)^j;
      endfor
  endswitch
endfunction