#include <iostream>
#include "Game.h"

using namespace std;

int main() {
    int choice;

    cout << "1. Player vs Player\n";
    cout << "2. Player vs Computer\n";
    cout << "Choose mode: ";
    cin >> choice;

    Game game(choice == 2);
    game.run();

    return 0;
}

