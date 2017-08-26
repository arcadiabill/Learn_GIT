#include <stdio.h>
int main()
{
    int c = 0;  // Added an initial assignment definition.

    while (c != 'x') {
        c = getchar();  // Corrected type of c to int
        if (c == 'x') // Fixed the assignment error to make it a comparison operator.
            return 0;
        switch (c) {
        case '\n':
        case '\r':
            printf("Newline\n");
            break;  // Added break statement to prevent fall-through.
        default:
            printf("%c",c);
            break;  //Added break statement to default catch, out of good practice.
        }
    }
    return 0;
}
