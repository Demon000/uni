Metoda monte carlo 1: function int=MC1(g,a,b,n)
int=(b-a)*mean(g(unifrnd(a,b,1,n)));
endfunction
Metoda monte carlo 2: function int=MC2(g,a,b,n)
x=unifrnd(a,b,1,n);
M=max(g(x));
y=unifrnd(0,M,1,n);
int=(b-a)*M*mean(y<=g(x))
clf;hold on;axis equal;
plot(x(y<=g(x)),y(y<=g(x)),'.k','markersize',15);
fplot(g,[a,b]);
axis([a,b,-0.1 M + 0.1]);
endfunction

1.I
function lab6P1i(n)
x=normrnd(1,1,1,n);
y=normrnd(3,1,1,n);
Vx=var(x); #returnează variația elementelor lui A de-a lungul primei dimensiuni a tabloului a căror dimensiune nu este egală cu 1
Vy=var(y);
Exy=mean(x.*y)
R=corrcoef(x,y); #Calculați matricea coeficientului de corelație între doi vectori aleatori distribuiți în mod normal
rho=corrcoef(1,2)
prb_sim=mean(x<2&y>1)
prb_teor=normcdf(2,1,1)*(1-normcdf(1,3,1))
endfunction

II
function lab6P1ii(n)
x=normrnd(1,1,1,n);
y=3*x+1;
Vx=var(x);
Vy=var(y);
Exy=mean(x.*y)
R=corrcoef(x,y);
rho=R(1,2)
prb_sim=mean(x<2&y>1)
prb_teor=normcdf(2,1,1)-normcdf(0,1,1)
endfunction

2.I
function lab6P2i(n)
g=@(x) exp(-x.^2);%pt i #.^ ridicare la patrat
g_1=MC1(g,-2,2,n)
g_2=MC2(g,-2,2,n)
endfunction


II
function lab6P2ii(n)
g=@(x) abs(sin(exp(x)));%pt ii
g_2=MC2(g,-1,3,n)
endfunction

III
function lab6P2iii(n)
g=@(x) x.^2./(1+x.^2).*(-1<=x&x<=0)+sqrt(2*x-x.^2).*(0<=x&x<=2);%pt iii
g_3=quadcc(g,-2,2)
g_2=MC2(g,-2,2,n)
endfunction




