#include <iostream>
#include <vector>
#include <random>
#include <cctype>
#include <algorithm>
#include <iomanip>

using std::cout;
using std::endl;
using std::vector;
using std::cin;

static void display_board();
static void make_number_appear();
static void move_left();
static void move_right();
static void move_up();
static void move_down();
static bool game_over();
static bool win_game_over();

// Merkt sich, ob schon gewonnen wurde, damit die Frage nur einmal kommt
static bool already_won{false};
static int score{0};
// Das Spielfeld: 4 Reihen mit je 4 Feldern, 0 = leeres Feld
static vector <vector<int>> board
{    {0,0,0,0}
    ,{0,0,0,0}
    ,{0,0,0,0}
    ,{0,0,0,0}
};
// Zufallsgenerator
static std::random_device rd;
static std::mt19937 gen(rd());
// 1 bis 9 ergibt eine 2, 10 ergibt eine 4 (90 % / 10 % wie im echten 2048)
static std::uniform_int_distribution<int> dice(1, 10);

int main() {
    char direction{};
    char keep_playing{};

cout << "Welcome to 2048! The controls are: W for up, S for down, A for left, D for right, R to reset the game" << endl;

    //In 2048 startet das Spiel immer mit zwei Zahlen
    make_number_appear();
    make_number_appear();
    display_board();

        cout << "\nInput only W,A,S,D,R,Q allowed:" << endl;

        do {
            cout << "Input:";
            cin >> direction;
            direction = static_cast<char>(std::tolower(direction));
            cout << endl;
                switch (direction) {
                    case 'w': {
                        move_up();
                        break;
                    }
                    case 's': {
                        move_down();
                        break;
                    }
                    case 'a': {
                        move_left();
                        break;
                    }
                    case 'd': {
                        move_right();
                        break;
                    }
                    case 'r': {
                        cout << "Resetting...";
                        // Neues Spiel: leeres Board, Punkte auf 0 und wieder zwei Startzahlen
                        board.clear();
                        score = 0;
                        board = {    {0,0,0,0}
                                      ,{0,0,0,0}
                                      ,{0,0,0,0}
                                      ,{0,0,0,0}
                        };
                        make_number_appear();
                        make_number_appear();
                        already_won = false;
                        break;
                    }
                    default: {
                        cout << "Invalid input! Try again." << endl;
                        break;
                    }
                }
            display_board();
            if (game_over() == true) {
                cout << "\nGame Over!" << endl;
                cout << "Your final score was: "<< score << endl;
                break;
            }
            //beim ersten 2048 fragen, danach ohne Nachfrage weiterspielen
            if (win_game_over() == true && already_won == false) {
                cout << "\nYou win! Congratulations!" << endl;
                cout << "Your final score was: "<< score << endl;
                cout << "Would you like to continue anyway? (Y/N):";
                cin >> keep_playing;
                keep_playing = static_cast<char>(std::tolower(keep_playing));
                if (keep_playing == 'n') {
                    break;
                }
                already_won = true;
            }
            cout << endl;
            cout << "Your current score is " << score << endl;
        }
        while (direction != 'q');

    cout << "Goodbye!" << endl;

    return 0;
}

void display_board(){
    for (size_t row{0}; row < board.size(); row++) {
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        for (size_t column{0}; column < board[row].size(); column++) {
            // setw sorgt dafür, dass alle Zahlen gleich breit sind und die Spalten untereinander stehen
            cout << std::setw(10)<< board.at(row).at(column) << std::setw(10);
        }
    }
}

// Setzt eine neue 2 oder 4 auf ein zufälliges leeres Feld
void make_number_appear() {
    //Positionen aller leeren Felder sammeln
    vector <std::pair<int, int>> position;
    for (size_t row{0}; row < board.size(); row++) {
        for (size_t column{0}; column < board[row].size(); column++) {
            if (board.at(row).at(column) == 0) {
                position.push_back({row, column});
            }else {
            }
        }
        }
    //Board ist voll: kein Platz für eine neue Zahl
    if (position.empty()) {
        return;
    }
    //Zufällige Position aus der Liste, der letzte gültige Index ist size() - 1
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

// Schiebt alle Zahlen nach links und fügt gleiche Nachbarn zusammen
void move_left() {
    // Kopie vom Board, um am Ende zu prüfen, ob der Zug etwas verändert hat
    vector <vector<int>> board_before_move {board};
    for (size_t row{0}; row < board.size(); row++) {
        size_t counter {0};
        vector <int> new_row {};
        vector <int> merged_row {};
        // 1. Erst nur die Zahlen der Reihe sammeln, Nullen weglassen
        for (size_t column{0}; column < board.size(); column++) {
            if (board.at(row).at(column) != 0) {
                new_row.push_back(board.at(row).at(column));
            }
            else{
            }
        }
        // 2. Gleiche Nachbarn zusammenfügen. Zuerst prüfen, ob es überhaupt eine nächste Zahl gibt.
        // Nach einem Zusammenfügen +2, damit der neue Stein im selben Zug nicht nochmal merged.
        while (new_row.size() != counter) {
            if (counter + 1 < new_row.size() && new_row.at(counter) == new_row.at(counter+1)) {
                merged_row.push_back(new_row.at(counter) + new_row.at(counter + 1));
                int total {new_row.at(counter) + new_row.at(counter + 1)};
                score += total;
                counter += 2;
            }
            else{
                merged_row.push_back(new_row.at(counter));
                counter++;
            }
        }
        // 3. Rechts mit Nullen auffüllen, bis die Reihe wieder 4 Felder hat
        while (merged_row.size() < board.size()) {
            merged_row.push_back(0);
        }
        board.at(row) = merged_row;
    }
    // Neue Zahl nur, wenn der Zug wirklich etwas verändert hat
    if (board_before_move != board) {
        make_number_appear();
    }else{
    }
}

// Wie move_left(), nur gespiegelt: Die Zahlen werden umgedreht, damit zuerst
// die Zahlen am rechten Rand mergen, und danach wieder zurückgedreht.
void move_right() {
    vector <vector<int>> board_before_move {board};
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
        // Umdrehen: die Zahl ganz rechts kommt nach vorne
        std::ranges::reverse(new_row);
        while (new_row.size() != counter) {
            if (counter + 1 < new_row.size() && new_row.at(counter) == new_row.at(counter+1)) {merged_row.push_back(new_row.at(counter) + new_row.at(counter + 1));
                int total {new_row.at(counter) +   new_row.at(counter + 1)};
                    score += total;
                counter += 2;
            }
            else{
                merged_row.push_back(new_row.at(counter));
                counter++;
            }
        }
        // Zurückdrehen, danach links mit Nullen auffüllen
        std::ranges::reverse(merged_row);
        while (merged_row.size() < board.size()) {
            merged_row.insert(merged_row.begin(),0);
        }
        board.at(row) = merged_row;
    }
    if (board_before_move != board) {
        make_number_appear();
    }else{
    }
}

// Wie move_up(), nur umgedreht (so wie move_right() zu move_left())
void move_down() {
    vector <vector<int>> board_before_move {board};
    for (size_t column{0}; column < board.size(); column++) {
        size_t counter {0};
        vector <int> new_column {};
        vector <int> merged_column {};
        for (size_t row{0}; row < board.size(); row++) {
            if (board.at(row).at(column) != 0) {
                new_column.push_back(board.at(row).at(column));
            }
            else{
            }
        }
        std::ranges::reverse(new_column);
        while (new_column.size() != counter) {
            if (counter + 1 < new_column.size() && new_column.at(counter) == new_column.at(counter+1)) {
                merged_column.push_back(new_column.at(counter) + new_column.at(counter + 1));
                int total {new_column.at(counter) + new_column.at(counter + 1)};
                score += total;
                counter += 2;
            }
            else{
                merged_column.push_back(new_column.at(counter));
                counter++;
            }
        }
        std::ranges::reverse(merged_column);
        while (merged_column.size() < board.size()) {
            merged_column.insert(merged_column.begin(),0);
        }
        for (size_t row{0}; row < board.size(); row++) {
            board.at(row).at(column) = merged_column.at(row);
        }
    }
    if (board_before_move != board) {
        make_number_appear();
    }else{
    }
}

// Wie move_left(), nur für Spalten: Die äußere Schleife geht über die Spalten,
// die innere läuft jede Spalte von oben nach unten durch
void move_up() {
    vector <vector<int>> board_before_move {board};
    for (size_t column{0}; column < board.size(); column++) {
        size_t counter {0};
        vector <int> new_column {};
        vector <int> merged_column {};
        for (size_t row{0}; row < board.size(); row++) {
            if (board.at(row).at(column) != 0) {
                new_column.push_back(board.at(row).at(column));
            }
            else{
            }
        }
        while (new_column.size() != counter) {
            if (counter + 1 < new_column.size() && new_column.at(counter) == new_column.at(counter+1)) {
                merged_column.push_back(new_column.at(counter) + new_column.at(counter + 1));
                int total {new_column.at(counter) + new_column.at(counter + 1)};
                score += total;
                counter += 2;
            }
            else{
                merged_column.push_back(new_column.at(counter));
                counter++;
            }
        }
        while (merged_column.size() < board.size()) {
            merged_column.push_back(0);
        }
        // Eine Spalte ist kein eigener Vector, also Feld für Feld zurückschreiben
        for (size_t row{0}; row < board.size(); row++) {
            board.at(row).at(column) = merged_column.at(row);
        }
    }
    if (board_before_move != board) {
        make_number_appear();
    }else{
    }
}

// Spiel vorbei, wenn kein Feld frei ist und nirgends zwei gleiche Nachbarn liegen.
// Rechts und unten prüfen reicht: Links und oben prüft schon der jeweilige Nachbar.
bool game_over() {
    for (size_t row{0}; row < board.size(); row++) {
        for (size_t column{0}; column < board[row].size(); column++) {
            if (board.at(row).at(column) == 0) {
                return false;
            }
            if (column + 1 < board.size() && board.at(row).at(column) == board.at(row).at(column+1)) {
                return false;
            }
            if (row + 1 < board.size() && board.at(row).at(column) == board.at(row+1).at(column)) {
                return false;
            }
        }
    }
    return true;
}

// true, sobald irgendwo eine 2048 auf dem Board liegt
bool win_game_over() {
    for (size_t row{0}; row < board.size(); row++) {
        for (size_t column{0}; column < board[row].size(); column++) {
            if (board.at(row).at(column) == 2048) {
                return true;
            }
        }
    }
    return false;
}