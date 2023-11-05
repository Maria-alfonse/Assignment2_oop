// File: A2_S5_20220265_9.cpp
// Purpose: a game with teddy bears
// Author: Maria Alfons Kamel
// Section: S5
// ID: 20220265
// TA: Maya Ahmed Kamal
// Date: 31 Oct 2023

#include <bits/stdc++.h>
using namespace std;

bool solve(int n){
    int c = n%10;
    int z = (n%100)/10;
    int reduce = n - (z*c);
    // the base cases
    if(n==42){
        return true;
    }
    if(n<42){
        return false;
    }

    //if n is dividable by 5 we divide it by 5 then the new number will try to satisfy the other conditions
    if(n%5==0 && solve(n-42)){
        return true;
    }
    // else n is dividable by 4 or 3
    // let int c = n%10 which is the last digit in n
    //then let int z = n%100/10 which is the second last digit
    // we multiply them then subtract them from n
    // then the new number will try to satisfy the other condition till n reaches 42
    else if((n%4 ==0 || n%3 == 0) && solve (n - (n%10)*((n%100)/10))){
        return true;
    }

    //if n is even we divide it by 2 then we try to satisfy the other conditions till n reaches 42
    else if(n%2 == 0 && solve(n/2)){
        return true;
    }

    //if the number does not satisfy any condition
    return false;
}

int main() {
    cout<<"Enter number of bears: ";
    int n; cin>>n;
    if(solve(n)){
        cout<<"true\n";
    }else cout<<"false\n";

    return 0;
}
