#include <iostream>
#include <algorithm>
#include <string>
#include <chrono>
#include <cstdlib> 
#include <cctype>
#include <format>
#include <tuple>
#include <stdexcept>
using namespace std;

std::tuple<int, int, int> getCurrentDate() {
    const auto now = std::chrono::system_clock::now();
    std::chrono::year_month_day ymd = std::chrono::floor<std::chrono::days>(now);
    return std::make_tuple(int(ymd.year()), unsigned(ymd.month()), unsigned(ymd.day()));
}

std::tuple<int, int, int> parseDate(const std::string &date) {
    int year = std::stoi(date);
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));
    return std::make_tuple(year, month, day);
}

bool isDigit(const string& str) {
    for (char c : str) {
        if (isdigit(c)) {
            return true;
        }
    }
    return false;
}

bool containsAt(const string& str) {
    for (char c : str) {
        if (c == '@') {
            return true;
        }
    }
    return false;
}

bool isValidNIPChecksum(const string& nip) {
    int weights[9] = {6, 5, 7, 2, 3, 4, 5, 6, 7};
    int sum = 0;

    for (int i = 0; i < 9; i++) {
        sum += (nip[i] - '0') * weights[i];
    }
    int control = sum % 11;
    return control == (nip[9] - '0');
}

class Firma {
    public:
    string name;
    string nip;
    string date;
    string mail;

    public:
    Firma(const string &_name, const string &_nip, const string &_date, const string &_mail) {


        // NIP check
        if (_name.length() < 3 || _name.length() > 100) {
            throw length_error("Błąd");
        }

        if (_nip.length() != 10) {
            throw length_error("NIP musi mieć 10 znaków");
        }

        if (!isDigit(_nip)) {
            throw invalid_argument("Numer NIP musi zawierać tylko liczby");
        }

        if (!isValidNIPChecksum(_nip)) {
            throw domain_error("Niepoprawna cyfra kontrolna numeru NIP");
        }

        // DATA check

        if (_date.length() != 10) {
            throw length_error("Nieprawidłowa długość daty");
        }

        if (_date[4] != '-' || _date[7] != '-') {
            throw invalid_argument("Nieprawidłowy format daty");
        }

        auto [year, month, day] = parseDate(_date);
        auto [currentYear, currentMonth, currentDay] = getCurrentDate();

        if (year < 2000 || year > currentYear) {
            throw domain_error("Rok rejestracji musi być w przedziale [2000, BIEŻĄCY ROK]");
        }

        if (month < 1 || month > 12 || (year == currentYear && month > currentMonth)) {
            throw domain_error("Nieprawidłowy miesiąc rejestracji");            
        }

        const int daysInMonths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int maxDay = daysInMonths[month - 1];
        if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) {
            maxDay = 29;
        }

        if (year == currentYear && month == currentMonth) {
            maxDay = currentDay;
        }

        if (day < 1 || day > maxDay) {
            throw domain_error("Nieprawidłowy dzień rejestracji");
        }

        // mail check

        if (!containsAt(_mail)) {
            throw invalid_argument("Adres email musi zawierać '@'");
        }

        name = _name;
        nip = _nip;
        date = _date;
        mail = _mail;
    }
};

int main() {
    try {
        Firma f("XYZ", "1234563218", "2024-04-24", "xyz@xyz.pl");
        cout << "Firma została poprawnie utworzona \n";
    } catch (const exception& e) {
        cerr << "Błąd: " << e.what() << "\n";
    }

    return 0;
}