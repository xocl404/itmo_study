#include <iostream>
using namespace std;
int main(){
    short N;
    int x[10000];
    cin>>N;
    for (int i=0;i<N;++i)
        cin>>x[i];
    int key,j;
    for (int i=1;i<N;++i){
        key=x[i];
        j=i-1;
        while(j>=0 && x[j]>key){
            x[j+1]=x[j];
            --j;
        }
        x[j+1]=key;
    }
    for (int i=0;i<N;++i)
        cout<<x[i]<<" ";
    return 0;
}
