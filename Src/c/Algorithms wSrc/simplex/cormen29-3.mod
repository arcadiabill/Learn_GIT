# Simplex example from Cormen 29.3, solved with GLPK 4.4.7
# 2013-Jan-01 Tue 09:33
# Usage: glpsol --math this_file.mod
#   Optimal value found, obj = 28, (x1,x2,x3)=(8,4,0)

var x1 >= 0;
var x2 >= 0;
var x3 >= 0;

maximize obj: 3 * x1 + 1 * x2 + 2 * x3 ;

s.t. c1:  1 * x1 + 1 * x2 + 3 * x3 <= 30;
s.t. c2:  2 * x1 + 2 * x2 + 5 * x3 <= 24;
s.t. c3:  4 * x1 + 1 * x2 + 2 * x3 <= 36;

solve;
display x1, x2, x3;
end;
