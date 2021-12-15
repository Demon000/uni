function Q=adquad2(f,a,b,err=1e-13,fa=f(a),fc=f((a+b)/2),fb=f(b))
h=b-a; c=(a+b)/2; fd=f((a+c)/2); fe=f((c+b)/2);
Q1=h/6*(fa+4*fc+fb);
Q2=h/12*(fa+4*fd+2*fc+4*fe+fb);
if abs(Q1-Q2)<err
  Q=Q2+(Q2-Q1)/15;
else
  Q1=adquad2(f,a,c,err,fa,fd,fc);
  Q2=adquad2(f,c,b,err,fc,fe,fb);
  Q=Q1+Q2;
endif
endfunction
