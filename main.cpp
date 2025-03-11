#include <iostream>
#include <cstring>

#define MAX_PRODUCTS 100
#define MAX_LEN 50

using namespace std;

// Klasa reprezentująca pojedynczy produkt
class Product {
public:
    int id;
    char name[MAX_LEN];
    char category[MAX_LEN];
    float price;
    int quantity;

    // Konstruktor do inicjalizacji produktu
    Product(int id = 0, const char* name = "", const char* category = "", float price = 0, int quantity = 0) {
        this->id = id;
        strncpy(this->name, name, MAX_LEN);
        strncpy(this->category, category, MAX_LEN);
        this->price = price;
        this->quantity = quantity;
    }

    // Metoda do wyświetlania informacji o produkcie
    void display() const {
        cout << "ID: " << id << ", Nazwa: " << name << ", Kategoria: " << category
             << ", Cena: " << price << " zł, Ilość: " << quantity << " szt." << endl;
    }
};

// Klasa zarządzająca produktami
class ProductManager {
private:
    Product products[MAX_PRODUCTS];  // Tablica przechowująca produkty
    int productCount = 0;            // Liczba produktów w tablicy

public:
    // Dodaje nowy produkt
    void addProduct() {
        if (productCount >= MAX_PRODUCTS) {
            cout << "Nie można dodać więcej produktów! Osiągnięto limit." << endl;
            return;
        }

        char name[MAX_LEN], category[MAX_LEN];
        float price;
        int quantity;

        cout << "Podaj nazwę produktu: ";
        cin.ignore();
        cin.getline(name, MAX_LEN);

        cout << "Podaj kategorię produktu: ";
        cin.getline(category, MAX_LEN);

        cout << "Podaj cenę produktu: ";
        cin >> price;

        cout << "Podaj ilość produktu: ";
        cin >> quantity;

        products[productCount++] = Product(productCount + 1, name, category, price, quantity);
        cout << "Produkt dodany pomyślnie!" << endl;
    }

    // Usuwa produkt po ID
    void removeProduct() {
        if (productCount == 0) {
            cout << "Brak produktów do usunięcia!" << endl;
            return;
        }

        int id;
        cout << "Podaj ID produktu do usunięcia: ";
        cin >> id;

        for (int i = 0; i < productCount; i++) {
            if (products[i].id == id) {
                for (int j = i; j < productCount - 1; j++) {
                    products[j] = products[j + 1];
                }
                productCount--;
                cout << "Produkt usunięty pomyślnie!" << endl;
                return;
            }
        }
        cout << "Nie znaleziono produktu o podanym ID!" << endl;
    }

    // Wyświetla wszystkie produkty
    void displayProducts() const {
        if (productCount == 0) {
            cout << "Brak produktów w katalogu!" << endl;
            return;
        }

        for (int i = 0; i < productCount; i++) {
            products[i].display();
        }
    }
};

// Funkcja główna – obsługuje menu użytkownika
int main() {
    ProductManager manager;

    int choice;
    while (true) {
        cout << "\n1. Dodaj produkt\n2. Usuń produkt\n3. Wyświetl produkty\n4. Wyjście\nWybór: ";
        cin >> choice;

        switch (choice) {
            case 1: manager.addProduct(); break;
            case 2: manager.removeProduct(); break;
            case 3: manager.displayProducts(); break;
            case 4: return 0;
            default: cout << "Nieprawidłowy wybór! Spróbuj ponownie." << endl;
        }
    }

    return 0;
}
