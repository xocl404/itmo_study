#include <iostream>
#include <string>
#include <vector>

int main() {
    int n,k,t;
    std::cin>>n>>k>>t;
    std::vector<std::string>sms(n);
    for (int i=0;i<n;++i) {
        std::cin>>sms[i];
    }
    for (int x=k-1;x>k-1-t;--x) {
        int count[256];
        for (int i=0;i<256;++i) {
            count[i]=0;
        }
        for (int i=0;i<n;++i) {
            ++count[(int)sms[i][x]+127];
        }
        int pos=0;
        std::vector<std::string>help(n);
        for (int i=0;i<256;++i) {
            while (count[i] > 0) {
                for (int j = 0; j < n; ++j) {
                    if ((int)sms[j][x]+127 == i) {
                        help[pos]=sms[j];
                        ++pos;
                        --count[i];
                    }
                }
            }
        }
        for (int i=0;i<n;++i) {
            sms[i]=help[i];
        }
    }
    for (int i=0;i<n;++i) {
        std::cout<<sms[i]<<std::endl;
    }

    return 0;
}
