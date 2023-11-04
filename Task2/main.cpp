#include <bits/stdc++.h>
#include "BigReal.h"
using namespace std;

int main() {

    // Test positive addition without +
    BigReal n1("123.456");
    BigReal n2("789.012");
    BigReal sum1 = n1 + n2;
    BigReal sum1_custom = n1+ n2;
    cout << "n1 + n2 = " << sum1 << endl; // Expected: "912.468"
    cout << "n1.plus(n2) = " << sum1_custom << endl; // Expected: "912.468"

    // Test positive subtraction without -
    BigReal diff1 = n2 - n1;
    BigReal diff1_custom = n2 - n1;
    cout << "n2 - n1 = " << diff1 << endl; // Expected: "665.556"
    cout << "n2.minus(n1) = " << diff1_custom << endl; // Expected: "665.556"

    // Test negative addition without +
    BigReal n3("-12.34");
    BigReal n4("-56.78");
    BigReal sum2 = n3 + n4;
    BigReal sum2_custom = n3 + n4;
    cout << "n3 + n4 = " << sum2 << endl; // Expected: "-69.12"
    cout << "n3.plus(n4) = " << sum2_custom << endl; // Expected: "-69.12"

    // Test negative subtraction without -
    BigReal diff2 = n3 - n4;
    BigReal diff2_custom = n3 - n4;
    cout << "n3 - n4 = " << diff2 << endl; // Expected: "44.44"
    cout << "n3.minus(n4) = " << diff2_custom << endl; // Expected: "44.44"

    return 0;
}
