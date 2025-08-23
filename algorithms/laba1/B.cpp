#include <iostream>
using namespace std;
int main(){
    int N,K,counter,help1,help2;
    int arr[1000];
    cin >> N >> K;
    for (int i=0;i<N;++i)
        cin>>arr[i];
    if(K>=0){
        K=K%N;
        counter=0;
        while(counter<K){
            help1=arr[N-1];
            for (int i=0;i<N;++i){
                help2=arr[i];
                arr[i]=help1;
                help1=help2;
            }
            ++counter;
        }
    }
    else{
       K=(-K)%N;
       counter=0;
       while(counter<K){
           help1=arr[0];
           for(int i=N-1;i>=0;--i){
               help2=arr[i];
               arr[i]=help1;
               help1=help2;
           }
           ++counter;
       }
    }
    for (int i=0;i<N;++i){
        cout<<arr[i]<<" ";
    }
    return 0;
}
