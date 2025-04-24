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

class Firma {
    public:
    string name;
    string nip;
    string date;
    string mail;

    public:
    Firma(const string &_name, const string &_nip, const string &_date, const string &_mail) {


        // NIP
        if (_name.length() < 3 || _name.length() > 100) {
            throw length_error("Błąd");
        }

        if (_nip.length() != 10) {
            throw length_error("NIP musi mieć 10 znaków");
        }

        if (!isDigit(_nip)) {
            throw invalid_argument("Numer NIP musi zawierać tylko liczby");
        }

        // DATA

        if (_date.length() != 10) {
            throw length_error("Nieprawidłowa długość daty");
        }

        if (_date[4] != '-' || _date[7] != '-') {
            throw invalid_argument("Nieprawidłowy format daty");
        }

        name = _name;
        nip = _nip;
        date = _date;
        mail = _mail;
    }
};