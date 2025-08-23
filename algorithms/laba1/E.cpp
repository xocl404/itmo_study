#include <iostream>
using namespace std;
int main(){
    int N,d;
    char s[1000000];
    cin>>N;
    for (int i=0;i<N;++i)
        cin>>s[i];
        for (int i = 0; i < N / 2; ++i)
            if (s[i] != s[N - 1 - i]) {
                d = i;
                break;
            }
        int b;
    if(N%2==0) {
        for (int i = d; i >= 0; --i) {
            b = 1;
            int j = (N/2)-1;
            int x = (N/2)+1;
            while (j >=0) {
                if (j == i)
                    --j;
                if (s[j] != s[x]) {
                    b = 0;
                    break;
                }
                --j;
                ++x;
            }
            if (b == 1)
                break;
        }
        if (b == 1)
            cout << "YES";
        else {
            for (int i = N - 1 - d; i <= N; ++i) {
                b = 1;
                int j = (N/2)-2;
                int x = N - 1;
                while (j >=0) {
                    if (x == i)
                        ++x;
                    if (s[j] != s[x]) {
                        b = 0;
                        break;
                    }
                    --j;
                    ++x;
                }
                if (b == 1)
                    break;
            }
            if (b == 1)
                cout << "YES";
            else
                cout << "NO";
        }
    }
    else{
        for (int i = d; i >= 0; --i) {
            b = 1;
            int j = N/2;
            int x = (N/2)+1;
            while (j >=0) {
                if (j == i)
                    --j;
                if (s[j] != s[x]) {
                    b = 0;
                    break;
                }
                --j;
                ++x;
            }
            if (b == 1)
                break;
        }
        if (b == 1)
            cout << "YES";
        else {
            for (int i = N - 1 - d; i <= N; ++i) {
                b = 1;
                int j = (N/2)-1;
                int x = N/2;
                while (j >=0) {
                    if (x == i)
                        ++x;
                    if (s[j] != s[x]) {
                        b = 0;
                        break;
                    }
                    --j;
                    ++x;
                }
                if (b == 1)
                    break;
            }
            if (b == 1)
                cout << "YES";
            else
                cout << "NO";
        }
    }
    return 0;
}
