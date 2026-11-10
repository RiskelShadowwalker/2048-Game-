#include <iostream>
#include <vector>
#include <random>
#include <cctype>

using std::cout;
using std::endl;
using std::vector;
using std::cin;

static void display_board();
static void make_number_appear();
static void move_left();

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
    board.at(0) = {0, 2, 2, 4};
cout << "Welcome to 2048! The controls are: W for up, S for down, A for left, D for right, R to reset the game" << endl;
    char direction{};
    make_number_appear();
    make_number_appear();
    display_board();

        cout << "\nInput only W,A,S,D,R allowed:" << endl;
        do {
            cout << "Input:";
            cin >> direction;
            direction = static_cast<char>(std::tolower(direction));
            cout << endl;
            if (direction !=  'r') {
                switch (direction) {
                    case 'w': {
                        break;
                    }
                    case 's': {
                        break;
                    }
                    case 'a': {
                        move_left();
                        break;
                    }
                    case 'd': {
                        break;
                    }
                    default: {
                        cout << "Invalid input! Try again." << endl;
                        break;
                    }
                }
            }else {
                cout << "Resetting..." << endl;
            }
            display_board();
            cout << endl;
        }
        while (direction != 'r');
    return 0;
}

void display_board(){
    for (size_t row{0}; row < board.size(); row++) {
        cout << endl;
        for (size_t column{0}; column < board[row].size(); column++) {
            cout << board.at(row).at(column) << " ";
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
        if (position.empty()) {
            return;
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

void move_left() {
    vector<vector<int>> board_before_move {board};
    for (size_t row{0}; row < board.size(); row++) {
        size_t counter {0};
        vector <int> new_row {};
        vector <int> merged_row {};
        for (size_t column{0}; column < board.size(); column++) {
            if (board.at(row).at(column) != 0) {
                new_row.push_back(board.at(row).at(column));
            }
            else{
            }
        }
        while (new_row.size() != counter) {
            if (counter + 1 < new_row.size() && new_row.at(counter) == new_row.at(counter+1)) {
                merged_row.push_back(new_row.at(counter) + new_row.at(counter + 1));
                counter += 2;
            }
            else{
                merged_row.push_back(new_row.at(counter));
                counter++;
            }
        }
        while (merged_row.size() < board.size()) {
            merged_row.push_back(0);
        }
        board.at(row) = merged_row;
    }
    if (board_before_move != board) {
        make_number_appear();
    }else{
    }
}