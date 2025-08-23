#include <iostream>
using namespace std;
int main(){
    int t;
    int a[1000][1000];
    char znak[1000][1000];
    char ravno[1000][1000];
    int n[1000];
    cin>>t;
    for (int i=0;i<t;++i){
        cin>>n[i];
        for (int j=0;j<n[i];++j)
            cin>>znak[i][j]>>ravno[i][j]>>a[i][j];
    }
    for (int i=0;i<t;++i){
        int niz=15;
        int verh=30;
        for(int j=0;j<n[i];++j){
            if (znak[i][j]=='>'&&a[i][j]>niz)
                niz=a[i][j];
            if (znak[i][j]=='<'&&a[i][j]<verh)
                verh=a[i][j];
            if (niz<=verh)
                cout<<niz<<endl;
            else
                cout<<"-1"<<endl;
        }
    }
    return 0;
}
