#include <stdio.h>
#include <string.h>

void swap(void *vp1, void *vp2, int size);

int main()
{
   short vp1 = 44;
   int vp2 =  5;
   
   printf("Size of int: %d  Size of short: %d\n", sizeof(int),sizeof(short));
   printf("vp1:%5d,  vp2:%5d\n", vp1, vp2);
   swap(&vp1, &vp2, sizeof(int));
   printf("vp1:%5d,  vp2:%5d\n", vp1, vp2);

}

void swap(void *vp1, void *vp2, int size)
{
   char buffer[size];
   
   memcpy(buffer, vp1, size);
   memcpy(vp1,    vp2, size);
   memcpy(vp2, buffer, size);
}
