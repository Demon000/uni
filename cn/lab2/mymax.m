function x=mymax(Nrbiti=64)
if Nrbiti == 64
  x = double(1);
  exp = 1023
else
  x = single(1);
  exp = 127
endif

while exp
  x = x * 2
  exp = exp - 1;
  num2float(x)
end
