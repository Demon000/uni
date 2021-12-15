  function S=evalsplinecubic(nodes,values,type,der_values,x)
   c=splinecubic(nodes,values,type,der_values);
   S=[];
   for i=1:length(x)
     if x(i)==nodes(end)
       S(i)=values(end);
     else
       poz=find(nodes>x(i),1)-1;
       X=x(i)-nodes(poz);
       S(i)=c(poz,1)+X*(c(poz,2)+X*(c(poz,3)+X*c(poz,4)));
     endif
   endfor
  endfunction