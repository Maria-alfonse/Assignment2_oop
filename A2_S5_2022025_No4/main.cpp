// File: A2_S5_2022025_No4.cpp
// Purpose: Get prime numbers using Sieve Of Eratosthenes algorthim.
// Author: Ahmed Abdelaziz Ahmed.
// Section: S5
// ID: 20220025
// TA: Maya Ahmed Kamal
// Date: 26 Oct 2023
#include <iostream>
#include <vector>
#include <map>


using namespace std;
void SieveOfEratosthenes(){
    map<int,bool>IsPrime;
int n;
cout<<"You want the range between 2 and What? \n";
cin >>n;
    for (int i = 2; i <= n; ++i) {
        IsPrime.insert({i, true});
    }
    for (int i = 2; i < n ; ++i) {
        for (int j = i*i; j <= n; j+=i) {
            while(j%i == 0 ){
                IsPrime[j] = false;
                break;
            }
        }
    }
    for(auto X : IsPrime){
        if(X.second){
            cout<<X.first<<" ";
        }
    }


}
int main() {
    SieveOfEratosthenes();
}