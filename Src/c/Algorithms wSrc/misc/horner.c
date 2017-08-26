#include <math.h>
#include <stdio.h>
#include <stdlib.h>
int k;
double horner( double *coeffs, int n, double x ) {
    double y = 0.0, p=1;
    for(k=0;k<n;k++) {
        y += p * coeffs[k];
        p = x * p;
    }
    return y;
}
double naive( double *coeffs, int n, double x) {
  double y = 0.0;
  for(k=0;k<n;k++)
      y += pow(x,k) * coeffs[k];
  return y;
}
int main(  ) {
    double k, p[] = { 1,0,3 }; // p(x):=1+3*x^2=1+x(0+3*x));
    int lenp = (sizeof(p)/sizeof(p[0]));
    for(k=-2;k<=2;k++)
      printf( "p(%4g)= horner:%4g = naive:%4g\n",
        k, horner( p, lenp, k), naive(p, lenp, k) );
    return 0;
}
