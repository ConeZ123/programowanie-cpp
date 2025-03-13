#include <iostream>
#include <cstdlib> 

void showBoard(char **board, int size) {
    std::cout << "\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << " " << board[i][j] << " ";
            if (j < size - 1) std::cout << "|";
        }
        std::cout << "\n";
    }
}

void clearBoard(char **board, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            board[i][j] = ' ';  
}

bool isFinished(char **board, int size, char &winner) {
    
    for (int i = 0; i < size; i++) {
        bool rowWin = true; 
        bool colWin = true;
        for (int j = 1; j < size; j++) {
            if (board[i][j] != board[i][0] || board[i][0] == ' ') {
                rowWin = false;
            }     
            if (board[j][i] != board[0][i] || board[0][i] == ' ') {
                colWin = false;
            }
        }
        if (rowWin) { 
            winner = board[i][0]; 
            return true; 
        }
        if (colWin) { 
            winner = board[0][i]; 
            return true; 
        }
    }

    bool diag1 = true; 
    bool diag2 = true;
    for (int i = 1; i < size; i++) {
        if (board[i][i] != board[0][0] || board[0][0] == ' ') {
            diag1 = false;
        }
        if (board[i][size - i - 1] != board[0][size - 1] || board[0][size - 1] == ' ') {
            diag2 = false;
        }
    }
    if (diag1) { 
        winner = board[0][0]; 
        return true; 
    }
    if (diag2) { 
        winner = board[0][size - 1]; 
        return true; 
    }

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (board[i][j] == ' ') {
                return false;
            }

    winner = ' '; 
    return true;
}

bool setPoint(char **board, int size, int x, int y, char player) {
    if (x >= size || y >= size || x < 0 || y < 0 || board[x][y] != ' ') {
        return false;
    }
    board[x][y] = player;
    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Użycie: " << argv[0] << " <rozmiar planszy>\n";
        return 1;
    }

    int size = std::atoi(argv[1]);
    if (size < 3) {
        std::cerr << "Rozmiar planszy musi być co najmniej 3x3!\n";
        return 1;
    }

    char **board = new char*[size];
    for (int i = 0; i < size; i++)
        board[i] = new char[size];

    clearBoard(board, size);

    char winner = ' ';
    char currentPlayer = 'X';
    int x, y;

    while (!isFinished(board, size, winner)) {
        showBoard(board, size);
        std::cout << "Gracz " << currentPlayer << ", podaj wiersz i kolumnę (0-" << size-1 << "): ";
        std::cin >> x >> y;

        if (setPoint(board, size, x, y, currentPlayer)) {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        } else {
            std::cout << "Nieprawidłowy ruch! Spróbuj ponownie.\n";
        }
    }

    showBoard(board, size);
    if (winner == ' ') {
        std::cout << "Wynik: remis!\n";
    } else {
        std::cout << "Zwycięzca: " << winner << "!\n";
    }

    for (int i = 0; i < size; i++)
        delete[] board[i];
    delete[] board;

    return 0;
}