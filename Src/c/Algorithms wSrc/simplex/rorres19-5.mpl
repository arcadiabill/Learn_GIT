# Solved with maple V.4 simplex
with(simplex);
maximize( 3*x1 -1*x2 +4*x3, {
  2*x1  -1*x2  +3*x3  <=5,
  1*x1  +4*x2  -2*x3  <=1,
  3*x1  +0*x2  +6*x3  <=4
  }, NONNEGATIVE);

  # {x1 = 7/6, x2 = 0, x3 = 1/12}  # solution

# Decimal value
evalf({x2 = 0, x1 = 7/6, x3 = 1/12});
  #  {x2 = 0, x1 = 1.166666667, x3 = .08333333333}

# Optimal value
z := subs({x2 = 0, x1 = 7/6, x3 = 1/12},  3*x1 -1*x2 +4*x3);
  #   z = 23/6

evalf(z);
  #   3.833333333
