function table=dif_div_double(nodes, values, derivated_values)
    double_nodes = repelem(nodes, 2);
    len = length(double_nodes);
    table = nan(len, len);
    table(:, 1) = repelem(values, 2);
    table(1:2:end - 1, 2) = derivated_values;
    table(2:2:end - 2, 2) = diff(values) ./ diff(nodes);
    for j = 3:len
        for i = 1:len - j + 1
            table(i, j) = (table(i + 1, j - 1) - table(i, j - 1))...
                / (double_nodes(j + i - 1) - double_nodes(i));
        endfor
    endfor
endfunction
