#include <iostream>

void sort(long long r[],long long number[],long long m) {
    long long key, key_n, l;
    for (long long i = 1; i < m; ++i) {
        key = r[i];
        key_n = number[i];
        l = i - 1;
        while (l >= 0 && r[l] < key) {
            r[l + 1] = r[l];
            number[l + 1] = number[l];
            --l;
        }
        r[l + 1] = key;
        number[l + 1] = key_n;
    }
}

 int main() {
    const long long C=1000000007;
    long long n,m,k;
    std::cin>>n>>m>>k;
    long long* a=new long long[n];
    for (long long i=0;i<n;++i) {
        std::cin>>a[i];
    }
    long long* r=new long long[m];
    long long* number=new long long[m];
    for (long long i=0;i<m;++i) {
        r[i]=0;
        number[i]=i+1;
    }
    for (long long i=0;i<m;++i) {
        for (long long j=0;j<n;++j) {
            long long x;
            std::cin>>x;
            r[i] = (r[i] + (x*a[j])%C)%C;
        }
    }
    sort(r,number,m);

    for (long long i=0;i<k;++i) {
        std::cout<<number[i]<<" ";
    }

    return 0;
}
