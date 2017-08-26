// Matrix chain multiplication, see Cormen.
// 2013-02-27

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<limits.h>

#define NN 100

/*
  Problem: Compute the chain of matrix product: A[1]A[2]...A[N]
  with minimal scalar multiplications.
  Matrix A[i] has dimension p[i-1] x p[i] for i = 1..n
  So the dimensions of each matrix in the chains is:
    A[1][ p[0] x p[1] ] .. A[i][ p[i-1] x p[i]] .. A[N][ p[n-1] x p[n] ];

  Data structure:
    m[i,j] = minimum number of multiplications to compute
    s[i,j] = k, optimal cut the chain: (A[i]*..*A[k]*..*A[j]).
      row 0 and column 0 are unused.
*/

int m[NN][NN];
int s[NN][NN];
int order[NN][NN]; // order the m[i][j] is filled.

void print_matrix(int mat[NN][NN], int n, char *name){
  int i,j;
  printf("%s is:\n",name);
  printf(" "); for(j=1;j<n;j++) printf("|  %5d", j); printf("\n");
  printf("-+"); for(j=1;j<n;j++) printf("-------+", j); printf("\n");
  for(i=1;i<n;i++) {
    printf("%d:", i);
    for(j=1;j<n;j++) {
      if (j<i) printf("%8s",""); else
      printf(" %6d ", mat[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void print_optimal_cuts(int i, int j){
    if(i==j){
        printf(" A%d",i);
    }else{
        printf("(");
        print_optimal_cuts(i,s[i][j]);
        print_optimal_cuts(s[i][j]+1,j);
        printf(")");
    }
}

void print_problem(int p[], int n) {
  int i;
  for (i = 1; i < n; i++) {
    printf("A%d[%dx%d]", i, p[i-1], p[i]);
    if (i < n-1)
      printf(" ");
  }
  printf("\n");
}

int mcm(int p[], int n) {
    int i, chain_len, sno=1;
    static int problem_no=0;

    printf("\nProblem %d {{{\nInput: ", ++problem_no);
    print_problem(p, n);

    for (i = 1; i < n; i++)
      m[i][i] = 0; // cost is zero, nothing to multiply for 1 matrix.

    for (chain_len=2; chain_len<n; chain_len++) { // smallest to largest.
        for (i=1; i<=n-chain_len+1; i++) {
            int cut, j;
            j = i+chain_len-1;
            m[i][j] = INT_MAX; // Compute minimal cost of A[i]..A[j].
            for (cut=i; cut<=j-1; cut++) {
                int cost = m[i][cut] + m[cut+1][j] + p[i-1]*p[cut]*p[j];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = cut;
                    order[i][j] = sno++;
                }
            }
        }
    }
    print_matrix(order, n, "order of filling m");
    print_matrix(m, n, "m");
    print_matrix(s, n, "s");
    printf("Minimum mult is %d by:", m[1][n-1]);
    print_optimal_cuts(1,n-1); printf("\n}}}\n");
    return m[1][n-1];
}

int main(int argc, char *argv[]){
    if (argc > 1) { // usage: cmd p[0]..p[n].
      int i, problem0[100];
      printf("Reading from command line:");
      for( i = 1; i < argc; i++ ){
        problem0[i-1] = atoi(argv[i]);
        printf(" %d ", problem0[i-1]);
      }
      mcm(problem0, argc-1);
    }else{
      int problem1[] = { 10, 100, 5, 50 };
      int problem2[] = { 30,35,15,5,10,20,25 };
      int problem3[] = { 1, 2, 3, 4 };
      #define LEN(X) sizeof(X)/sizeof(X[0])
      mcm(problem1, LEN(problem1));
      mcm(problem2, LEN(problem2));
      mcm(problem3, LEN(problem3));
    }
    return 0;
}
