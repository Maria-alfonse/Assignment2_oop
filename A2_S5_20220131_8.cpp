// File:A2_S5_20220131_8.cpp
// Purpose: generate patterns
// Author: Rana Esmail Zekery
// Section: S5
// ID: 20220131
// TA: eng/Nardeen Mokhless Khela and eng/Maya Ahmed Kamal
// Date: 1 novmber 2023

#include <iostream>

using namespace std;


void recursivepattern(int n,int i)
{
    if(n==1)//base case
    {

        for(int j=0; j < i; j++)
            cout<<" ";
        cout<<"*";
    }
    else
    {
        recursivepattern(n/2, i);// Recursively call the function with n/2
        cout<<'\n';
        for(int k=0; k < i; k++)//print left sides ,right
            cout<<" ";
        for(int p=0;p<n;p++)//print left stars ,right
            cout<<"* ";
        cout<<'\n';
        recursivepattern(n/2, i + n);// Recursively call the function with n/2 and updated i
    }
}

int main()
{
    recursivepattern(8,0);

}
