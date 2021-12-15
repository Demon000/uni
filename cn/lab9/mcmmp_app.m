function mcmmp_app(k = 3)
  clf; axis equal; axis([0 2 0 1]);
  xticks(0:0.2:2); yticks(0:0.2:1);
  grid on; hold on; set(gca, "fontsize", 15)

  i = 1
  [x, y] = ginput(1)
  noduri = []
  valori = []

  while ~isempty([x, y])
    plot(x, y, '*k', 'MarkerSize', 10);
    text(x + 0.02, y + 0.02, num2str(i), 'fontsize', 13);
    noduri(i) = x;
    valori(i) = y;
    i = i + 1
    [x, y] = ginput(1)
  endwhile

  if length(noduri) > k
    [coeficienti, err] = metoda_celor_mai_mici_patrate(noduri, valori, k)
    plot_points = linspace(min(noduri), max(noduri), 10000);
    plot_values = polyval(coeficienti, plot_points);

    plot(plot_points, plot_values);
  endif

endfunction
