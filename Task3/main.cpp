#include <bits/stdc++.h>
using namespace std;

class Instruction {
public:
    map<string, string>instructions;
    void GetInstructions(string filename){
        ifstream file (filename);
        string line;
        string Address = "00";
        int cnt = 0;
        int cnt1 = 0;
        string lst = "0123456789ABCDEF";
        while(getline(file, line)){
            instructions[Address] = line;
            Address = lst[0+cnt1] + lst[0 + cnt];
            cnt++;
            if (cnt == 15){
                cnt = 0 ;
                cnt1 ++;
            }
        }
        file.close();
    }
};


class Memory : public Instruction{
public:
    map<string , string>registers;
    Memory(){
        string lst = "0123456789ABCDEF";
        for(int i=0 ; i<16 ; i++){
            for(int j=0 ; j<16 ; j++){
                string s = string(1, lst[i]) + string (1, lst[j]);
                char c = instructions[s][0];

                if(c == '1'){
                    void LoadToAddress();
                }else if(c == '2'){
                    void LoadPattern();
                }else if(c == '3'){

                }else if(c == '4'){

                }else if(c == '5'){

                }else if(c == '6'){

                }else if(c == 'B'){

                }else if(c == 'C'){

                }
            }
        }
    }

};
int main() {

    return 0;
}