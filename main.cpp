
#include <iostream>
#include <cstring>
#include <cstdio>  // Do obsługi plików: fopen(), fprintf(), fscanf(), fclose()

#define MAX_PRODUCTS 100
#define MAX_LEN 50

using namespace std;

class Product {
public:
    int id;
    char name[MAX_LEN];
    char category[MAX_LEN];
    float price;
    int quantity;

    Product(int id, const char* name, const char* category, float price, int quantity) {
        this->id = id;
        strncpy(this->name, name, MAX_LEN);
        strncpy(this->category, category, MAX_LEN);
        this->price = price;
        this->quantity = quantity;
    }

    void display() {
        cout << "ID: " << id << ", Nazwa: " << name << ", Kategoria: " << category
             << ", Cena: " << price << ", Ilość: " << quantity << endl;
    }
};

class ProductManager {
private:
    Product* products[MAX_PRODUCTS];
    int count = 0;
    const char* filename = "products.txt";  // Nazwa pliku do zapisu i odczytu

public:
    void addProduct() {
        if (count >= MAX_PRODUCTS) {
            cout << "Nie można dodać więcej produktów!" << endl;
            return;
        }

        char name[MAX_LEN], category[MAX_LEN];
        float price;
        int quantity;

        cout << "Podaj nazwę: ";
        cin.ignore();
        cin.getline(name, MAX_LEN);

        cout << "Podaj kategorię: ";
        cin.getline(category, MAX_LEN);

        cout << "Podaj cenę: ";
        cin >> price;

        cout << "Podaj ilość: ";
        cin >> quantity;

        products[count] = new Product(count + 1, name, category, price, quantity);
        count++;
        cout << "Produkt dodany!" << endl;

        saveToFile();  // Zapisujemy po dodaniu nowego produktu
    }

    void removeProduct() {
        int id;
        cout << "Podaj ID produktu do usunięcia: ";
        cin >> id;

        for (int i = 0; i < count; i++) {
            if (products[i]->id == id) {
                delete products[i];

                for (int j = i; j < count - 1; j++) {
                    products[j] = products[j + 1];
                }

                count--;
                cout << "Produkt usunięty!" << endl;

                saveToFile();  // Zapisujemy zmiany do pliku
                return;
            }
        }
        cout << "Nie znaleziono produktu o podanym ID!" << endl;
    }

    void displayProducts() {
        if (count == 0) {
            cout << "Brak produktów w katalogu!" << endl;
            return;
        }

        for (int i = 0; i < count; i++) {
            products[i]->display();
        }
    }

    void saveToFile() {
        FILE* file = fopen(filename, "w");  // Otwieramy plik do zapisu
        if (!file) {
            cout << "Błąd otwierania pliku do zapisu!" << endl;
            return;
        }

        for (int i = 0; i < count; i++) {
            fprintf(file, "%d %s %s %.2f %d\n", products[i]->id, products[i]->name,
                    products[i]->category, products[i]->price, products[i]->quantity);
        }

        fclose(file);
        cout << "Dane zapisane do pliku!" << endl;
    }

    void loadFromFile() {
        FILE* file = fopen(filename, "r");  // Otwieramy plik do odczytu
        if (!file) {
            cout << "Brak zapisanych danych!" << endl;
            return;
        }

        count = 0;  // Resetujemy liczbę produktów

        while (!feof(file) && count < MAX_PRODUCTS) {
            int id, quantity;
            float price;
            char name[MAX_LEN], category[MAX_LEN];

            if (fscanf(file, "%d %s %s %f %d", &id, name, category, &price, &quantity) == 5) {
                products[count] = new Product(id, name, category, price, quantity);
                count++;
            }
        }

        fclose(file);
        cout << "Dane załadowane z pliku!" << endl;
    }

    ~ProductManager() {
        for (int i = 0; i < count; i++) {
            delete products[i];
        }
    }
};

int main() {
    ProductManager manager;
    manager.loadFromFile();  // Wczytujemy produkty przy starcie programu

    int choice;
    while (true) {
        cout << "\n1. Dodaj produkt\n2. Usuń produkt\n3. Wyświetl produkty\n4. Wyjście\nWybór: ";
        cin >> choice;

        if (choice == 1) manager.addProduct();
        else if (choice == 2) manager.removeProduct();
        else if (choice == 3) manager.displayProducts();
        else break;
    }

    return 0;
}
