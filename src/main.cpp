#include <iostream>
#include <vector>
#include <random>

using std::cout;
using std::endl;
using std::vector;
using std::cin;

static void display_board();
static void make_number_appear();


static vector <vector<int>> board
{    {0,0,0,0}
    ,{0,0,0,0}
    ,{0,0,0,0}
    ,{0,0,0,0}
};

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_int_distribution<int> dice(1, 10);

int main() {

    make_number_appear();
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
    vector <std::pair<int, int>> position;

    for (size_t row{0}; row < board.size(); row++) {
        for (size_t column{0}; column < board[row].size(); column++) {
            if (board.at(row).at(column) == 0) {
                position.push_back({row, column});
            }else {
            }
        }
    }
    std::uniform_int_distribution<int> size_roll(0, position.size() - 1);
    int position_to_put_number = size_roll(gen);
    int roll = dice(gen);
    std::pair<int, int> row_and_column {position.at(position_to_put_number)};
    if (roll < 10) {
        board.at(row_and_column.first).at(row_and_column.second) = 2;
    }
    else {
        board.at(row_and_column.first).at(row_and_column.second) = 4;
    }
}