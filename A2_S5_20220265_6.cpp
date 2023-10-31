// File: A2_S5_20220265_6.cpp
// Purpose: convert decimal to binary
// Author: Maria Alfons Kamel
// Section: S5
// ID: 20220265
// TA: Maya Ahmed Kamal
// Date: 31 Oct 2023

#include <bits/stdc++.h>
using namespace std;

void binaryPrint(int n){
    // the non-negativity condition
    if(n>-1) {
        //to check if the number reached 0 or not yet
        if (n / 2 != 0) {
            //if n is not 0 or 0.5
            binaryPrint(n / 2);
        }
        //to print the reminder
        cout << n % 2;
    }
}


void Numbers(string prefix, int k) {
    //When k reaches zero it will print the prefix and return.
    if (k == 0) {
        cout << prefix << endl;
        return;
    } else {
        //to make two recursive calls, one with '0' appended and one with '1' appended.
        //it will append zeros when k=0 it will return and append 1 to the last digit and so on
        Numbers(prefix + "0", k - 1);
        Numbers(prefix + "1", k - 1);
    }
}

int main() {
    binaryPrint(0);
    binaryPrint(4);
    binaryPrint(27);
    cout<<endl;
    Numbers("00101", 7);
    return 0;
}
