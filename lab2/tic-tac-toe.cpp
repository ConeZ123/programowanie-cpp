#include <iostream>

const int SIZE = 3;

void showBoard(char board[SIZE][SIZE]) {
    std::cout << "\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            std::cout << " " << board[i][j] << " ";
            if (j < SIZE - 1) {
                std::cout << "|";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


void clearBoard(char board[3][3]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

bool isFinished(char board[3][3], char *winner) {
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            *winner = board[i][0];
            return true;
        }
        if (board[i][0] != ' ' && board[0][i] == board[1][0] && board[1][i] == board[2][i]) {
            *winner = board[0][i];
            return true;
        }
    }

    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        *winner = board[0][0];
        return true;
    }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        *winner = board[0][2];
        return true;
    }

    for (int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                return false;
            } 
        }
    }
    *winner = ' ';
    return true;
}

bool setPoint(char board[3][3], unsigned int x, unsigned int y, char player) {
    if (x >= SIZE || y >= SIZE || board[x][y] != ' ') {
        return false;
    }
    board[x][y] = player;
    return true;
}

int main() {
    char board[SIZE][SIZE];
    clearBoard(board);
    char winner = ' ';
    char currentPlayer = 'X';
    int x, y;

    while (!isFinished(board, &winner)) {
        showBoard(board);
        std::cout << "Gracz " << currentPlayer << ", podaj wiersz i kolumne: ";
        std::cin >> x >> y;

        if (setPoint(board, x, y, currentPlayer)) {
            currentPlayer = (currentPlayer == 'X') ? 'O': 'X';
        } else {
            std::cout << "Nieprawidłowy ruch";
        }
    }

    showBoard(board);
    if (winner == ' ') {
        std::cout << "Wynik: remis! \n";
    } else {
        std::cout << "Zwyciezca: " << winner << "\n";
    }
    return 0;
}