function [coeficienti, err] = metoda_celor_mai_mici_patrate(noduri, valori, k)
  A = vander(noduri, k + 1);
  [coeficienti, err] = rezolvare_sistem_supradeterminat(A, valori');
endfunction
