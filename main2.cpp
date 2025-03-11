#include <iostream>
#include <cstdio>
#include <cstring>

#define MAX_PRODUCTS 100
#define MAX_LEN 50

using namespace std;

struct Product {
    int id;
    char name[MAX_LEN];
    char category[MAX_LEN];
    float price;
    int quantity;
};

Product products[MAX_PRODUCTS];
int productCount = 0;

// Dodawanie produktu
void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        cout << "Baza produktów jest pełna!" << endl;
        return;
    }

    Product p;
    p.id = productCount + 1;

    cout << "Podaj nazwę produktu: ";
    cin.ignore();
    cin.getline(p.name, MAX_LEN);

    cout << "Podaj kategorię produktu: ";
    cin.getline(p.category, MAX_LEN);

    cout << "Podaj cenę: ";
    cin >> p.price;

    cout << "Podaj ilość: ";
    cin >> p.quantity;

    products[productCount++] = p;
    cout << "Produkt dodany!" << endl;
}

// Usuwanie produktu po ID
void removeProduct() {
    int id;
    cout << "Podaj ID produktu do usunięcia: ";
    cin >> id;

    int index = -1;
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Produkt nie znaleziony!" << endl;
        return;
    }

    for (int i = index; i < productCount - 1; i++) {
        products[i] = products[i + 1];
    }
    productCount--;
    cout << "Produkt usunięty!" << endl;
}

// Zapisywanie produktów do pliku za pomocą fprintf()
void saveToFile() {
    FILE* file = fopen("products.txt", "w");
    if (!file) {
        cout << "Błąd zapisu do pliku!" << endl;
        return;
    }

    for (int i = 0; i < productCount; i++) {
        fprintf(file, "%d %s %s %.2f %d\n",
                products[i].id, products[i].name, products[i].category,
                products[i].price, products[i].quantity);
    }

    fclose(file);
    cout << "Zapisano do pliku!" << endl;
}

// Wczytywanie produktów z pliku za pomocą fscanf()
void loadFromFile() {
    FILE* file = fopen("products.txt", "r");
    if (!file) {
        cout << "Brak pliku do odczytu." << endl;
        return;
    }

    productCount = 0;
    while (fscanf(file, "%d %s %s %f %d",
                  &products[productCount].id, products[productCount].name,
                  products[productCount].category, &products[productCount].price,
                  &products[productCount].quantity) != EOF) {
        productCount++;
    }

    fclose(file);
    cout << "Załadowano produkty!" << endl;
}

// Wyświetlanie produktów
void displayProducts() {
    if (productCount == 0) {
        cout << "Brak produktów!" << endl;
        return;
    }

    for (int i = 0; i < productCount; i++) {
        cout << "ID: " << products[i].id << ", Nazwa: " << products[i].name
             << ", Kategoria: " << products[i].category
             << ", Cena: " << products[i].price
             << ", Ilość: " << products[i].quantity << endl;
    }
}

// Menu aplikacji
void menu() {
    int choice;
    while (true) {
        cout << "\n1. Dodaj produkt\n2. Usuń produkt\n3. Wyświetl produkty\n"
             << "4. Zapisz do pliku\n5. Wczytaj z pliku\n6. Wyjście\n"
             << "Wybór: ";
        cin >> choice;

        switch (choice) {
            case 1: addProduct(); break;
            case 2: removeProduct(); break;
            case 3: displayProducts(); break;
            case 4: saveToFile(); break;
            case 5: loadFromFile(); break;
            case 6: return;
            default: cout << "Nieprawidłowy wybór!" << endl;
        }
    }
}

int main() {
    menu();
    return 0;
}
