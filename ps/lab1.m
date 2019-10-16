disp("Running");

function out=aranjamente(arr, k)
  out = [];
  eachk = nchoosek(arr, k);
  [eachk_rows, _] = size(eachk);
  for i = 1 : eachk_rows
    eachk_row = eachk(i,:);
    eachkperms = perms(eachk_row);
    out = [out; eachkperms];
  endfor
endfunction

function out=_nsumk(n, k, i, elements)
  if i == k
    if sum(elements) == n
      disp(elements);
    endif
  else
    for num = 0 : n
      new_elements = [elements, num];
      _nsumk(n, k, i + 1, new_elements);
    endfor
  endif
endfunction

function out=nsumk(n, k)
  _nsumk(n, k, 0, []);
endfunction
