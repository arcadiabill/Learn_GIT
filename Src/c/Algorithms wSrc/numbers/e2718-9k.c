// e to 9000 digits from http://numbers.computation.free.fr/Constants/constants.html
int main(){int N=9009,n=N,a[9009],x;while(--n)a[n]=1+1/n;
for(;N>9;printf("%d",x)) for(n=N--;--n;a[n]=x%n,x=10*a[n-1]+x/n); return 0; }
