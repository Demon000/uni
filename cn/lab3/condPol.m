function R = condPol(n)
c = 2 .^ (- n - 1:1);
xi = roots([1, c]);
xi = fliplr(xi);

for i = 1:n
    sum = 0;
    for j = 1:n
        sum = sum + abs(c(j)) * abs(xi(i) ^ (n - j));
    endfor
 
    p_prim = polyval(polyder(c), xi(i));
    R = sum / (abs(xi(i)) * abs(p_prim));
endfor
endfunction
