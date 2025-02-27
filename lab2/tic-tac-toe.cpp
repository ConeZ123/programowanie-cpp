#include <iostream>

const int SIZE = 3;

void showBoard(char board[SIZE][SIZE]) {
    std:: cout << "\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            std::cout << " " << board[i][j] << " ";
            if (j < SIZE - 1) {
                std::cout << "|";
            }
        }
    }
}

void clearBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

bool isFinished(char board[SIZE][SIZE], char *winner) {
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            *winner = board[i][0];
            return true;
        }
    }
}

bool setPoint(char board[SIZE][SIZE], unsigned int x, unsigned int y) {
        
}