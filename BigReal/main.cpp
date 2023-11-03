#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BigReal {
private:
    string _Real;
    int _Size;
    bool _Sign; //0 +ve && 1 -ve

    bool isValid() {
        int count = 0;
        for (int i = 0; i < _Size; ++i) {
            if (_Real[i] == '.' && count == 0) {
                count++;
            }

            else if (!isdigit(_Real[i])){
                return false;
            }
        }
        if(count == 0){
            _Real +=".0";
        }
        return true;
    }

    vector<string>Split_String(string s , string Delim=".") {
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
        if (s != ".") {
            vString.push_back(s);
        }
        return vString;
    }

    string Sum(BigReal& stNum, BigReal& SecNum) {
        string Ans = "";
        int carry = 0;
        if (stNum.isValid() && SecNum.isValid()) {
            vector<string> Num1 = Split_String(stNum._Real);
            string Deci1 = Num1[0];
            string frac1 = Num1[1];
            vector<string> Num2 = Split_String(SecNum._Real);
            string Deci2 = Num2[0];
            string frac2 = Num2[1];
            if (!stNum._Sign && !SecNum._Sign) {
                int digit_Idx1 = frac1.size() - 1;
                int digit_Idx2 = frac2.size() - 1;
                while(digit_Idx1 != digit_Idx2){
                    if(digit_Idx1 < digit_Idx2){
                        frac1 = frac1 + '0';
                        digit_Idx1++;
                    }else{
                        frac2 = frac2 + '0';
                        digit_Idx2++;
                    }
                }

                while (digit_Idx1 > -1 || digit_Idx2 > -1) {

                    int Digit1 = (digit_Idx1 >= 0) ? frac1[digit_Idx1] - '0' : 0;
                    int Digit2 = (digit_Idx2 >= 0) ? frac2[digit_Idx2] - '0' : 0;
                    int sum = Digit1 + Digit2 + carry;
                    carry = sum / 10;
                    sum = sum % 10;
                    Ans = to_string(sum) + Ans;
                    digit_Idx1--;
                    digit_Idx2--;

                }
                //std::reverse(Ans.begin(), Ans.end());
                Ans = '.' + Ans;
                digit_Idx1 = Deci1.size() - 1;
                digit_Idx2 = Deci2.size() - 1;
                while (digit_Idx1 > -1 || digit_Idx2 > -1) {
                    int Digit1 = (digit_Idx1 >= 0) ? Deci1[digit_Idx1] - '0' : 0;
                    int Digit2 = (digit_Idx2 >= 0) ? Deci2[digit_Idx2] - '0' : 0;
                    int sum = Digit1 + Digit2 + carry;
                    carry = sum / 10;
                    sum = sum % 10;
                    Ans = to_string(sum) + Ans;
                    digit_Idx1--;
                    digit_Idx2--;
                }
                if (carry > 0) {
                    Ans = to_string(carry) + Ans;
                }


                return Ans;
            }

            else if(stNum._Sign && SecNum._Sign){

                int digit_Idx1 = frac1.size() - 1;
                int digit_Idx2 = frac2.size() - 1;
                while(digit_Idx1 != digit_Idx2){
                    if(digit_Idx1 < digit_Idx2){
                        frac1 = frac1 + '0';
                        digit_Idx1++;
                    }else{
                        frac2 = frac2 + '0';
                        digit_Idx2++;
                    }
                }

                while (digit_Idx1 > -1 || digit_Idx2 > -1) {

                    int Digit1 = (digit_Idx1 >= 0) ? frac1[digit_Idx1] - '0' : 0;
                    int Digit2 = (digit_Idx2 >= 0) ? frac2[digit_Idx2] - '0' : 0;
                    int sum = Digit1 + Digit2 + carry;
                    carry = sum / 10;
                    sum = sum % 10;
                    Ans = to_string(sum) + Ans;
                    digit_Idx1--;
                    digit_Idx2--;

                }
                //std::reverse(Ans.begin(), Ans.end());
                Ans = '.' + Ans;
                digit_Idx1 = Deci1.size() - 1;
                digit_Idx2 = Deci2.size() - 1;
                while (digit_Idx1 > -1 || digit_Idx2 > -1) {
                    int Digit1 = (digit_Idx1 >= 0) ? Deci1[digit_Idx1] - '0' : 0;
                    int Digit2 = (digit_Idx2 >= 0) ? Deci2[digit_Idx2] - '0' : 0;
                    int sum = Digit1 + Digit2 + carry;
                    carry = sum / 10;
                    sum = sum % 10;
                    Ans = to_string(sum) + Ans;
                    digit_Idx1--;
                    digit_Idx2--;
                }
                if (carry > 0) {
                    Ans = to_string(carry) + Ans;
                }

                Ans = '-'+Ans;
                return Ans;
            }else if(stNum._Sign!=SecNum._Sign){
                if(stNum < SecNum){
                    swap(stNum,SecNum);
                }
                if(stNum._Sign){
                    stNum._Sign = !stNum._Sign;
                }if(SecNum._Sign){
                    SecNum._Sign = !SecNum._Sign;
                }

                Ans = Sub(stNum,SecNum);
                return Ans;


            }
        }
        else {
            cout << "Numbers are invalid";
            return "";
        }
    }

    string Sub(BigReal& num1, BigReal& num2) {
        string Ans = "";

        if (num1.isValid() && num2.isValid()) {
            bool resultSign = num1._Sign;
            if (Equality(num1,num2)){
                Ans="0";
                return Ans;
            }
            if (less_than(num1, num2)) {
                swap(num1, num2);
                resultSign= !num1._Sign; // Change sign of the result
            }
            if (num1._Sign == num2._Sign) {
                vector<string> Num1 = Split_String(num1._Real);
                string Int1 = Num1[0];
                string Dec1 = Num1[1];
                vector<string> Num2 = Split_String(num2._Real);
                string Int2 = Num2[0];
                string Dec2 = Num2[1];

                // Subtract decimal parts
                int lenDec1 = Dec1.length(), lenDec2 = Dec2.length();
                int maxLenDec = max(lenDec1, lenDec2);

                if (lenDec1 < lenDec2)
                    Dec1.append(lenDec2 - lenDec1, '0');
                else if (lenDec1 > lenDec2)
                    Dec2.append(lenDec1 - lenDec2, '0');

                int borrow = 0;
                for (int i = maxLenDec - 1; i >= 0; i--) {
                    int sub = ((Dec1[i] - '0') - (Dec2[i] - '0') - borrow);
                    if (sub < 0) {
                        sub += 10;
                        borrow = 1;
                    } else
                        borrow = 0;
                    Ans = to_string(sub) + Ans;
                }

                Ans = '.' + Ans;

                // Subtract integer parts
                int lenInt1 = Int1.length(), lenInt2 = Int2.length();
                int maxLenInt = max(lenInt1, lenInt2);

                if (lenInt1 < lenInt2)
                    Int1 = string(lenInt2 - lenInt1, '0') + Int1;
                else if (lenInt1 > lenInt2)
                    Int2 = string(lenInt1 - lenInt2, '0') + Int2;

                for (int i = maxLenInt - 1; i >= 0; i--) {
                    int sub = ((Int1[i] - '0') - (Int2[i] - '0') - borrow);
                    if (sub < 0) {
                        sub += 10;
                        borrow = 1;
                    } else
                        borrow = 0;
                    Ans = to_string(sub) + Ans;
                }

                if (!Dec1.empty() || !Dec2.empty()) {
                    Ans = Ans.substr(0, Ans.find_last_not_of('0') + 1);  // Remove trailing zeros 52.15000000
                    if (Ans[Ans.size() - 1] == '.') {  // Remove decimal point if no decimal places 43.0000
                        Ans.pop_back();//43
                    }
                }
                if (!Int1.empty() || !Int2.empty()) {
                    Ans = Ans.substr(Ans.find_first_not_of('0') , Ans.size());  // Remove trailing zeros 00052.15
                }
                if(Ans.empty()){
                    Ans = "0.0";
                }
                Ans = (resultSign ? "-" : "") + Ans;
                return Ans;
            }
            else if (num1._Sign!=num2._Sign){
                if(num1._Sign){
                    num1._Sign = !num1._Sign;
                }if(num2._Sign){
                    num2._Sign = !num2._Sign;
                }
                Ans = Sum(num1,num2);
                Ans = (resultSign ? "-" : "") + Ans;
                return Ans;
            }

        }
        else {
            cout << "Numbers are invalid";
            return "";
        }
    }


    void GetValue(){
        if(_Sign){
            cout<<"+"<<_Real<<endl;
        }else{
            cout<<"-"<<_Real<<endl;
        }
    }

    bool less_than(BigReal& n, BigReal& m){
        if(n.isValid() && m.isValid()){
            vector<string>n1 = n.Split_String(n._Real);
            vector<string>m1 = m.Split_String(m._Real);
            if(n1==m1 && n._Sign == m._Sign){
                return false;
            }else if(n1==m1 && n._Sign != m._Sign ){
                return n._Sign;
            }
            if(n._Sign != m._Sign){
                //if n 0 and m 1 then false
                return n._Sign;
            }else{
                if(n1[0].size() == m1[0].size()){
                    for(int i=0 ; i < n1[0].size() ; i++){
                        if(n1[0][i] < m1[0][i]){
                            return !n._Sign;
                        }else if(n1[0][i] > m1[0][i]){
                            return n._Sign;
                        }
                    }
                    // 2ecound stage
                    if(n1[1].size() == m1[1].size()){
                        for(int i=0 ; i < n1[1].size() ; i++){
                            if(n1[1][i] < m1[1][i]){
                                return !n._Sign;
                            }else if(n1[1][i] > m1[1][i]) {
                                return n._Sign;
                            }
                        }
                    }else if(n1[1].size() < m1[1].size()) {
                        return !n._Sign;
                    }else{
                        return n._Sign;
                    }
                }else if(n1[0].size() < m1[0].size()) {
                    return !n._Sign;
                }else{
                    return n._Sign;
                }
            }
        }else {
            cout<<"Numbers not valid!\n";
            return false;
        }
    }

    bool greater_than(BigReal&n, BigReal&m){
        if(n._Real == m._Real){
            return false;
        }else{
            return !less_than(n, m);
        }
    }

    bool Equality(BigReal&n, BigReal&m){
        if(n._Real == m._Real && n._Size == m._Size && n._Sign == m._Sign){
            return true;
        }return false;
    }

public:
    BigReal(){
        _Real = "0.0";
        _Size = 3;
        _Sign = 0;
    }

    BigReal(string Real) {
        bool check = true;
        int count = 0;
        for (int i = 0; i < Real.size(); ++i) {
            if (Real[i] == '.' && count == 0) {
                count++;
            }
            else if (!isdigit(Real[i])){
                check = false;
            }
        }
        if(check){
            _Real = Real;
            _Size = _Real.size();
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
            if(_Real[0] == '.'){
                _Real = '0' + _Real;
            }
        }else{
            cout<<"Invalid Number!\tSetting value to 0.0\n";
            _Real = "0.0";
            _Size = 3;
            _Sign = 0;
        }

    }

//copy constructor

//Assignment operator

    int size(){
        return _Size;
    }

    int sign(){
        return _Sign;
    }


    BigReal operator+(BigReal& other) {
        BigReal Answer(Sum(*this, other));
        return Answer;
    }

    BigReal operator-(BigReal& other){
        BigReal Answer(Sub(*this, other));
        return Answer;

    }


    bool operator<(BigReal& other){
        bool Answer(less_than(*this, other));
        return Answer;
    }

    bool operator>(BigReal& other){
        bool Answer(greater_than(*this, other));
        return Answer;
    }

    bool operator==(BigReal& other){
        bool Answer(Equality(*this, other));
        return Answer;
    }

    friend ostream& operator<<(ostream& os, BigReal& BIG) {
        os << (BIG._Sign ? "-" : "") << BIG._Real;
        return os;
    }
};

int main() {
    BigReal n1 ("11.9000000000000000000000000000000001");
    BigReal n2 ("2333333333339.1134322222222292");
    BigReal n3 = n1 + n2;
    cout << n3<<'\n';
    BigReal();
    string n,m;
    cin>>n>>m;
    BigReal n4 (n), n5 (m);
    cout<<(n2<n3)<<'\n'<<(n2>n3)<<'\n';

    return 0;
}
