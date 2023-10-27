#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;
vector<string>Split_String(string s , string Delim=" ") {
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
map<string ,vector<string>>LoadLookUp(string FileName = "LookUpTable.txt"){
    map<string ,vector<string>>mp;
    fstream MyFile;
    MyFile.open(FileName , ios::in);
    if(MyFile.is_open()){
        string line;
        while(getline(MyFile,line)){
          vector<string>vString =Split_String(line);
          string word = vString[0];
          vString.erase(vString.begin());
          mp[word] = vString;
        }
    }
    MyFile.close();
    return mp;
}
vector<string>ReadPost(string FileName = "Post.txt") {
    fstream MyFile;
    vector<string>vString;
    MyFile.open(FileName , ios::in);
    if(MyFile.is_open()){
        string line;
        while(getline(MyFile,line)){
            vString=Split_String(line);
        }
    }
    MyFile.close();
    return vString;
}
vector<string>ReWritePost(map<string ,vector<string>> Table = LoadLookUp(), vector<string>vString = ReadPost() ){

    for (int i = 0; i < vString.size(); ++i) {
        auto itr = Table.find(vString[i]);
        if(itr != Table.end()){
            vString[i] = Table[vString[i]][0];
        }
    }
    return vString;
}
string JoinString(vector<string> vString = ReWritePost(), string Delim  = " ") {
    string S1; for (string& s : vString){
        S1 = S1 + s + Delim;
    }
    return S1.substr(0, S1.length() - Delim.length());
}
void NewPost(string Post = JoinString()){
    fstream MyFile;
    MyFile.open("NewPost.txt" , ios::out);
    MyFile << Post;
}
int main() {
    NewPost();
    return 0;
}