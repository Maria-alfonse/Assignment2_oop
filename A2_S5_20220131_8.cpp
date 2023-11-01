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