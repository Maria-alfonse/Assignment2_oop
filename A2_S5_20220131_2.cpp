// File:A2_S5_20220131_2.cpp
// Purpose: convert masculine to both genders
// Author: Rana Esmail Zekery
// Section: S5
// ID: 20220131
// TA: eng/Nardeen Mokhless Khela and eng/Maya Ahmed Kamal
// Date: October 28, 2023
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Function to check if a word is a masculine pronoun
bool isMascPronoun(const string& word) {
    static const string pronouns[] = {"he", "him", "his", "himself"};// Static Storage and constant to make sure that the array constant and doesn't change during the program

    for (const string& pronoun : pronouns) {
        if (word == pronoun) {
            return true;
        }
    }

    return false;
}

// Function to check if a string contains only alphabetic characters
bool isWord(const string& str) {
    for (char c : str) {
        if (!isalpha(c)) {
            return false;//HE2
        }
    }
    return true;
}

// Function to replace masculine pronouns in a sentence with both feminine and masculine
string replace_masculine_Pronouns(const string& sentence) {
    string result = sentence;
    string delimiter = " ,.!?";
    int start = 0, end;

    while (start != string::npos) {
        end = result.find_first_of(delimiter, start);//to find the first one of the delimiter and get the index of it//find the non-alphabetic characters
        //search from start
        if (end == string::npos) {//there is no delimiter
            end = result.length();
        }
        string word = result.substr(start, end - start);// length

        // Replace "he" with "he or she"
        if (isMascPronoun(word) && isWord(word) && word == "he") {
            result.replace(start, word.length(), word + " or she");
        }
        // Replace "him" with "him or her"
        if (isMascPronoun(word) && isWord(word) && word == "him") {
            result.replace(start, word.length(), word + " or her");
        }
        // Replace "himself " with "himself or herself"
        if (isMascPronoun(word) && isWord(word) && word == "himself") {
            result.replace(start, word.length(), word + " or herself");
        }

        // Replace "his" with "his or her"
        if (isMascPronoun(word) && isWord(word) && word == "his") {
            result.replace(start, word.length(), word + " or her");
        }

        start = result.find_first_not_of(delimiter, end);//to find the
        // alphabetic characters
    }

    return result;
}

int main() {
    string sentence;

    cout << "Enter a sentence: ";
    getline(cin, sentence);

    string inclusiveSentence = replace_masculine_Pronouns(sentence);

    cout << "Inclusive Speech sentense: " << inclusiveSentence << '\n';

    return 0;
}
