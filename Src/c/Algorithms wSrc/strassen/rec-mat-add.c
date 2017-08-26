// Recursive matrix addition, prelude to strassen.
// 2013-Feb-15 Fri 12:27

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define M 2
#define N (1<<M)
typedef int mat[N][N];
typedef struct { int ra, rb, ca, cb; } corners;

void set(mat A, corners a, int k){
  int i,j;
  for(i=a.ra;i<a.rb;i++)
    for(j=a.ca;j<a.cb;j++)
      A[i][j] = k;
}

void print(mat A, corners a, char *name) {
  int i,j;
  printf("%s = {\n",name);
  for(i=a.ra;i<a.rb;i++){
    for(j=a.ca;j<a.cb;j++)
      printf("%4d, ", A[i][j]);
    printf("\n");
  }
  printf("}\n");
}

void print_corners(corners a, char *name, char*nl) { // for debugging.
  printf("%s[%d..%d,%d..%d]%s", name, a.ra, a.rb, a.ca, a.cb, nl);
}

void find_corner(corners a, int i, int j, corners *b) {
  int rm = a.ra + (a.rb - a.ra)/2 ;
  int cm = a.ca + (a.cb - a.ca)/2 ;
  *b = a;
  if (i==0)  b->rb = rm;     // top rows
  else       b->ra = rm;     // bot rows
  if (j==0)  b->cb = cm;     // left cols
  else       b->ca = cm;     // right cols
  assert( !(b->rb < b->ra || b->cb < b->ca) );
  // if( b->rb < b->ra || b->cb < b->ca )
  // __asm int 3;
}

void add(mat A, mat B, mat C, corners a, corners b, corners c ) {
  int i,j;
  if(a.rb - a.ra == 1) {
    C[ c.ra ][ c.ca ] = A[ a.ra ][ a.ca ] + B[ b.ra ][ b.ca ];
    return;
  }
  for(i=0;i<2;i++) {
     for(j=0;j<2;j++) {
        corners c = a;
        find_corner(a, i, j, &c);
        add(A, B, C, c, c, c);
     }
  }
}

int main() {
  mat A, B, C;
  corners ai = {0,N,0,N};
  corners bi = {0,N,0,N};
  corners ci = {0,N,0,N};
  set(A,ai,1);
  set(B,bi,2);
  print(A, ai, "A");
  print(B, bi, "B");
  add(A,B,C, ai, bi, ci);
  print(C, ci, "C");
  return 0;
}
