#include <iostream>

int main(int argc, char* argv[]) {
    int wybor, i;

    do {
        std::cout << "\n1. Liczba argumentów\n";
        std::cout << "2. Wybrany argument\n";
        std::cout << "3. Wszystkie argumenty\n";
        std::cout << "4. Koniec\n";
        std::cout << "Wybór: ";
        std::cin >> wybor;

        if (wybor == 1)
            std::cout << argc << "\n";

        else if (wybor == 2) {
            std::cout << "Numer: ";
            std::cin >> i;
            std::cout << (i >= 0 && i < argc ? argv[i] : "Błąd!") << "\n";
        } 

        else if (wybor == 3) {
            for (int j = 0; j < argc; j++)
                std::cout << argv[j] << "\n";
        } 

        else if (wybor != 4)
            std::cerr << "Błąd!\n";

    } while (wybor != 4);

    return 0;
}