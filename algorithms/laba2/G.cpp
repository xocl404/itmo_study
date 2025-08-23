#include <iostream>

void hoaraquicksort(long long arr[], long long D[], int start, int end) {
    int left=start;
    int right=end;
    int pivot=arr[start+rand()%(end-start)];
    while(left<=right) {
        while (arr[left]<pivot)
            ++left;
        while (arr[right]>pivot)
            --right;
        if (left<right) {
            std::swap(arr[left],arr[right]);
            std::swap(D[left],D[right]);
            ++left;
            --right;
        }
        else if (left==right){
            ++left;
            --right;
        }
    }
    if(left<end)
        hoaraquicksort(arr,D,left,end);
    if(right>start)
        hoaraquicksort(arr,D,start,right);
}

int main () {
    int N;
    std::cin>>N;
    long long* T = new long long[N];
    long long* D = new long long[N];
    for (int i=0;i<N;++i) {
        std::cin>>T[i]>>D[i];
    }
    hoaraquicksort (T,D,0,N-1);
    long long S=D[0]-T[0];
    for (long long i=1;i<N;++i) {
        T[i]+=T[i-1];
        S+=D[i]-T[i];
    }
    std::cout<<S;
    return 0;
}
