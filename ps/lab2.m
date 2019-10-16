disp("Running");

function out=is_a_event(balls)
  out = false;
  if any(balls(:) == 'r')
    out = true;
  endif
endfunction

function out=is_b_event(balls)
  out = false;
  if all(balls == balls(1))
    out = true;
  endif
endfunction

function out=sim_solve1a()
  balls = ['r', 'r', 'r', 'r', 'r', 'a', 'a', 'a', 'v', 'v'];
  no_cases = 2000;
  no_fav_cases = 0;

  for i = 1 : no_cases
    balls_sample = randsample(balls, 3);
    if is_a_event(balls_sample)
      no_fav_cases = no_fav_cases + 1;
    endif
  endfor
  
  out = no_fav_cases / no_cases;
endfunction

function out=sim_solve1b()
  balls = ['r', 'r', 'r', 'r', 'r', 'a', 'a', 'a', 'v', 'v'];
  no_cases = 2000;
  no_fav_cases = 0;

  for i = 1 : no_cases
    balls_sample = randsample(balls, 3);
    if is_a_event(balls_sample) && is_b_event(balls_sample)
      no_fav_cases += 1;
    endif
  endfor
  
  out = no_fav_cases / no_cases;
endfunction

function out=sim_solve1c()
  balls = ['r', 'r', 'r', 'r', 'r', 'a', 'a', 'a', 'v', 'v'];
  no_cases = 2000;
  no_fav_cases_a = 0;
  no_fav_cases_a_and_b = 0;

  for i = 1 : no_cases
    balls_sample = randsample(balls, 3);
    if is_a_event(balls_sample)
      no_fav_cases_a += 1;
    endif

    if is_a_event(balls_sample) && is_b_event(balls_sample)
      no_fav_cases_a_and_b += 1;
    endif
  endfor
  
  p_a = no_fav_cases_a / no_cases;
  p_a_and_b = no_fav_cases_a_and_b / no_cases;
  out = p_a / p_a_and_b;
endfunction

function out=sim_solve1d()
  balls = ['r', 'r', 'r', 'r', 'r', 'a', 'a', 'a', 'v', 'v'];
  no_cases = 2000;
  is_last_event_a = false;
  no_fav_cases_a = 0;
  no_fav_cases_a_and_b_after_a = 0;

  for i = 1 : no_cases
    balls_sample = randsample(balls, 3);

    if is_b_event(balls_sample) && is_last_event_a
      no_fav_cases_a_and_b_after_a += 1;
    endif
    
    if is_a_event(balls_sample)
      is_last_event_a = true;
      no_fav_cases_a += 1;
    else
      is_last_event_a = false;
    endif
  endfor
  
  out = no_fav_cases_a_and_b_after_a / no_fav_cases_a;
endfunction

function out=solve2a()
  center = [0.5, 0,5];
  point = [rand(), rand()];
  radius = 0.5;
  
  out = (point(1) - center(1)) ^ 2 + (point(2) - center(2)) ^ 2 < radius ^ 2;
endfunction

function out=sim_solve2a()
  no_cases = 2000;
  no_fav_cases = 0;
  
  for i = 1 : no_cases
    if solve2a() == true
      no_fav_cases += 1;
    endif
  endfor
  
  out = no_fav_cases / no_cases;
endfunction

function out=dist(a, b)
  out = sqrt((b(1) - a(1)) ^ 2 + (b(2) - a(2)) ^ 2);
endfunction
  
function out=solve2b()
  center = [0.5, 0,5];
  point = [rand(), rand()];

  center_dist = dist(point, center);
  
  out = true;
  
  square_points = [[0, 0]; [1, 0]; [1, 1]; [0, 1]];
  [no_rows_square_points, _] = size(square_points);
  for i = 1 : no_rows_square_points;
    square_point = square_points(i, :);
    square_point_dist = dist(point, square_point);
    if square_point_dist < center_dist
      out = false;
    endif
  endfor
endfunction

function out=sim_solve2b()
  no_cases = 2000;
  no_fav_cases = 0;
  
  for i = 1 : no_cases
    if solve2b() == true
      no_fav_cases += 1;
    endif
  endfor
  
  out = no_fav_cases / no_cases;
endfunction

function out=is_acute_triangle(triangle)
  a = triangle(1, :);
  b = triangle(2, :);
  c = triangle(3, :);

  dist_a_to_b = dist(a, b);
  dist_a_to_c = dist(a, c);
  dist_b_to_c = dist(b, c);

  out = dist_a_to_b ^ 2 + dist_a_to_c ^ 2 < dist_b_to_c ^ 2;
endfunction

function out=solve2c()
  point = [rand(), rand()];
  first_triangle = [point; [0, 0]; [1, 0]];
  second_triangle = [point; [1, 0]; [1, 1]];

  out = is_acute_triangle(first_triangle) == is_acute_triangle(second_triangle);
endfunction

function out=sim_solve2c()
  no_cases = 2000;
  no_fav_cases = 0;
  
  for i = 1 : no_cases
    if solve2c() == true
      no_fav_cases += 1;
    endif
  endfor
  
  out = no_fav_cases / no_cases;
endfunction