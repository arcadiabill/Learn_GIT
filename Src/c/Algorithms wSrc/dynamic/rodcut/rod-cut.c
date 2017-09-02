#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max2(A,B) (A>B? A:B)
#define N 1000

int p[N], r[N], s[N];

// initializer for prices and optimal solutions
void init() {
	memset(r, -1, sizeof(int)*N); r[0] = 0; // r = {-1,0,0...}
	p[0] = 0; p[1] = 1; p[2] = 5; p[3] = 8; p[4] = 9; p[5] = 10;
	p[6] = 17; p[7] = 17; p[8] = 20; p[9] = 24; p[10] = 30;
}

// naive exponential solution
int cut_rod(int n) {
	int q = 0, i;
	for (i = 1; i <= n; ++i)
		q = max2(q, p[i] + cut_rod(n - i));
	return q;
}

// top-down solution
int top_down_cut_rod(int n) {
  int q, i;
	if (r[n] != -1)
		return r[n];
	q = 0;
	for (i = 1; i <= n; ++i)
		q = max2(q, p[i] + top_down_cut_rod(n - i));
	return r[n] = q;
}

// bottom-up solution
int buttom_up_cut_rod(int n) {
  int i, j;
	if (r[n] != -1)
		return r[n];
	for (j = 1; j <= n; ++j) {
		int q = 0;
		for (i = 1; i <= j; ++i)
			q = max2(q, p[i] + r[j - i]);
		r[j] = q;
	}
	return r[n];
}

// bottom-up solution that maintains not only the best price
// but also the "required cut" for such solution
int extended_buttom_up_cut_rod(int n) {
  int i, j;
	if (r[n] != -1)
		return r[n];
	for (j = 1; j <= n; ++j) {
		int q = 0;
		for (i = 1; i <= j; ++i)
			if (q < p[i] + r[j - i]) {
				q = p[i] + r[j - i];
				s[j] = i;
			}
		r[j] = q;
	}
	return r[n];
}

// prints the extended method's output
void print_cut_rod_soln(int n) {
	do
		printf("%d ",  s[n]);
	while ((n -= s[n]) > 0);
}

int main() {
	int n = 10;
	init();
	// cin >> n;
  printf("%d\n", extended_buttom_up_cut_rod(n));
	print_cut_rod_soln(n);
	return 0;
}
