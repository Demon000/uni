function w=ponderi_baricentrice(x)
  w=x;
  for j=1:length(x)
    
    w(j)=1/prod([x(j)-x(1:j-1),x(j)-x(j+1:end)]);
  endfor
endfunction