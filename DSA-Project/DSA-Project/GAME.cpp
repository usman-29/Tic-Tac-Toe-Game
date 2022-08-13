#include "GAME.h"

//Game Class Functions

//Default Constructor
Game::Game() {
    size = 3;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = player.none;
        }
    }
}

//Parameterised Constructor
Game::Game(int max) {
    size = max;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = player.none;
        }
    }
}

//This Function has whole functionality of the game
void Game::play() {
    bool end = false;
    do {
        system("CLS");
        Display();
        cout << "Enter your move: " << endl;
        getHumanMove();
        if (checkWin(player.human)) {
            Display();
            cout << "You Won" << endl;
            end = true;
            break;
        }
        else if (isDraw()) {
            Display();
            cout << "Game Tied!" << endl;
            end = true;
            break;
        }
        Move aimove = minimax();
        board[aimove.row][aimove.col] = player.ai;
        if (checkWin(player.ai)) {
            Display();
            cout << "Computer won" << endl;
            end = true;
            break;
        }
    } while (end == false);
}

void Game::getHumanMove() {
    bool wrong = true;
    int i = 0;
    int j = 0;
    cin >> i >> j;
    while (board[i][j] != player.none or i < 0 or i >= size or j < 0 or j >= size) {
        cout << "Invalid move!" << endl;
        cout << "Enter your move: ";
        cin >> i >> j;
    }
    board[i][j] = player.human;
}

bool Game::checkWin(char mark) {
    int count = 0;

    //To check vertically
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[j][i] == mark) {
                count++;
            }
            else {
                break;
            }
        }
        if (count == size) {
            return true;
        }
        else {
            count = 0;
        }
    }

    //To check horizontally
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == mark) {
                count++;
            }
            else {
                break;
            }
        }
        if (count == size) {
            return true;
        }
        else {
            count = 0;
        }
    }

    //To check right diagonal
    for (int i = 0; i < size; i++) {
        if (board[i][i] == mark) {
            count++;
        }
    }
    if (count == size) {
        return true;
    }
    else {
        count = 0;
    }

    //To check left diagonal
    for (int i = 0; i < size; i++) {
        if (board[i][(size - 1) - i] == mark) {
            count++;
        }
    }
    if (count == size) {
        return true;
    }
    else {
        count = 0;
        return false;
    }
}

bool Game::isDraw() {
    bool tie = false;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == player.none) {
                tie = true;
                break;
            }
        }
    }
    return tie == true ? false : true;
}

//Min-Max Algorithm
Move Game ::minimax() {
    int score = numeric_limits<int>::max();
    Move move;
    int level = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == player.none) {
                board[i][j] = player.ai;
                int temp = maxSearch(level, numeric_limits<int>::min(), numeric_limits<int>::max());
                if (temp < score) {
                    score = temp;
                    move.row = i;
                    move.col = j;
                }
                board[i][j] = player.none;
            }
        }
    }
    return move;
}

int Game::maxSearch(int level, int alpha, int beta) {
    if (checkWin(player.human)) {
        return 10;
    }
    else if (checkWin(player.ai)) {
        return -10;
    }
    else if (isDraw()) {
        return 0;
    }
    int score = numeric_limits<int>::min();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == player.none) {
                board[i][j] = player.human;
                score = max(score, minSearch(level + 1, alpha, beta) - level);
                alpha = max(alpha, score);
                board[i][j] = player.none;
                if (beta <= alpha) {
                    return alpha;
                }
            }
        }
    }
    return score;
}

int Game::minSearch(int level, int alpha, int beta) {
    if (checkWin(player.human)) {
        return 10;
    }
    else if (checkWin(player.ai)) {
        return -10;
    }
    else if (isDraw()) {
        return 0;
    }
    int score = numeric_limits<int>::max();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == player.none) {
                board[i][j] = player.ai;
                score = min(score, maxSearch(level + 1, alpha, beta) + level);
                beta = min(beta, score);
                board[i][j] = player.none;
                if (beta <= alpha) {
                    return beta;
                }
            }
        }
    }
    return score;
}

void Game::Display() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] != player.none) {
                cout << " " << board[i][j] << "     ";
            }
            else {
                cout << " " << i << j << "    ";
            }
        }
        cout << endl;
    }
}