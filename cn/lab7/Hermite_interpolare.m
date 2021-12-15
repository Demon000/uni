function [H, dH] = Hermite_interpolare(x, f, df, X)
    c = dif_div_duble(x, f, df)(1, :);
    z = repelem(x, 2);
    H = [];
    dH = [];
    for k = 1:length(X)
        DP = 0;
        P = 1;
        H(k) = c(1);
        dH(k) = 0;
        for i = 1:length(z) - 1
            DP = DP * (X(k) - z(i)) + P;
            P = P * (X(k) - z(i));
            H(k) = H(k) + P * c(i + 1);
            dH(k) = dH(k) + DP * c(i + 1);
        endfor
    endfor
end
