function [x,ni,rho]=model_sys_lin(A,b,omega,err=1e-10,p=Inf)
%omega este omis pentru Jacobi si Gauss-Seidel
M=...;
N=...;T=M\N;c=...;
rho=...; 
 while norm(T,p)>=1
   p=input("Dati alt p a.i. norm(T,p)<1:");
 endwhile
 factor=norm(T,p)/(1-norm(T,p));
 x_old=...; 
 x=...; ni=1;
while true
   x=...;
   if ...
     return;
   else  
     ...
     ...
   end 
end
