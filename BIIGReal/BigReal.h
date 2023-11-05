//
// Created by Ahmed on 11/5/2023.
//
#pragma once
#include <bits/stdc++.h>
using namespace std;
#ifndef BIIGREAL_BIGREAL_H
#define BIIGREAL_BIGREAL_H


class BigReal {
private:
    string _Real;
    int _Size;
    bool _Sign; //0 +ve && 1 -ve

    bool isValid() {
        //To count the dots
        int count = 0;
        for (int i = 0; i < _Size; ++i) {
            if (_Real[i] == '.' && count == 0) {
                count++;
            }
                //if the char is not a number and the count is 1 then this is invalid number
            else if (!isdigit(_Real[i])){
                return false;
            }
        }
        //to add a decimal part
        if(count == 0){
            _Size+=2;
            _Real +=".0";
        }
        return true;
    }

    vector<string>Split_String(string s) {
        //vector of size 2 to store the int and decimal parts
        vector<string>vString;
        string int_part ;
        string Decimal_part;

        //to locate the position of the .
        int Dot_pos =  s.find(".");

        //if the  . is in the string
        if(Dot_pos != string::npos) {
            //int part = the string before the . and the decimal part = the string after it
            int_part = s.substr(0, Dot_pos);
            Decimal_part = s.substr(Dot_pos + 1);

            //if int part or the decimal parts are empty is loads 0 and increase the size by 1
            if (int_part.empty()) {
                int_part = "0";
                _Size++;
            }
            if (Decimal_part.empty()) {
                Decimal_part = "0";
                _Size++;
            }

        }else{ //if no . we add a 0
            int_part = s;
            Decimal_part = "0";
            _Size++;
        }
        vString.push_back(int_part);
        vString.push_back(Decimal_part);
        return vString;
    }

    bool less_than(BigReal& n, BigReal& m){
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
                int frac1 = n1[1].size();
                int frac2 = m1[1].size();

                while (frac1 > frac2) {
                    m1[1] +='0';
                    frac2++;
                }
                while (frac1 < frac2) {
                    n1[1] +='0';
                    frac1++;
                }

                for(int i=0 ; i < n1[1].size() ; i++){
                    if(n1[1][i] < m1[1][i]){
                        return !n._Sign;
                    }else if(n1[1][i] > m1[1][i]) {
                        return n._Sign;
                    }
                }

            }else if(n1[0].size() < m1[0].size()) {
                return !n._Sign;
            }else{
                return n._Sign;
            }
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
        //to erase loading zeros in the fraction
        while(n._Real[n._Real.size()-1] == '0'){
            n._Real.erase(n._Real.size()-1);
            n._Size--;
        }
        while(m._Real[m._Real.size()-1] == '0'){
            m._Real.erase(m._Real.size()-1);
            m._Size--;
        }
        if(n._Real == m._Real && n._Size == m._Size && n._Sign == m._Sign){
            return true;
        }return false;
    }

    string Sum(BigReal stNum, BigReal SecNum) {
        string Ans = "";
        int carry = 0;
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
        }
        else if(stNum._Sign!=SecNum._Sign){
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
    string Sub(BigReal num1, BigReal num2) {
        string Ans = "";
        bool resultSign = num1._Sign;
        if (Equality(num1,num2)){
            Ans="0";
            return Ans;
        }
        if (less_than(num1, num2)) {
            swap(num1, num2);
            resultSign= !num1._Sign; // Change sign of the result
        }
        if (num1._Sign == num2._Sign && num1._Sign==0) {
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
        if (num1._Sign == 1 && num2._Sign == 1) {
            // Both numbers are negative; convert to positive
            num1._Sign = 0; // Change sign of num1 to positive
            num2._Sign = 0; // Change sign of num2 to positive

            if (less_than(num1, num2)) {//-3--5==-3+5
                // num1 is smaller in magnitude, so the result will be positive
                num1._Sign = 1; // Change sign of num1 to what it was
                Ans = Sum(num2, num1);
            } else {//-5--3
                // Change sign of num1 to neg as it was
                num2._Sign =1;
                // num1 is greater or equal in magnitude, so the result will be negative
                Ans = Sum(num1, num2);
                resultSign = 1; // The result should be negative
            }

            Ans = (resultSign ? "" : "-") + Ans;
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

public:
    BigReal();
    BigReal(string Real) ;
    int size();
    int sign();
    BigReal operator+(BigReal& other) ;
    BigReal operator-(BigReal& other);
    friend ostream& operator<<(ostream& os, BigReal& BIG);
    bool operator<(BigReal& other);
    bool operator>(BigReal& other);
    bool operator==(BigReal& other);
};


#endif //BIIGREAL_BIGREAL_H
