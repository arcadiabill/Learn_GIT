#include <iostream>
#include <cstring>
using namespace std;

const int N = 1000;
int p[11];
int r[N], s[N];

#define max(A,B) (A>B? A:B)

// initializer for prices and optimal solutions
void init() {
	memset(r, -1, N);
	r[0] = 0;
	p[0] = 0;
	p[1] = 1;
	p[2] = 5;
	p[3] = 8;
	p[4] = 9;
	p[5] = 10;
	p[6] = 17;
	p[7] = 17;
	p[8] = 20;
	p[9] = 24;
	p[10] = 30;
}

// naive exponential solution
int cutRod(int n) {
	int q = 0;
	for (int i = 1; i <= n; ++i)
		q = max(q, p[i] + cutRod(n - i));
	return q;
}

// top-down solution
int topDownCutRod(int n) {
	if (r[n] != -1)
		return r[n];
	int q = 0;
	for (int i = 1; i <= n; ++i)
		q = max(q, p[i] + topDownCutRod(n - i));
	return r[n] = q;
}

// bottom-up solution
int buttomUpCutRod(int n) {
	if (r[n] != -1)
		return r[n];
	for (int j = 1; j <= n; ++j) {
		int q = 0;
		for (int i = 1; i <= j; ++i)
			q = max(q, p[i] + r[j - i]);
		r[j] = q;
	}
	return r[n];
}

// bottom-up solution that maintains not only the best price
// but also the "required cut" for such solution
int extendedButtomUpCutRod(int n) {
	if (r[n] != -1)
		return r[n];
	for (int j = 1; j <= n; ++j) {
		int q = 0;
		for (int i = 1; i <= j; ++i)
			if (q < p[i] + r[j - i]) {
				q = p[i] + r[j - i];
				s[j] = i;
			}
		r[j] = q;
	}
	return r[n];
}

// prints the extended method's output
void printCutRodSoln(int n) {
	do
		cout << s[n] << " ";
	while ((n -= s[n]) > 0);
  cout << endl;
}

int main() {
	init();
	int n = 10;
	// cin >> n;
	cout << extendedButtomUpCutRod(n) << endl;
	printCutRodSoln(n);
	return 0;
}
