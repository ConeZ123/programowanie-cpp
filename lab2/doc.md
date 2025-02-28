## Kółko i krzyżyk

Napisz prostą grę ,,kółko i krzyżyk’'.

Wykorzystaj dwuwymiarową tablicę znakową (char). Unikaj zmiennych globalnych, przekazuj kontekst do funkcji.

Typ char - zmienna 8-bitowa która odpowiada znakowi z kodu ASCII. Przyjmujemy, że pole puste to wartość ’ ’ (spacja), krzyżyk to ‘X’, a kółko to ‘O’.

Zaimplementuj funkcje:

- void showBoard(char board[3][3]) - wyswietlaj grę w formie tekstowej

- void clearBoard(char board[3][3]) - wyczyść grę (ustaw wszystkie pola na spacje),

- bool isFinished(char board[3][3], char *winner) - sprawdz, czy gra jest już zakończona, w dodatkowym argumencie, przekażesz na zewnątrz funkcji kto został zwycięzcą jeżeli to już koniec,

- bool setPoint(char board[3][3], unsigned int x, unsigned int y, char player) - zwraca fałsz gdy pole jest już zajęte lub prawdę gdy jest wolne i zostało uzyte,

```
O | X | O 
X | X | O
O | O | X
Wynik: remis
```

## Jak uruchomić?
1. Skompiluj program:
```
g++ -o <nazwa> <nazwa_pliku>.cpp
```

2. Uruchom program:

```
./<nazwa>
```

## Działanie programu

```cpp
#include <iostream>

const int SIZE = 3; // Definiujemy stałą określającą rozmiar planszy

// Funkcja wyświetlająca aktualny stan planszy
void showBoard(char board[SIZE][SIZE]) {
    std::cout << "\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            std::cout << " " << board[i][j] << " ";
            if (j < SIZE - 1) {
                std::cout << "|"; // Separator pionowy między kolumnami
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// Funkcja czyszcząca planszę (ustawiająca wszystkie pola na spacje)
void clearBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

// Funkcja sprawdzająca, czy gra się zakończyła i określająca zwycięzcę
bool isFinished(char board[SIZE][SIZE], char *winner) {
    // Sprawdzanie wierszy i kolumn
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            *winner = board[i][0]; // Zwycięstwo w wierszu
            return true;
        }
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            *winner = board[0][i]; // Zwycięstwo w kolumnie
            return true;
        }
    }

    // Sprawdzanie przekątnych
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        *winner = board[0][0];
        return true;
    }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        *winner = board[0][2];
        return true;
    }

    // Sprawdzanie, czy na planszy są jeszcze wolne pola
    for (int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                return false; // Gra jeszcze trwa
            } 
        }
    }
    *winner = ' '; // Jeśli brak wolnych pól, to remis
    return true;
}

// Funkcja ustawiająca znak gracza na podanej pozycji
bool setPoint(char board[SIZE][SIZE], unsigned int x, unsigned int y, char player) {
    if (x >= SIZE || y >= SIZE || board[x][y] != ' ') { // Sprawdzanie poprawności ruchu
        return false;
    }
    board[x][y] = player; // Ustawienie znaku gracza na planszy
    return true;
}

int main() {
    char board[SIZE][SIZE]; // Deklaracja planszy
    clearBoard(board); // Czyszczenie planszy przed rozpoczęciem gry
    char winner = ' '; // Zmienna przechowująca zwycięzcę
    char currentPlayer = 'X'; // Pierwszy gracz to 'X'
    int x, y;

    // Pętla gry - trwa, dopóki gra się nie zakończy
    while (!isFinished(board, &winner)) {
        showBoard(board); // Wyświetlenie aktualnego stanu planszy
        std::cout << "Gracz " << currentPlayer << ", podaj wiersz i kolumne: ";
        std::cin >> x >> y;

        // Próba wykonania ruchu
        if (setPoint(board, x, y, currentPlayer)) {
            // Zmiana gracza po poprawnym ruchu
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        } else {
            std::cout << "Nieprawidłowy ruch";
        }
    }

    showBoard(board); // Wyświetlenie końcowego stanu planszy
    if (winner == ' ') {
        std::cout << "Wynik: remis! \n";
    } else {
        std::cout << "Zwyciezca: " << winner << "\n";
    }
    return 0;
}
```