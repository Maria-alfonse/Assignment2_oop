// File: A2_S5_2022025_No1.cpp
// Purpose: The program aims to correct spacing, capitalization, and ensuring a proper ending period.
// Author: Ahmed Abdelaziz Ahmed.
// Section: S5
// ID: 20220025
// TA: Maya Ahmed Kamal
// Date: 26 Oct 2023
#include <iostream>
#include <vector>

using namespace std;
string  ReadString() {
    string S1 , Ans;
    cout << "Please Enter Your String?\n";
    getline(cin , S1);
    Ans = S1;
    while(S1.back() != '.'){
        getline(cin , S1);
        Ans+=S1;
    }
    return Ans;
}
string  LowerAllString(string S1) {
    for (short i = 0; i < S1.length(); i++) {
        S1[i] = tolower(S1[i]);
    }
    return S1;
}
vector<string>Split_String(string s , string Delim=" ") {
    s = LowerAllString(s);
    int pos = 0, WordIdx = 0;
    string word;
    vector<string> vString;
    while ((pos = s.find(Delim)) != std::string::npos) {
        word = s.substr(0, pos);
        if (word != "") {
            if (vString.size() == 0) {
                word[0] = ::toupper(word[0]);
            }
            vString.push_back(word);
        }
        s.erase(0, pos + Delim.size());
    }
    if (s != " ") {

        vString.push_back(s);
    }
    return vString;
}
string JoinString(vector<string> vString, string Delim  = " ") {
    string S1; for (string& s : vString){
        S1 = S1 + s + Delim;
    }
    return S1.substr(0, S1.length() - Delim.length());
}
int main() {
    string s = ReadString();
    vector<string>vString = Split_String(s);
    s =  JoinString(vString);
    cout<<s;
}