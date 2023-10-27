#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


vector<string> readFile( string& filename) {
    ifstream file(filename+".txt");
    vector<string> lines;
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
    file.close();
}
void compareCharacterByCharacter(string file1_name, string file2_name) {
    bool identical = true;
    vector<string> File1 = readFile(file1_name);
    vector<string> File2 = readFile(file2_name);

    if (File1.size() != File2.size()) {
        identical = false;
    }

    for (int i = 0; i < max(File1.size(), File2.size()); i++) {
        if (i >= File1.size() || i >= File2.size() || File1[i] != File2[i]) {
            identical = false;
            cout << "Files are different at line " << (i + 1) << ":\n";
            if (i < File1.size()) {
                cout << "File 1: " << File1[i] << '\n';
            }
            if (i < File2.size()) {
                cout << "File 2: " << File2[i] << '\n';
            }
            break;
        }
    }

    if (identical) {
        cout << "Files are identical\n";
    }
}
vector<string> split(string s,string delim) {
    vector <string> vec;
    int pos = 0;
    string word;
    while ((pos = s.find(delim)) != std::string::npos)
    {
        word = s.substr(0, pos);
        if (word != " ") {
            vec.push_back(word);
        }
        s.erase(0, pos + delim.length());

    }
    if (s != " ") {
        vec.push_back(s);
    }
    return vec;
}


void compareWordByWord(string file1_name, string file2_name) {
    vector<string> File1 = readFile(file1_name);
    vector<string> File2 = readFile(file2_name);
    vector<string> File1_splited;
    vector<string> File2_splited;

    bool identical = true;

    for (int i = 0; i < max(File1.size(), File2.size()); i++) {
        if (i < File1.size()) {//number of max lines less than files number
            File1_splited = split(File1[i], " ");
        }
        if (i < File2.size()) {
            File2_splited = split(File2[i], " ");
        }

        if (File1_splited.size() != File2_splited.size()) {
            identical = false;
        }
        //loop in every word
        for (int j = 0; j < max(File1_splited.size(), File2_splited.size()); j++) {
            if (j >= File1_splited.size() || j >= File2_splited.size() || File1_splited[j] != File2_splited[j]) {
                identical = false;
                cout << "Files are different at line " << (i + 1) << ", word " << (j + 1) << ":\n";
                if (j < File1_splited.size()) {
                    cout << "File 1: " << File1_splited[j] << '\n';
                }
                if (j < File2_splited.size()) {
                    cout << "File 2: " << File2_splited[j] << '\n';
                }
                break;
            }
        }

        if (!identical) {
            break;
        }

    }

    if (identical) {
        cout << "Files are identical\n";
    }
}


void menu(){
    int op;
    string f1_name,f2_name;
    cout <<"enter the first file name :";
    cin >>f1_name;
    cout <<"enter the second file name :";
    cin >>f2_name;
    cout <<"1-compare by char\n";
    cout << "2-compare by word\n";
    cin >>op;
    switch (op) {
        case 1:
            compareCharacterByCharacter(f1_name,f2_name);
            break;
        case 2:
            compareWordByWord(f1_name,f2_name);
            break;
        default:
            cout << "Invalid choice. Please select (1 or 2).\n";
    }
}
int main() {
    menu();
}
