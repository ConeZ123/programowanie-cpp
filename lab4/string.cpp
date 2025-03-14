#include <iostream>
#include <cstdlib> 
#include <string>

namespace strutil {
    std::string toUpper(const std::string& original) {
        std::string result = original;
        for (char& c : result) {
            if (c >= 'a' && c <= 'z') {
                c -= 32;
            }
        }
        return result;
    }

    std::string randStr(int length) {
        std::string result;
        for (int i = 0; i < length; i++) {
            result += 'a' + std::rand() % 26;
        }
        return result;
    }

    int longestWordLength(const std::string& str) {
        int maxLength = 0, currentLength = 0;

        for (char c : str) {
            if (c == ' ') {
                if (currentLength > maxLength) {
                    maxLength = currentLength;
                }
                currentLength = 0;
            } else {
                currentLength++;
            }
        }

        if (currentLength > maxLength) {
            maxLength = currentLength;
        }
        return maxLength;
    }

    void rot13(std::string& str) {
        for (char& c : str) {
            if (c >= 'A' && c <= 'Z') {
                c = (c - 'A' + 13) % 26 + 'A';
            } else if (c >= 'a' && c <= 'z') {
                c = (c - 'a' + 13) % 26 + 'a';
            }
        }
    }

    int countOccurrence(const std::string& text, const std::string& word) {
        if (word.empty()) {
            return 0;
        }

        int count = 0;
        int textLen = text.length();
        int wordLen = word.length();

        for (int i = 0; i <= textLen - wordLen; i++) {
            bool match = true;

            for (int j = 0; j < wordLen; j++) {
                if (text[i + j] != word[j]) {
                    match = false;
                    break;
                }
            }

            if (match) {
                count++;
                i += wordLen - 1;
            }
        }
        return count;
    }
}

int main() {
    std::string input;
    std::cout << "Podaj tekst: ";
    std::getline(std::cin, input);

    while (true) {
        std::cout << "\nWybierz opcję:\n";
        std::cout << "1. Zamień na wielkie litery\n";
        std::cout << "2. Wygeneruj losowy string\n";
        std::cout << "3. Znajdź długość najdłuższego słowa\n";
        std::cout << "4. Zakoduj ROT13\n";
        std::cout << "5. Policz wystąpienia słowa\n";
        std::cout << "6. Wyjdź\n";
        std::cout << "Twój wybór: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 6) break;

        switch (choice) {
            case 1:
                std::cout << "Wielkie litery: " << strutil::toUpper(input) << "\n";
                break;
            case 2: {
                int length;
                std::cout << "Podaj długość losowego stringa: ";
                std::cin >> length;
                std::cin.ignore();
                std::cout << "Losowy string: " << strutil::randStr(length) << "\n";
                break;
            }
            case 3:
                std::cout << "Długość najdłuższego słowa: " << strutil::longestWordLength(input) << "\n";
                break;
            case 4:
                strutil::rot13(input);
                std::cout << "Zakodowany ROT13: " << input << "\n";
                break;
            case 5: {
                std::string word;
                std::cout << "Podaj słowo do wyszukania: ";
                std::getline(std::cin, word);
                std::cout << "Liczba wystąpień: " << strutil::countOccurrence(input, word) << "\n";
                break;
            }
            default:
                std::cout << "Niepoprawny wybór, spróbuj ponownie.\n";
        }
    }

    return 0;
}
