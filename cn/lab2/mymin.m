function x=mymin(Nrbiti=64)
if Nrbiti == 64
  x = double(1);
  exp = 1022
else
  x = single(1);
  exp = 126
endif

while exp
  x = x / 2
  exp = exp - 1;
  num2float(x)
end
