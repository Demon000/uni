function x=myminsubnorm(Nrbiti=64)
%cel mai mic nr. subnormal
if Nrbiti==32
  x=single(1);
else
  x=1;
end
while x / 2 > 0
  x = x / 2
  num2float(x)
end
