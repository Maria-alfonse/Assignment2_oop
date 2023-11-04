#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "BigReal.h"
using namespace std;


int main() {
    BigReal n1 ("90.999999999999999999999999999999999999999999999999999999999999999999999");
    BigReal n2 ("00001.111111111111111111111111111111111111111111111111111111111111111111111");
    cout << (n1 < n2) << " " << (n1 > n2) << " " << (n1 == n2) << '\n';
    BigReal n5 = n1 - n2;
    BigReal n6 = n2 - n1;
    cout << n5 << '\n' << n6;

    BigReal n3 ("90.9");
    BigReal n4 ("+=090.111111111111111111111111111111111111111111111111111111111111111111111");
    cout << (n3 < n4) << " " << (n3 > n4) << " " << (n3 == n4) << '\n';

    n1 = n2;
    cout<<(n1-n2);
    return 0;
}