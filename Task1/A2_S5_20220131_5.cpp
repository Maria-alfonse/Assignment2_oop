#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

// Function to sort pairs in descending order depend on the second element which is (score) .
bool sortbysecdesc(const pair<string, int> &a, const pair<string, int> &b) {
    return a.second > b.second;
}

// Function to add a player and their score to the list of scores.
void add_player(vector<pair<string, int>> &scores, string name, int score) {
    scores.push_back(make_pair(name, score));
}

// Function to update the top 10 list of players .
void ftop_10(vector<pair<string, int>> &top_10, vector<pair<string, int>> &scores) {
    top_10 = scores;  //copy all elemnt in top_10
    sort(top_10.begin(), top_10.end(), sortbysecdesc);
    // Remove elements after the top 10
    if (top_10.size() > 10) {
        top_10.resize(10);
    }
}

// Function to find a player's highest score in the top 10 list.
void find_player(string name, vector<pair<string, int>> &top_10,vector<pair<string, int>> &scores) {
    int max_score = 0;
    for (auto &player : top_10) {
        if (player.first == name) {
            max_score = max(max_score, player.second);//find the max score
        }
    }
    bool inputed =false;
    for (auto &player : scores) {
        if (player.first == name) {
            inputed=true;
        }
    }
    if (max_score == 0&&inputed) {
        cout << name<<" not found in the top 10 list." << endl;
    }
    else if (!inputed) {
        cout <<name <<"has not been input";

    }
    else if ( max_score>0&& inputed){
        cout << name << "'s highest score is :" << max_score << endl;
    }

}

// Function to display the menu and handle user input.
void menu(vector<pair<string, int>> &top_10, vector<pair<string, int>> &scores) {
    int op;
    cout <<"""1 - Add player\n"
           "2 - Print the top 10\n"
           "3 - Find player\n"
           "4 - Exit\n""";
    cin >> op;
    if (op == 1) {
        string name;
        int score;
        cout << "Enter your name :";
        cin >> name;
        cout << "Enter your score :";
        cin >> score;
        add_player(scores, name, score);
    }
    else if (op == 2) {
        cout <<"top_10 list is :\n";

        ftop_10(top_10, scores);
        for (int i = 0; i < static_cast<int>(top_10.size()); i++) {
            cout << top_10[i].first << " " << top_10[i].second << '\n';
        }
    }
    else if (op == 3) {
        ftop_10(top_10, scores);
        cout <<"enter the name of the player :";
        string name;
        cin >> name;
        find_player(name, top_10,scores);
    }
    else if (op == 4) {
        exit(0);

    }
    else {
        cout << "Invalid option. Please select a valid option (1-4)." << '\n';


    }
}

int main() {
    vector<pair<string, int>> top_10;
    vector<pair<string, int>> scores;

    while (true) {
        menu(top_10, scores);
    }

}
