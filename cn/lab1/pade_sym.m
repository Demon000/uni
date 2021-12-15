function R = pade_sym(f, m, k, x)
if k == 0
    R = taylor(f, 'order', m + k + 1);
else
    c = sym(zeros(1, k)); r = c; d = c';
    %c vectorul valorilor de pe prima coloana din matricea Toeplitz
    %r vectorul valorilor de pe prima linie din matricea Toeplitz
    %d e coloana termenilor liberi din sistemul de ecuatii
    for i = 0:k - 1
        c(i + 1) = subs(diff(f, x, m - i), x, 0) / factorial(m - i);
        r(i + 1) = subs(diff(f, x, m + i), x, 0) / factorial(m + i);
        d(i + 1, 1) = - subs(diff(f, x, m + i + 1), x, 0) / factorial(m + i + 1);
    endfor
 
    C = toeplitz(r, c);
    b = C \ d; %b=solutia sistemului cu matricea C si coloana libera d
    b = [1; b];
    a = sym(zeros(m + 1, 1));
 
    for i = 0:m + k
        c(i + 1) = subs(diff(f, x, i), x, 0) / factorial(i);
    endfor
 
    for j = 0:m
        for l = 0:min([j, k])
            if (l <= k)
                a(j + 1) = a(j + 1) + c(j + 1 - l) * b(l + 1);
            endif
        endfor
    endfor
 
    R = (x .^ (0:m) * a) / (x .^ (0:k) * b);
endif
endfunction
