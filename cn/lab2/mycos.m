function y=mycos(x)
x = reducereper(x); 
semn = 1;
if x > 3 * pi / 2
  x = 2 * pi - x;
  semn = -1;
elseif x > pi
  x = x - pi;
  semn = -1;
elseif x > pi / 2
  x = pi - x;
end
if x <= pi / 4
  y = cosred(x);
else
  y = sinred(pi / 2 - x);
end
y = semn * y;
