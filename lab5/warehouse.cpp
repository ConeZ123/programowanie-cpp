#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

struct Product {
    std::string name;
    unsigned int price;
    unsigned int qty;
};

void loadFromFile(const std::string& filename, std::vector<Product>& products) {
    ifstream input;
    input.open(filename.c_str());

    if (!input.is_open()) {
        cerr << "Nie mozna otworzyc pliku: " << filename;
        return;
    }

    Product p;
    while (input >> p.name >> p.price >> p.qty) {
        products.push_back(p);
    }
    input.close();
}

void saveToFile(const std::string& filename, const std::vector<Product>& products) {
ofstream output;
    output.open(filename.c_str());

    if (!output.is_open()) {
        cerr << "Blad zapisu do pliku: " << filename;
        return;
    }

    for (size_t i = 0; i < products.size(); i++) {
        output << products[i].name << " " << products[i].price << " " << products[i].qty << "\n";
    }
    output.close();
}

void displayProducts(const std::vector<Product>& products) {
    cout << "Magazyn:\n";
    cout << "Nazwa\tCena\tIlosc\n";
    for (size_t i = 0; i < products.size(); i++) {
        cout << products[i].name << "\t" << products[i].price << "\t" << products[i].qty << "\n";
    }
}

void addProduct(std::vector<Product>& products) {
    Product p;
    cout << "Podaj nazwe produktu: ";
    cin >> p.name;
    cout << "Podaj cene produktu: ";
    cin >> p.price;
    cout << "Podaj ilosc produktu: ";
    cin >> p.qty;

    if (p.price == 0 || p.qty == 0) {
        std::cerr << "Cena i ilosc musza byc wieksze od 0!\n";
        return;
    }

    products.push_back(p);
}

void removeProduct(std::vector<Product>& products) {
    string name;
    cout << "Podaj nazwe produktu do usuniecia: ";
    cin >> name;

    bool found = false;
    for (size_t i = 0; i < products.size(); i++) {
        if (products[i].name == name) {
            products.erase(products.begin() + i);
            cout << "Produkt usuniety.\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cerr << "Nie znaleziono produktu!\n";
    }
}

void changeProductQty(std::vector<Product>& products) {
    string name;
    unsigned int new_qty;
    cout << "Podaj nazwe produktu: ";
    cin >> name;
    cout << "Podaj nowa ilosc: ";
    cin >> new_qty;

    bool found = false;
    for (size_t i = 0; i < products.size(); i++) {
        if (products[i].name == name) {
            products[i].qty = new_qty;
            cout << "Zmieniono ilosc produktu.\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cerr << "Produkt nie znaleziony!\n";
    }
}

void searchProduct(const std::vector<Product>& products) {
    string name;
    cout << "Podaj nazwe produktu: ";
    cin >> name;

    bool found = false;
    for (size_t i = 0; i < products.size(); i++) {
        if (products[i].name == name) {
            cout << "Znaleziono: " << products[i].name << " Cena: " << products[i].price << " Ilosc: " << products[i].qty << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cerr << "Produkt nie znaleziony!\n";
    }
}

void optimizeWarehouse(std::vector<Product>& products) {
    vector<Product> optimized;

    for (size_t i = 0; i < products.size(); i++) {
        bool found = false;
        for (size_t j = 0; j < optimized.size(); j++) {
            if (optimized[j].name == products[i].name && optimized[j].price == products[i].price) {
                optimized[j].qty += products[i].qty;
                found = true;
                break;
            }
        }

        if (!found) {
            optimized.push_back(products[i]);
        }
    }

    products = optimized;
    cout << "Magazyn zoptymalizowany!\n";
}

int main(int argc, char* argv[]) {
    string filename = (argc > 1) ? argv[1] : "magazyn.txt";
    vector<Product> products;

    loadFromFile(filename, products);

    while (true) {
        cout << "1. Wyświetl raport \n";
        cout << "2. Dodaj produkt \n";
        cout << "3. Usuń produkt \n";
        cout << "4. Zmien ilosc \n";
        cout << "5. Znajdz produkt \n";
        cout << "6. Optymalizuj magazyn \n";
        cout << "7. Zakończ program: \n";
        cout << "Wybierz opcje: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                displayProducts(products);
                break;
            case 2:
                addProduct(products);
                break;
            case 3:
                removeProduct(products);
                break;
            case 4:
                changeProductQty(products);
                break;
            case 5:
                searchProduct(products);
                break;
            case 6:
                optimizeWarehouse(products);
                break;
            case 7:
                saveToFile(filename, products);
                std::cout << "Zapisano dane. Koniec programu.\n";
                return 0;
            default:
                std::cerr << "Niepoprawny wybor!\n";
        }
    }

    return 0;
}
