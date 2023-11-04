#include "BigReal.h"
using namespace std;
//Default constructor
BigReal :: BigReal(){
    _Real = "0.0";
    _Size = 3;
    _Sign = 0;
}

BigReal ::BigReal(string Real) {
    _Real = Real;
    _Size = _Real.size();
    _Sign = 0;

    //to check the sign
    if (_Real[0] == '+') {
    _Sign = 0;
    _Real.erase(_Real.begin());
    _Size--;
    }
    else if (_Real[0] >= '0' && _Real[0] <= '9') {
    _Sign = 0;
    }
    else if (_Real[0] == '-') {
    _Sign = 1;
    _Real.erase(_Real.begin());
    _Size--;
    }

    //to correct the . position
    if(_Real[0] == '.'){
    _Real = '0' + _Real;
    _Size++;
    }

    //to check if the number is valid
    bool check = 0;
    int count_dot = 0;
    for (int i = 0; i < _Size; ++i) {
        //if the char is . and is the first . count_dot increase by 1
        if (_Real[i] == '.' && count_dot == 0) {
            count_dot++;
        }
        //if the char is not a number or if it is a . but not the first one then the number is invalid
        else if (!isdigit(_Real[i])){
            cout<<"\nInvalid Number! Set Number to default 0.0\n";
            check = 1;
            break;
            }
    }
    if(count_dot == 0){
        _Size+=2;
        _Real +=".0";
    }
    if(check){
        _Real = "0.0";
        _Size = 3;
        _Sign = 0;
    }
    //delete loading zeros 0090 -> 90
    while(!_Real.empty() && _Real[0]=='0' && _Real.size()>1){
        _Real.erase(_Real.begin());
        _Size--;
    }
}
int BigReal :: size(){
    return _Size;
}
int BigReal :: sign(){
    return _Sign;
}
BigReal BigReal :: operator+(BigReal& other) {
    BigReal Answer;
    string Result = Sum(*this, other);
    if(Result[0] == '-'){
        Answer._Sign = 1;
        Result.erase(Result.begin());
    }else {
        Answer._Sign = 0;
    }
    Answer._Size = Result.size();
    Answer._Real = Result;
    return Answer;
}
BigReal BigReal :: operator-(BigReal& other){
    BigReal Answer;
    string Result = Sub(*this, other);
    if(Result[0] == '-'){
        Answer._Sign = 1;
        Result.erase(Result.begin());
    }else {
        Answer._Sign = 0;
    }
    Answer._Size = Result.size();
    Answer._Real = Result;
    return Answer;
}
ostream& operator<<(ostream& os, BigReal& BIG) {
    os << (BIG._Sign ? "-" : "") << BIG._Real;
    return os;
}
bool BigReal :: operator<(BigReal& other){
    //Answer store the result of the less_than function which tests the < case
    bool Answer(less_than(*this, other));
    return Answer;
}
bool BigReal :: operator>(BigReal& other){
    //Answer store the result of the greater_than function which tests the > case
    bool Answer(greater_than(*this, other));
    return Answer;
}
bool BigReal :: operator==(BigReal& other){
    //Answer store the result of the Equality function which tests the = case
    bool Answer(Equality(*this, other));
    return Answer;
}
bool BigReal :: operator==(BigReal& other){
    bool Answer(Equality(*this, other));
    return Answer;
}
