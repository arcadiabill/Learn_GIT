/*
  A naive recursive MCM implementation that simply
  follows the above optimal substructure property
*/

#include<stdio.h>
#include<limits.h>
 
#define NN 100
int m[NN][NN];
int s[NN][NN];
int order[NN][NN]; // order the m[i][j] is filled.

// Matrix Ai has dimension p[i-1] x p[i] for i = 1..n
int matrix_chain_order_brute(int p[], int i, int j) {
    int cut, cost, min_cost = INT_MAX;
    static int sno=1;
 
    if(i == j)
        return 0;

    // Place parenthesis at different places between first and last matrix,
    // recursively calculate cost of multiplcations for each parenthesis
    // placement and return the minimum cost
    for (cut = i; cut <j; cut++) {
        cost = matrix_chain_order_brute(p, i, cut) +
                matrix_chain_order_brute(p, cut+1, j) +
                p[i-1]*p[cut]*p[j];
 
        if (cost < min_cost) {
            m[i][j] = cost;
            s[i][j]=cut;
            order[i][j]=sno++;
            min_cost = cost;
        }
    }
    return min_cost;
}
 
int main() {
    int arr[] = {1, 2, 3, 4, 3};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Minimum number of multiplications is %d\n",
                          matrix_chain_order_brute(arr, 1, n-1));
    return 0;
}
