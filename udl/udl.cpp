
#include <iostream>

using namespace std;

int operator"" _bin(const char* str, size_t len) {
    int ret = 0;
    for (int i = 0; i < len; i++) {
        ret = ret << 1;
        if (str[i] == '1')
            ret += 1;
    }

    return ret;
}

int main() {
    cout <<"110"_bin << endl;
    cout <<"1100110"_bin << endl;

    return 0;
}