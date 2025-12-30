#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include <string>
#include <conio.h>
#include <cctype>
using namespace std;

class Game {
private:
    Board board;
    bool whiteTurn;
    bool hasSelection;
    int selR, selC;
    int curR, curC;
    bool vsComputer;
    bool gameOver;
    string winner;

public:
    Game(bool computerMode) {
        whiteTurn = true;
        hasSelection = false;
        curR = 7; curC = 0;
        vsComputer = computerMode;
        gameOver = false;
    }

    int pieceValue(char p) {
        p = tolower(p);
        if (p == 'p') return 1;
        if (p == 'n' || p == 'b') return 3;
        if (p == 'r') return 5;
        if (p == 'q') return 9;
        if (p == 'k') return 100;
        return 0;
    }

    bool correctTurn(char p) {
        if (whiteTurn && isupper(p)) return true;
        if (!whiteTurn && islower(p)) return true;
        return false;
    }

    bool isPathClear(int r1, int c1, int r2, int c2) {
        int dr = (r2 > r1) - (r2 < r1);
        int dc = (c2 > c1) - (c2 < c1);

        r1 += dr; c1 += dc;
        while (r1 != r2 || c1 != c2) {
            if (board.get(r1, c1) != ' ') return false;
            r1 += dr; c1 += dc;
        }
        return true;
    }

    bool isValidMove(int r1, int c1, int r2, int c2) {
        char p = board.get(r1, c1);
        char t = board.get(r2, c2);

        if (p == ' ') return false;
        if (t != ' ' && correctTurn(t)) return false;

        int dr = r2 - r1;
        int dc = c2 - c1;
        if (p == 'P') {
            if (dc == 0 && dr == -1 && t == ' ') return true;
            if (r1 == 6 && dc == 0 && dr == -2 && t == ' ') return true;
            if (abs(dc) == 1 && dr == -1 && islower(t)) return true;
        }
        if (p == 'p') {
            if (dc == 0 && dr == 1 && t == ' ') return true;
            if (r1 == 1 && dc == 0 && dr == 2 && t == ' ') return true;
            if (abs(dc) == 1 && dr == 1 && isupper(t)) return true;
        }
        if (tolower(p) == 'r' && (r1 == r2 || c1 == c2)) return isPathClear(r1,c1,r2,c2);
        if (tolower(p) == 'b' && abs(dr) == abs(dc)) return isPathClear(r1,c1,r2,c2);
        if (tolower(p) == 'q' && (r1 == r2 || c1 == c2 || abs(dr) == abs(dc))) return isPathClear(r1,c1,r2,c2);
        if (tolower(p) == 'n' && ((abs(dr) == 2 && abs(dc) == 1) || (abs(dr) == 1 && abs(dc) == 2))) return true;
        if (tolower(p) == 'k' && abs(dr) <= 1 && abs(dc) <= 1) return true;

        return false;
    }

    bool isKingAlive(bool white) {
        char k = white ? 'K' : 'k';
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (board.get(i, j) == k) return true;
        return false;
    }

    bool isKingInCheck(bool white) {
        char king = white ? 'K' : 'k';
        int kr = -1, kc = -1;

        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (board.get(i, j) == king) { kr = i; kc = j; }

        if (kr == -1) return true;

        for (int r = 0; r < SIZE; r++)
            for (int c = 0; c < SIZE; c++) {
                char p = board.get(r, c);
                if (p != ' ' && (isupper(p) != white))
                    if (isValidMove(r, c, kr, kc)) return true;
            }
        return false;
    }

    bool isSafeMove(int r1, int c1, int r2, int c2, bool white) {
        char from = board.get(r1, c1);
        char to   = board.get(r2, c2);

        board.move(r1, c1, r2, c2);
        bool safe = !isKingInCheck(white);
        board.set(r1, c1, from);
        board.set(r2, c2, to);

        return safe;
    }

    bool hasAnyMove(bool white) {
        for (int r1 = 0; r1 < SIZE; r1++)
            for (int c1 = 0; c1 < SIZE; c1++) {
                char p = board.get(r1, c1);
                if (p != ' ' && (isupper(p) == white))
                    for (int r2 = 0; r2 < SIZE; r2++)
                        for (int c2 = 0; c2 < SIZE; c2++)
                            if (isValidMove(r1, c1, r2, c2) && isSafeMove(r1, c1, r2, c2, white))
                                return true;
            }
        return false;
    }

    void checkGameState() {
        if (!isKingAlive(true))  { gameOver = true; winner = "Black"; return; }
        if (!isKingAlive(false)) { gameOver = true; winner = "White"; return; }
        if (isKingInCheck(whiteTurn) && !hasAnyMove(whiteTurn)) {
            gameOver = true;
            winner = whiteTurn ? "Black" : "White";
        }
    }

    void computerMove() {
        int bestScore = -1000;
        int br1 = -1, bc1 = -1, br2 = -1, bc2 = -1;

        for (int r1 = 0; r1 < SIZE; r1++)
            for (int c1 = 0; c1 < SIZE; c1++) {
                char p = board.get(r1, c1);
                if (islower(p))
                    for (int r2 = 0; r2 < SIZE; r2++)
                        for (int c2 = 0; c2 < SIZE; c2++)
                            if (isValidMove(r1, c1, r2, c2) && isSafeMove(r1, c1, r2, c2, false)) {
                                int score = pieceValue(board.get(r2, c2));
                                if (score >= bestScore) {
                                    bestScore = score;
                                    br1 = r1; bc1 = c1;
                                    br2 = r2; bc2 = c2;
                                }
                            }
            }

        if (br1 != -1) {
            board.move(br1, bc1, br2, bc2);
            whiteTurn = true;
            checkGameState();
        } else {
            gameOver = true;
            winner = "White";
        }
    }

    void run() {
        char key;

        while (!gameOver) {
            board.display(curR, curC, hasSelection);

            if (vsComputer && !whiteTurn) {
                computerMove();
                continue;
            }

            key = toupper(_getch());

            if (key == 'Q') break;
            if (key == 'W' && curR > 0) curR--;
            if (key == 'S' && curR < 7) curR++;
            if (key == 'A' && curC > 0) curC--;
            if (key == 'D' && curC < 7) curC++;

            if (key == 'E') {
                if (!hasSelection) {
                    char p = board.get(curR, curC);
                    if (p != ' ' && correctTurn(p)) {
                        selR = curR; selC = curC;
                        hasSelection = true;
                    }
                } else {
                    if (isValidMove(selR, selC, curR, curC) &&
                        isSafeMove(selR, selC, curR, curC, whiteTurn)) {
                        board.move(selR, selC, curR, curC);
                        whiteTurn = !whiteTurn;
                        checkGameState();
                    }
                    hasSelection = false;
                }
            }
        }

        system("cls");
        cout << "GAMEOVER\n" << winner << " wins!\n";
        system("pause");
    }
};

#endif

