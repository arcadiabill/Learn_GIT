#  March 18, 2001.  MAPLE code to pivot on a tableau.
#
#  Usage:
#     Set Up: 
#      We must first specify an m x n matrix, A, of constraint coeffs.
#                            an m x 1 matrix, b, of RHS values (assumed >= 0)
#                            a  1 x n matrix, c, of objective fn coeffs.
#            and an initial value for z (the objective value), usually zero.
#
# Here, we provide two MAPLE functions:
#
#     ratios: ratios(j) determines all upper bounds for entering variable xj.
#    
#     pivot:  pivot(i,j) modifies A,b,c,z by pivoting on row i, col j and
#             prints out the result in a crude tableau format.
#
# NOTE: MAPLE has the same sort of things in its built-in "simplex" package,
#       but they might use 'dictionaries' rather than tableaux. 
with(linalg):


pivot := proc(rw, cl)  # Manipulate global variables A,b,c,z by
                       # pivoting on row rw, column cl of current tableau.
local ii,jj,pv,pivcolval;
global A, b, c, z;

pv := A[rw,cl]; # Store value of pivot before modifying it.
if pv=0 then print(`ERROR (pivot): Division by zero.\n`);
else

  ####
  ####  Perform the pivot on the data.
  ####

  # Scale the pivot row.
  for jj from 1 to coldim(A) 
   do
       A[rw,jj]  := A[rw,jj]/pv:
   od:
       b[rw,1] := b[rw,1]/pv:

  # Add appropriate multiples of pivot row to all other rows
  for ii from 1 to rowdim(A)
   do
    if ii <> rw
    then
     pivcolval := A[ii,cl]:
     for jj from 1 to coldim(A) 
      do
          A[ii,jj]  := A[ii,jj] - pivcolval*A[rw,jj]:
      od:
          b[ii,1]   :=  b[ii,1] - pivcolval*b[rw,1]:
    fi:
   od:
   
  # Add appropriate multiple of pivot row to reduced costs and obj. value.
  pivcolval := c[1,cl]:
  for jj from 1 to coldim(A) 
   do
          c[1,jj]  := c[1,jj] - pivcolval*A[rw,jj]:
   od:
          z := z - pivcolval*b[rw,1]:


   ####
   ####  Display the new tableau in floating point format.
   ####
 
   # Print column labels
   for jj to coldim(A) 
    do
     printf(`    x%1d  `,jj); 
    od;
   printf(` |    b  \n`);
   
   for jj to coldim(A) 
    do
     printf(`________`); 
    od;
   printf(`_|_________\n`);
   

   # Display current A and b values 
   for ii to rowdim(A)
   do
     for jj to coldim(A) 
      do
       printf(`  %6.2f`,evalf(A[ii,jj]) ); 
      od;
     printf(` | %6.2f \n`,evalf(b[ii,1]) );
   od;
   
   for jj to coldim(A) 
    do
     printf(`________`); 
    od;
   printf(`_|_________\n`);
   
   # Display reduced costs and current z.
   for jj to coldim(A) 
    do
     printf(`  %6.2f`,evalf(c[1,jj]) ); 
    od;
   printf(` | %6.2f \n\n\n`,evalf(z) );
   
fi:  # If pivot non-zero.
     
end;


ratios := proc(jj)  # Give ratios for entering variable x.jj
local ii;
global A, b;

for ii to rowdim(A)
 do
   if A[ii,jj] <= 0 then printf(`row %2d:  No upper bound \n`,ii);
                    else printf(`row %2d:  Upper bound = %8.4f \n`,
                                     ii, evalf(b[ii,1]/A[ii,jj]) );
   fi:
 od:
end;
