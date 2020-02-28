1 Bernoulli
function out=lab3P1(p,l,k)
out=randsample([0,1],l*k,true,[1-p,p]);
out=reshape(out,l,k);
endfunction

2.A Bino
clf;
p=0.3; n=5; m=3;
x1=binornd(n,p,1,m);
N1=histc(x1,0:n);
subplot(1,2,1); hold on; title('Binornd');#The first two inputs to subplot indicate the number of plots in each row and column. The
third input specifies which plot is active. For example, create four plots in a 2-by-2 grid
within a figure window.

bar(0:n,N1/m,'hist','FaceColor','b');
bar(0:n,binopdf(0:n,n,p),'FaceColor','y'); #binopdf=calculează funcția de densitate a probabilității binomiale la fiecare dintre valorile din x folosind numărul corespunzător de încercări în n și probabilitatea de succes pentru fiecare încercare din p.
legend('estimated probabilities','theoretical probabilities');
x2=lab3P22(p,n,m);
N2=histc(x2,0:n);
subplot(1,2,2); hold on; title('My binornd');
bar(0:n,N2/m,'hist','FaceColor','b');
bar(0:n,binopdf(0:n,n,p),'FaceColor','y');
legend('estimated probabilities','theoretical probabilitie');

B
function out=lab3P22(p,n,m)
aux=lab3P1(p,n,m)
out=sum(aux,1); #creaza o matrice pe o coloana cu suma elementelor de pe acele randuri;aduna toate elementele de pe fiecare rand
endfunction

3.A Geo
clf;
p=0.3; n=5; m=3;
x1=geornd(p,1,m);
n = max(x1);
N1=histc(x1,0:n);
subplot(1,2,1); hold on; title('Binornd');
bar(0:n,N1/m,'hist','FaceColor','b');
bar(0:n,geopdf(0:n,p),'FaceColor','y');
legend('estimated probabilities','theoretical probabilities');
x2=lab3P32(p,m);
n=max(x2);
N2=histc(x2,0:n);
subplot(1,2,2); hold on; title('My binornd');
bar(0:n,N2/m,'hist','FaceColor','b');
bar(0:n,geopdf(0:n,p),'FaceColor','y');
legend('estimated probabilities','theoretical probabilities');

B
function out=lab3P32(p,m)
out=zeros(1,m);
for i=1:m
    while ~lab3P1(p,1,1)
        out(i)+=1;
end
end
endfunction

4
function poz = axa (p,k,m)
poz=zeros(m,k+1);
c=zeros(1,m);
for i=1:m
  stg=0;
  for j=2:k+1
    pas = 2 * bernoulli(p,1,1)-1;
    poz(i,j)=poz(i,j-1)+pas;
    if pas==1 && stg==0
      c(i)=c(i)+1;
    else
      stg=2;
    end
  end
end
endfunction

function out=bernoulli(p)
out=rand<p;
end


