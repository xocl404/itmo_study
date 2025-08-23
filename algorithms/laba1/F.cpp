#include <iostream>
using namespace std;
int main(){
    int n;
    int days[8000000];
    cin>>n;
    int sum=0;
    for (int i=0;i<n;++i) {
        cin >> days[i];
        sum+=days[i];
    }
    int k=0;
    int s=0;
    for (int i=0;i<n;++i) {
        s+=days[i];
        if(sum-s==s-days[i]){
            cout<<i;
            ++k;
            break;
        }
    }
    if(k==0)
        cout<<"-1";
    return 0;
}
