// NIEDOKONCZONE

#include <iostream>
#include <cstdlib>

void showBoard(char **board, int size) {
    std::cout << "\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << " " << board[i][j] << " ";
            if (j < size - 1) {
                std::cout << "|";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


void clearBoard(char **board, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = ' ';
        }
    }
}

bool isFinished(char **board, int size, char *winner) {
    for (int i = 0; i < size; i++) {
        bool row_win = true;
        bool col_win = true;

        for (int j = 1; j < size; j++) {
            if (board[i][j] != board[1][0] || board[i][0] == ' ') {
                row_win = false;
            }

            if (board[j][i] != board[0][1] || board[0][i] == ' ') {
                col_win = false;
            }

        if (row_win) {
            *winner = board[i][0];
            return true;
        }

        if (col_win) {
            *winner = board[0][i];
            return true;
        }
            
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] = ' ') {
                    return false;
                }
            }
        }

        *winner = ' ';
        return true;

        bool diag1 = true;
        bool diag2 = true;

        for (int i = 1; i < size; i++) {
           if (board[i][i] != board[0][0] || board[0][0] == ' ') {
                diag1 = false;
           }
           if (board[i][i - size - 1] != board[0][size - 1] || board[0][size - 1] == ' ');
                diag2 = false; 
        }

        if (diag1) {
            *winner = board[0][0];
            return true;
        }
        
        if (diag2) {
            *winner = board[0][size - 1];
            return true;
        }

    }

}

bool setPoint(char **board, int size, unsigned int x, unsigned int y, char player) {
    if (x >= size || y >= size || board[x][y] != ' ') {
        return false;
    }
    board[x][y] = player;
    return true;
}

int main(int argc, char* argv[]) {
    int size = std::atoi(argv[1]);
    if (size < 3) {
        std::cerr << "Rozmiar planszy musi byc co najmniej 3x3";
        return 1;
    }

    char **board = new char*[size];

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