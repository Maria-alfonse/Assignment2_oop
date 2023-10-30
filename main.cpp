// File: A2_S5_20220265_6.cpp
// Purpose: convert decimal to binary
// Author: Maria Alfons Kamel
// Section: S5
// ID: 20220265
// TA: Maya Ahmed Kamal
// Date: 30 Oct 2023

#include <bits/stdc++.h>
using namespace std;

static void binaryPrint(int n){
    // the non negativity condition
    if(n>-1) {
        //to check if the number reached 0 or ont yet
        if (n / 2 != 0) {
            //if n is not 0 or 0.5
            binaryPrint(n / 2);
        }
        //to print the reminder
        cout << n % 2;
    }
}
int main() {
    binaryPrint(0);
    binaryPrint(4);
    binaryPrint(27);
    return 0;
}