include <iostream>

 long long Merge (int arr[],int left,int mid,int right) {
    int it1=0;
    int it2=0;
    long long counter = 0;
    int* result = new int [right-left];
    while (left + it1 < mid && mid + it2 < right) {
        if (arr[left + it1] <= arr[mid + it2] ) {
            result[it1+it2]=arr[left+it1];
            ++it1;
        } else {
            result[it1 + it2] = arr[mid + it2];
            counter += (1ll * (mid - it1 - left));
            ++it2;
        }
    }
    while (left + it1 < mid) {
        result[it1 + it2] = arr[left + it1];
        ++it1;
    }
    while (mid + it2 < right) {
        result [it1 + it2] = arr[mid + it2];
        ++it2;
    }
    for (int i=0;i<(it1+it2);++i) {
        arr[left+i]=result[i];
    }
    return counter;
}

long long MergeSort (int arr[],int left, int right) {
    long long counter=0;
    if (left+1>=right) {
        return counter;
    }
    int mid = (left + right) / 2;
    counter+=MergeSort(arr, left, mid);
    counter+=MergeSort(arr, mid, right);
    counter+=Merge(arr, left, mid, right);
    return counter;
}

int main() {
    int N;
    std::cin>>N;
    int* arr=new int [N];
    for (int i=0;i<N;++i) {
        std::cin>>arr[i];
    }
    long long counter = MergeSort (arr,0,N);
    std::cout<<counter;
    return 0;
}
