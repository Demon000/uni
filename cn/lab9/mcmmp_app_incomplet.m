function mcmmp_app_incomplet(k = 7)
    clf; axis equal; axis([0 2 0 1]);
    xticks(0:0.2:2); yticks(0:0.2:1);
    grid on; hold on; set(gca, "fontsize", 15)
 
    i = 1
    [x, y] = ginput(1);
    X = x; Y = y;
    while ~ isempty([x, y])
        plot(x, y, '*k', 'MarkerSize', 10);
        text(x + 0.02, y + 0.02, num2str(i), 'fontsize', 13);
        i = i + 1
        [x, y] = ginput(1);
        X = [X, x]; Y = [Y, y];
    endwhile

    if length(X) <= k
        error("length(X) <= k");
    endif
    
    coef = metoda_celor_mai_mici_patrate(X, Y, k)
    sx = linspace(min(X) - 1, max(Y) + 1, 10000);
    sy = polyval(coef, sx);
    plot(sx, sy, 'LineWidth', 2);
endfunction
