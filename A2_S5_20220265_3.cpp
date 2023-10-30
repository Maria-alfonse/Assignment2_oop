// File: A2_S5_20220265_3.cpp
// Purpose: splits a string according to the given delimiter and saves the split string in a vector
// Author: Maria Alfons Kamel
// Section: S5
// ID: 20220265
// TA: Maya Ahmed Kamal
// Date: 30 Oct 2023

#include <bits/stdc++.h>
using namespace std;

// This function returns a vector of strings
vector<string>split(string target, string delimiter){
    // A string variable in which we add to it every character before the delimiter
    string word ="";

    //the vector we will return
    vector<string>s;

    //this loops over every character in the target string
    for(int i=0 ; i<target.size(); i++){
        //if the character is the first character in the delimiter string it skips it by adding 
        // the size of the delimiter string and subtracting 1 because the for loop adds 1, 
        // then it adds the formed word to the vector and clears the word string to then add to it the next word
        if(target[i]==delimiter[0]){
            i += delimiter.size()-1 ;
            s.push_back(word);
            word = "";
        }else{
            //adds character by character in each word
            word += target[i];
        }
    }
    // if the word string not empty it adds it to the vector
    if(word.size()) {
        s.push_back(word);
    }
    
    //returns vector
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
