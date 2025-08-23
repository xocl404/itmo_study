#include <iostream>

using namespace std;

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
    cin>>N;
    int *arr=new int[N];
    for (int i=0;i<N;++i){
        cin>>arr[i];
    }
    hoaraquicksort(arr,0,N-1);
    for (int i=0;i<N;++i){
        cout<<arr[i]<<" ";
    }

    return 0;
}
