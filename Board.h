#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <cstdlib>
using namespace std;

const int SIZE = 8;

class Board {
private:
    char grid[SIZE][SIZE];

public:
    Board() { init(); }

    void init() {
        char start[SIZE][SIZE] = {
            {'r','n','b','q','k','b','n','r'},
            {'p','p','p','p','p','p','p','p'},
            {' ',' ',' ',' ',' ',' ',' ',' '},
            {' ',' ',' ',' ',' ',' ',' ',' '},
            {' ',' ',' ',' ',' ',' ',' ',' '},
            {' ',' ',' ',' ',' ',' ',' ',' '},
            {'P','P','P','P','P','P','P','P'},
            {'R','N','B','Q','K','B','N','R'}
        };

        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                grid[i][j] = start[i][j];
    }

    char get(int r, int c) const { return grid[r][c]; }
    void set(int r, int c, char p) { grid[r][c] = p; }

    void move(int r1, int c1, int r2, int c2) {
        grid[r2][c2] = grid[r1][c1];
        grid[r1][c1] = ' ';
    }

    void display(int curR, int curC, bool selected) {
        system("cls");
        cout << "WASD: Move | E: Select/Move | Q: Quit\n";
        if (selected) cout << "Piece selected\n\n";
        else cout << "\n";

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (i == curR && j == curC)
                    cout << "[" << grid[i][j] << "]";
                else
                    cout << " " << grid[i][j] << " ";
            }
            cout << endl;
        }
    }
};

#endif

