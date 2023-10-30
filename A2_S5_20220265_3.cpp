// File: A2_S5_20220265_3.cpp
// Purpose: splits a string according to the given delimiter and saves the split string in a vector
// Author: Maria Alfons Kamel
// Section: S5
// ID: 20220265
// TA: Maya Ahmed Kamal
// Date: 30 Oct 2023

#include <bits/stdc++.h>
using namespace std;

vector<string>split(string target, string delimiter){
    string word ="";
    vector<string>s;
    for(int i=0 ; i<target.size(); i++){
        if(target[i]==delimiter[0]){
            s.push_back(word);
            word = "";
        }else{
            word += target[i];
        }
    }
    s.push_back(word);
    return s;
}

int main() {
    vector<string>s = split("10,20,30", ",");
    for(int i=0 ; i<s.size() ;i++){
        cout<<s[i]<<'\n';
    }

    cout<<'\n';

    vector<string>s1 = split("do re mi fa so la ti do", " ");
    for(int i=0 ; i<s1.size() ;i++){
        cout<<s1[i]<<'\n';
    }
    return 0;
}
