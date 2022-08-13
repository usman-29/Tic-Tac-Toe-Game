#pragma once
#include<iostream>
#include<algorithm>
using namespace std;
#define MAX 10

//Structure for Move
struct Move {
    int row = 0;
    int col = 0;
};

//Structure for Player
struct Player {
    char none = '-';
    char human = 'X';
    char ai = 'O';
};

//Game Class
class Game {
private:
    Player player;
    char board[MAX][MAX];
    int size;
public:
    Game();
    Game(int max);
    void play();
    void getHumanMove();
    bool checkWin(char mark);
    bool isDraw();
    Move minimax();
    int maxSearch(int level, int alpha, int beta);
    int minSearch(int level, int alpha, int beta);
    void Display();
};
