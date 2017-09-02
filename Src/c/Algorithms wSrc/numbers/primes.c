// primes upto 100k from http://numbers.computation.free.fr/Constants/constants.html
int main(){int a[100000],i=1e5,n=i,p=1;while(--i)a[i]=1;
while(++p<n)for(a[p]?printf("%d ",i=p):0;p<4e4&&i*p<n;a[i++*p]=0); return 0; }
