// File: A2_S5_2022025_No7.cpp
// Purpose: Domino Game
// Author: Ahmed Abdelaziz Ahmed.
// Section: S5
// ID: 20220025
// TA: Maya Ahmed Kamal
// Date: 26 Oct 2023
#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;
struct dominoT {
    int leftDots;
    int rightDots;
    bool operator==(const dominoT& other) const {
        return leftDots == other.leftDots && rightDots == other.rightDots;
    }
};


bool FormsDominoChain(deque<dominoT> & dominos ,deque<dominoT>&Chain) {
    if (Chain.size() == dominos.size()) {
        return true;
    }
    if (Chain.size() == 0) {
        Chain.push_back(dominos[0]);
    }
    int LastRight = Chain.back().rightDots;
    for (int i = Chain.size(); i < dominos.size(); ++i) {

        if(dominos[i].rightDots == Chain.back().rightDots && dominos[i].leftDots == Chain.back().leftDots   ||   dominos[i].leftDots == Chain.back().rightDots &&  dominos[i].rightDots == Chain.back().leftDots  ){
            auto it = find(dominos.begin(), dominos.end(),dominos[i-1]);
            dominoT Temp = *it;
            if (it != dominos.end()) {
                dominos.erase(it); // Remove the element
            }
            dominos.push_back(Temp);
            return FormsDominoChain(dominos, Chain);
        }


        if (dominos[i].leftDots == Chain.back().rightDots) {
            Chain.push_back(dominos[i]);
            if (FormsDominoChain(dominos, Chain)) {
                return true;
            }
            Chain.pop_back();
            return false;
        } else if (dominos[i].rightDots == Chain.back().rightDots) {
            dominoT Temp = {dominos[i].rightDots, dominos[i].leftDots};
            Chain.push_back(Temp);
            if (FormsDominoChain(dominos, Chain)) {
                return true;
            }
            Chain.pop_back();
            return false;
        }else if (dominos[i].leftDots == Chain.front().leftDots) {
            dominoT Temp = {dominos[i].rightDots, dominos[i].leftDots};
            Chain.push_front(Temp);
            if (FormsDominoChain(dominos, Chain)) {
                return true;
            }
            Chain.pop_back();
            return false;
        }else if(dominos[i].rightDots == Chain.front().leftDots){
            Chain.push_front(dominos[i]);
            if (FormsDominoChain(dominos, Chain)) {
                return true;
            }
            Chain.pop_back();
            return false;
        }
    }

    return false;
}
void PrintDominoChain(deque<dominoT>& chain) {
    for (int i = 0; i < chain.size(); ++i) {
        const dominoT& domino = chain[i];
        cout << domino.leftDots << "|" << domino.rightDots;
        if (i < chain.size() - 1) {
            cout << " - ";
        }
    }
    cout <<endl;
}
int main() {

    deque<dominoT> dominoSet = {{1, 4}, {2, 6}, {4, 4}, {6,1},{4,3}};
    deque<dominoT> chain;

    if (FormsDominoChain(dominoSet, chain)) {
        cout << "Domino Solution: ";
        PrintDominoChain(chain);
    } else {
        cout << "No valid chain" << endl;
    }

    return 0;
}
