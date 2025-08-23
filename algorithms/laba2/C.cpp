#include <iostream>

void hoaraquicksort(int arr[], int start, int end) {
    int left=start;
    int right=end;
    int pivot=arr[start+rand()%(end-start)];
    while(left<=right) {
        while (arr[left]<pivot)
            ++left;
        while (arr[right]>pivot)
            --right;
        if(left<right) {
            arr[left]=arr[left]+arr[right];
            arr[right]=arr[left]-arr[right];
            arr[left]=arr[left]-arr[right];
            ++left;
            --right;
        }
        else if (left==right){
            ++left;
            --right;
        }
    }
    if(left<end)
        hoaraquicksort(arr,left,end);
    if(right>start)
        hoaraquicksort(arr,start,right);
}

int main() {
    int N;
    std::cin>>N;
    int *x=new int[N];

    for (int i=0;i<N;++i) {
        std::cin>>x[i];
    }

    hoaraquicksort (x,0,N-1);

    int a=0;
    long long sum=0;
    int i=N-1;
    while(i>=0) {
        if ((x[i]==x[i-1]||(x[i]-1)==x[i-1]) && a==0) {
            a=x[i-1];
            i-=2;
        } else if ((x[i]==x[i-1]||(x[i]-1)==x[i-1]) && a!=0) {

            sum+=1ll*a*x[i-1];
            i-=2;
            a=0;
        } else {
            --i;
        }
    }

    std::cout<<sum;

    return 0;
}
