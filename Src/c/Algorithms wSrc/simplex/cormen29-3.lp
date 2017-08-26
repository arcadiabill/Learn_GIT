/*
Solve with lp-solve-ide, output: opt=28, x1=8, x2=4, x3=0
2012-Dec-31 Mon 17:57
*/

max: 3x1 +x2 + 2x3 ;
 x1 +  x2 + 3x3 <= 30;
2x1 + 2x2 + 5x3 <= 24;
4x1 +  x2 + 2x3 <= 36;

/*
Dual:
min: 30y1 + 24y2 + 36ye3;

 y1 + 2y2 + 4y3 >= 3;
 y1 + 2y2 +  y3 >= 1;
3y1 + 5y2 + 2y3 >= 2;

implicit constraints: y1,y2,y3 >= 0; 
*/
