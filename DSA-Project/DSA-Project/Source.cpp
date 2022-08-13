//Tic Tac Toe Game Project
#include <iostream>
#include"GAME.h"
using namespace std;

int main() {
    int again = 0;
    int size = 0;
    do {
        system("CLS");
        cout << "Enter the size of game NxN: ";
        cin >> size;
        while (size < 3 or size > 10) {
            cout << "Invalid size! range is 3 to 10" << endl; //Range for the game size is 3-10
            cout << "Enter the size of game NxN: ";
            cin >> size;
        }
        Game tictactoe(size);
        tictactoe.play();
        cout << "Press 1 if you want to play again: ";
        cin >> again;
    } while (again == 1);
    cout << endl;
    system("pause");
    return 0;
}