// What: permutations of the characters of a string.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void perm(char *input) {
    char ch[1000], temp;
    int i, k = 1, b, f, l;
    strcpy(ch, input);
    l = strlen(ch);
    for( i = 1; i <= l; i++ ) {
        k = k * i;
    }
    f = strlen( ch );
    for( i = 0; i < k; i++ ) {
        b = i % ( f - 1 );
        temp = ch[b + 1];
        ch[b + 1] = ch[b];
        ch[b] = temp;
        printf( "%s\n", ch );
    }
}

int main( ) {
    perm("abcd");
    return 0;
}
