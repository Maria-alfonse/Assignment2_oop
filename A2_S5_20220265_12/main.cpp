// File: A2_S5_20220265_6.cpp
// Purpose: Phishing Scanner, scan a file for scam words.
// Author: Maria Alfons Kamel
// Section: S5
// ID: 20220265
// TA: Maya Ahmed Kamal
// Date: 31 Oct 2023

#include <bits/stdc++.h>
using namespace std;

//This function is to convert a string to a lower case
string to_lower(string s){
    for(int i=0 ; i<s.size() ; i++){
        //if the character is in the range of the upper case ascii
        if(s[i]>=65 && s[i]<=90 ){
            //convert it lo lower by adding 32
            s[i]+=32;
        }
    }
    return s;
}

//map to store the scam words and there points
map<string, int>scam_words = {
        {"credit card", 3},
        {"password", 3},
        {"social security", 3},
        {"bank", 2},
        {"account", 2},
        {"verify", 2},
        {"urgent", 2},
        {"suspicious", 2},
        {"account information", 2},
        {"click here", 2},
        {"free", 1},
        {"prize", 1},
        {"winner", 1},
        {"inheritance", 1},
        {"refund", 1},
        {"lottery", 1},
};

//this function takes the file name as a string
void scanner(string name){
    //to open the file for reading and saves it in a variable named file
    ifstream file (name);

    //to check if the file is opened successfully and if not it allows the user to reEnter the file name
    while (!file) {
        cout<< "Error: Unable to open file " << name << "\nPlease reEnter the name: ";
        cin>>name;
        //attempt to open the new file name
        file.open(name);
    }

    //string to save in it each line in the file and a cnt variable to count the total points of the scam words
    string line;
    int cnt=0;

    //while loop to loop over each line and saves it in line variable
    while(getline(file, line)){

        //to convert the whole line to a lower case letters
        string line2 = to_lower(line);

        //for loop to loop over the map
        for(auto i : scam_words){
            //if the word is in the map it will add its points
            if(line2.find(i.first) != string::npos){
                cnt += i.second;
            }
        }
    }
    //print the total points
    cout<<cnt<<'\n';
}

int main() {
    string name;
    cout<<"Enter the file name with extension .txt: ";
    cin>>name;
    scanner(name);
    return 0;
}
