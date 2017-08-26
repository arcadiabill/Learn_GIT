/* 
Generating permutations in lexicographic order
Algorithm due to Dijkstra.
C Implementation by Glenn C. Rhoads
*/

#include <stdio.h>
#include <stdlib.h>

void all_perms(int n) {
    int i, j, r, s, temp;
    int *pi;

    pi = malloc( (n+1) * sizeof(int));
    for (i=0; i <= n; i++) pi[i] = i;
    i = 1;
    while (i) {
        for (i=1; i <= n; i++)
          printf( " %2d", pi[i]);
        printf("\n");

        i = n-1; while (pi[i] > pi[i+1]) i--;
        j = n  ; while (pi[i] > pi[j]  ) j--;

        #define swap(x,y) temp=x; x=y; y=temp;
        swap(pi[i], pi[j]); // temp = pi[i]; pi[i] = pi[j]; pi[j] = temp;
        r = n;
        s = i+1;

        while (r > s) {
            swap(pi[r], pi[s]); // temp = pi[r]; pi[r] = pi[s]; pi[s] = temp;
            r--; s++;
        }
    } 
}

int main(void) {
    int n;
    printf( "Enter n: "); scanf( "%d", &n);
    all_perms(n);
    return 0;
}  
