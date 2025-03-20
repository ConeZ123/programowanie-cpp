#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Product {
    string name;
    unsigned int price;
    unsigned int qty;
};

void loadFromFile(const string& filename, vector<Product> items) {
    ifstream input;
    input.open(filename);

    if(!input) {
        cerr << "Nie można otworzyć pliku: " << filename;
    }

    Product p;
    while (input >> p.name >> p.price >> p.qty) {
        items.push_back(p);
    }
    input.close();
}

void saveToFile(const string& filename, vector<Product> items) {
    ofstream input;
    input.open(filename);

    if(!input) {
        cerr << "Bład zapisu do pliku: " << filename;
    }

    for (size_t i = 0; i < items.size(); i++) {
        cout << items[i].name << "\t" << items[i].price << "\t" << items[i].qty << "\n";
    }
    input.close();
}

void displayProduct(const vector<Product>& items) {
    cout << "Magazyn: ";
    cout << "Nazwa: \t" << "Cena: \t" << "Ilosc: \t";
    for (size_t i = 0; i < items.size(); i++) {
        cout << items[i].name << "\t" << items[i].price << "\t" << items[i].qty << "\n";
    }
}

void addProduct(vector<Product>& items) {
    Product p;
    cout << "Podaj nazwę produktu: ";
    cin >> p.name;
    cout << "Podaj cenę produktu: ";
    cin >> p.price;
    cout << "Podaj ilość produktu: ";
    cin >> p.qty;

    if (p.price < 0 || p.qty < 0) {
        cout << "Cena i ilość produktu nie może być ujemna";
    }
    items.push_back(p);
}

void removeProduct(vector<Product>& items) {
    string name;
    cout << "Podaj nazwę produktu: ";
    cin >> name;

    for (size_t i = 0; i < items.size(); i++) {
        if (items[i].name == name) {
            items.erase(items.begin() + i);
            cout << "Produkt pomyślnie usunięty.\n";
        }
        cerr << "Nie znaleziono produktu.\n";
    } 

}

void changeQuantity(vector<Product>& items) {
    string name;
    cout << "Podaj nazwę produktu: ";
    cin >> name;

    unsigned int newQty;
    cout << "Podaj ilość produktu: ";
    cin >> newQty;

    for (size_t i = 0; i < items.size(); i++) {
        if (items[i].name == name) {
            items[i].qty == newQty;
            cout << "Ilość prodktu została zmieniona.\n";
        }
        cerr << "Nie znaleziono produktu.\n";
    }
}

void searchProduct(vector<Product>& items) {
    string name;
    cout << "Podaj nazwę produktu: ";
    cin >> name;

    for (size_t i = 0; i < items.size(); i++) {
        if (items[i].name == name) {
            cout << "Znaleziono produkt: " << items[i].name << "Cena: " << items[i].price << "Ilość: " << items[i].qty << "\n";
        }
        cerr << "Nie znaleziono produktu.\n";
    }
}

void optimizedWarehouse(vector<Product>& items) {
    // ....     
}

int main(int argc, char* argv[]) {
    string filename = (argc > 1) ? argv[1] : 'magazyn.txt';
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
                displayProduct(products);
            case 2:
                addProduct(products);
            case 3:
                removeProduct(products);
            case 4:
                changeQuantity(products);
            case 5:
                searchProduct(products);
            case 6:
                optimizedWarehouse(products);
            case 7:
                saveToFile(filename, products);
                cout << "Pomyślnie zapisano dane do pliku.";
            default:
                cerr << "Niepoprawny wybór!";
        }
    }

    return 0;
}
