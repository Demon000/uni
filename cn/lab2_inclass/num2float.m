function b=num2float(x)
if isa(x,'single')
    b=dec2bin(typecast(x,'uint32'),32);
    b=[b(1) ' ' b(2:9) ' ' b(10:end)];
else
    b=dec2bin(typecast(x,'uint64'),64);
    b=[b(1) ' ' b(2:12) ' ' b(13:end)];
end
##h=num2hex(x);
##b=[''];
##for i=1:length(h)
##    b=[b dec2bin(hex2dec(h(i)),4)];
##end
##if isa(x,'single')
##    b=[b(1) ' ' b(2:9) ' ' b(10:end)];
##else
##    b=[b(1) ' ' b(2:12) ' ' b(13:end)];
##end
