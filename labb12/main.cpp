#include "CurlRAII.hpp"
#include <getopt.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static const char* HELP =
R"(imgw v1.0 – weather data client
usage: imgw [-t type] [-l] id
options:
  -l            list all station IDs
  -t <param>    print only given parameter (temperatura | cisnienie | wilgotnosc_wzgledna | …)
  -h            display this help)";


static std::vector<std::string> split_csv_line(const std::string& line)
{
    std::vector<std::string> tokens;
    std::istringstream       ss(line);
    std::string              field;
    while (std::getline(ss, field, ','))
        tokens.emplace_back(field);
    return tokens;
}

int main(int argc, char* argv[])
{
    CurlGlobal curl_raii;        

    bool list_mode      = false;
    std::string only_ty;

    int opt;
    while ((opt = getopt(argc, argv, "hlt:")) != -1) {
        switch (opt) {
            case 'l': list_mode = true; break;
            case 't': only_ty   = optarg; break;
            case 'h': std::cout << HELP << '\n'; return 0;
            default :
                std::cerr << HELP << '\n';
                return 1;
        }
    }

    try
    {
        if (list_mode) {
            // --- tryb -l 
            std::string url = "https://danepubliczne.imgw.pl/api/data/synop/format/csv";
            std::string body = fetch_url(url);

            std::istringstream csv(body);
            std::string line;
            std::getline(csv, line);               // pomijamy nagłówek
            while (std::getline(csv, line)) {
                auto cols = split_csv_line(line);
                if (cols.size() >= 2)
                    std::cout << cols[0] << ',' << cols[1] << '\n';
            }
            return 0;
        }

        // --- zapytanie o konkretną stację 
        if (optind >= argc) {
            std::cerr << "Brak ID stacji.\n\n" << HELP << '\n';
            return 1;
        }
        std::string station_id = argv[optind];

        std::string url = "https://danepubliczne.imgw.pl/api/data/synop/id/"
                        + station_id + "/format/csv";
        std::string body = fetch_url(url);

        // Jeśli nie podano -t: wypisz pełny CSV otrzymany od IMGW
        if (only_ty.empty()) {
            std::cout << body;
            return 0;
        }

        // --- tryb -t <param> 
        std::istringstream csv(body);
        std::string header_line, data_line;
        std::getline(csv, header_line);
        std::getline(csv, data_line);

        auto headers = split_csv_line(header_line);
        auto values  = split_csv_line(data_line);

        auto it = std::find(headers.begin(), headers.end(), only_ty);
        if (it == headers.end()) {
            std::cerr << "Nieznany parametr: " << only_ty << '\n';
            return 1;
        }
        size_t idx = std::distance(headers.begin(), it);
        if (idx >= values.size()) {
            std::cerr << "Brak wartości dla parametru.\n";
            return 1;
        }
        std::cout << values[idx] << '\n';
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Błąd: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}
