/*
  From http://rosettacode.org/wiki/FFT
  What: Inplace FFT and iFFT with O(n) memory usage.
  Uses complex numbers from C99 standard.

  Usage:
  $ gcc -std=gnu99 -g -o fft.exe fft.c
  $ ./fft.exe
    Data: x[0]=(1, 0), x[1]=(2, 0), x[2]=(5, 0), x[3]=(1, 0),
        x[4]=(0, 0), x[5]=(0, 0), x[6]=(0, 0), x[7]=(99, 0),

    FFT: x[0]=(108, 0), x[1]=(71.71, 62.88), x[2]=(-4, 98), x[3]=(-69.71, 72.88),
        x[4]=(-96, 0), x[5]=(-69.71, -72.88), x[6]=(-4, -98), x[7]=(71.71, -62.88),

    iFFT: x[0]=(1, 0), x[1]=(2, 0), x[2]=(5, 0), x[3]=(1, 0),
        x[4]=(0, 0), x[5]=(0, 0), x[6]=(0, 0), x[7]=(99, 0),
*/

#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <assert.h>
 
double PI = 3.14159265358979; // PI = atan2(1, 1) * 4, or USE M_PI
const double eps = 1.e-7;
typedef double complex cplx;
 
void fft_rec(cplx buf[], cplx out[], int n, int step, int inv) {
  if (step < n) {
    int i;
    fft_rec(out       , buf       , n, step * 2, inv);
    fft_rec(out + step, buf + step, n, step * 2, inv);
 
    for (i = 0; i < n; i += 2 * step) {
      int sign = inv? -1 : 1;
      cplx t = cexp(-I * PI * i * sign / n) * out[i + step];
      buf[i / 2]     = out[i] + t;
      buf[(i + n)/2] = out[i] - t;
    }
  }
}
 
int is_power_of_two(int x) {
  while (((x % 2) == 0) && x > 1) /* While x is even and > 1 */
    x /= 2;
  return (x == 1);
}

int next_power_of_2(int x) {
  // return pow(2, ceil(log(x)/log(2));
  int power = 1;
  while(power < x)
      power*=2;
  return power;
}

void fft(cplx buf[], int n, int inv) {
  cplx out[n];
  int i;
  assert(is_power_of_two(n));
  for (i = 0; i < n; i++)
    out[i] = buf[i];
  fft_rec(buf, out, n, 1, inv);
  if (inv) {
    for (i = 0; i < n; i++)
      buf[i] /= n;
  }
}

void show(char * s, cplx buf[], int n) {
  void cround(cplx *c) {
      if (fabs(cimag(*c))<eps)
        *c = creal(*c);
      if (fabs(creal(*c))<eps)
        *c = cimag(*c)*I;
  } 
  printf(s);
  for (int i = 0; i < 8; i++) {
    cround(&buf[i]);
    printf("x[%d]=",i);
    printf("(%.4g, %.4g), ", creal(buf[i]), cimag(buf[i]));
    if (i%4==3) printf("\n    ");
  }
  printf("\n");
}
 
int main() {
  cplx buf[] = {1, 2, 5, 1, 0, 0, 0, 99};
  int n = 8;

  show("Data: ", buf, n);
  fft(buf, n, 0);
  show("FFT: ", buf, n);
  fft(buf, n, 1);
  show("iFFT: ", buf, n);
 
  return 0;
}
