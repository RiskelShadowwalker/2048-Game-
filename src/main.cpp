#include <iostream>
#include <vector>
#include <string>
#include <random>

using std::cout;
using std::endl;
using std::vector;
using std::cin;

static std::random_device rd;
static std::mt19937 gen(rd());

static void display_board();
static void make_number_appear();


static vector <vector<std::string>> board

{    {"*","*","*","*"}
    ,{"*","*","*","*"}
    ,{"*","*","*","*"}
    ,{"*","*","*","*"}
};



int main() {

    display_board();
    make_number_appear();
    display_board();

    return 0;
}

void display_board(){
    for (size_t i{0}; i < board.size(); i++) {
        cout << endl;
        for (size_t j{0}; j < board[i].size(); j++) {
            cout << board.at(i).at(j) << " ";
        }
    }
}

void make_number_appear() {
    for (size_t i{0}; i < board.size(); i++) {
        for (size_t j{0}; j < board[i].size(); j++) {
            std::uniform_int_distribution<int> dice(1, 10);
            int roll = dice(gen);
            if (board.at(i).at(j) == "*") {
                if (roll < 10){
                    board.at(i).at(j) = '2';
                }else {
                    board.at(i).at(j) = '4';
                }
            }
            else {
            }
        }
    }
}
