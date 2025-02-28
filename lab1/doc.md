## Napisz program, który realizuje menu użytkownika korzystając z pętli do ... while.:

```
1. Wypisz ilość argumentów programu
2. Wypisz wybrany argument programu
3. Wypisz wszystkie argumenty programu
4. Zakończ program
```

W przypadku, gdy użytkownik wybierze inną opcję niż od 1 do 4, wypisz błąd na wyjście błędów (przez std::cerr).

```cpp
#include <iostream>  // Biblioteka do wejścia/wyjścia

int main(int argc, char* argv[]) {  // Funkcja main z argumentami
    int wybor, i;  // Zmienna do wyboru opcji i indeksu argumentu

    do {
        // Wyświetlenie menu
        std::cout << "\n1. Liczba argumentów\n";
        std::cout << "2. Wybrany argument\n";
        std::cout << "3. Wszystkie argumenty\n";
        std::cout << "4. Koniec\n";
        std::cout << "Wybór: ";
        std::cin >> wybor;  // Wczytanie opcji od użytkownika

        if (wybor == 1)  // Wypisanie liczby argumentów
            std::cout << argc << "\n";

        else if (wybor == 2) {  // Pobranie i wyświetlenie konkretnego argumentu
            std::cout << "Numer: ";
            std::cin >> i;
            std::cout << (i >= 0 && i < argc ? argv[i] : "Błąd!") << "\n";  // Sprawdzenie poprawności indeksu
        } 

        else if (wybor == 3) {  // Wypisanie wszystkich argumentów
            for (int j = 0; j < argc; j++)
                std::cout << argv[j] << "\n";
        } 

        else if (wybor != 4)  // Obsługa błędnego wyboru
            std::cerr << "Błąd!\n";

    } while (wybor != 4);  // Pętla działa dopóki użytkownik nie wybierze 4

    return 0;  // Zakończenie programu
}
```

## Jak uruchomić?
1. Skompiluj program:
```
g++ -o <nazwa> <nazwa pliku>.cpp
```

2. Uruchom program z argumentami:

```
./<nazwa> arg1 arg2 arg3
```