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

Product products[MAX_PRODUCTS]; // Tablica przechowująca produkty
int productCount = 0;           // Liczba produktów w tablicy

// Funkcja dodająca nowy produkt
void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        cout << "Baza produktów jest pełna!" << endl;
        return;
    }

    Product newProduct;
    newProduct.id = productCount + 1;

    cout << "Podaj nazwę produktu: ";
    cin.ignore(); // Wyczyszczenie wczesniejszych inputow
    cin.getline(newProduct.name, MAX_LEN); // Wczytanie całej linii tekstu jako nazwy produktu

    cout << "Podaj kategorię produktu: ";
    cin.getline(newProduct.category, MAX_LEN);

    cout << "Podaj cenę: ";
    cin >> newProduct.price;

    cout << "Podaj ilość: ";
    cin >> newProduct.quantity;

    products[productCount++] = newProduct; // Dodanie nowego produktu do tablicy na pozycji prodcutCount
    cout << "Produkt dodany!" << endl;
}

// Funkcja usuwająca produkt po ID
void removeProduct() {
    int id;
    cout << "Podaj ID produktu do usunięcia: ";
    cin >> id;

    int index = -1; // Defaultowo produkt jest nieodnaleziony (brak takiego ID)

    // Szukanie produktu o podanym ID
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Nie znaleziono produktu o podanym ID!" << endl;
        return;
    }

    // Przesunięcie produktów w tablicy, aby usunąć wybrany produkt
    for (int i = index; i < productCount - 1; i++) {
        products[i] = products[i + 1];
    }

    productCount--;  // Zmniejszenie liczby produktów
    cout << "Produkt usunięty!" << endl;
}

// Funkcja zapisująca produkty do pliku
void saveToFile() {
    FILE* file = fopen("products.txt", "w");
    if (!file) {
        cout << "Błąd zapisu do pliku!" << endl;
        return;
    }

    for (int i = 0; i < productCount; i++) {
        fprintf(file, "%d %s %s %.2f %d\n", products[i].id, products[i].name, 
                products[i].category, products[i].price, products[i].quantity);
    }

    fclose(file);
    cout << "Produkty zapisane do pliku!" << endl;
}

// Funkcja wczytująca produkty z pliku
void loadFromFile() {
    FILE* file = fopen("products.txt", "r");
    if (!file) {
        cout << "Brak pliku do odczytu." << endl;
        return;
    }

    productCount = 0;
    while (fscanf(file, "%d %s %s %f %d", // Podanie jakich typow wczytywane sa dane
                  &products[productCount].id, products[productCount].name,
                  products[productCount].category, &products[productCount].price, // Przypisanie odpowiednich danych do pol struktury product, products[]
                  &products[productCount].quantity) != EOF) { // EOF To End Of File funckji fscanf() i konczy sie z zakonczeniem petli while
        productCount++; // Z kazdym wczytanym produktem dodajemy jedna liczbe do productCount aby sledzic ich liczbe
    }

    fclose(file);
    cout << "Produkty wczytane z pliku!" << endl;
}

// Funkcja wyświetlająca listę produktów
void displayProducts() {
    if (productCount == 0) {
        cout << "Brak produktów!" << endl;
        return;
    }

    for (int i = 0; i < productCount; i++) {
        cout << products[i].id << ". " << products[i].name << " | " 
             << products[i].category << " | " << products[i].price << " zł | " 
             << products[i].quantity << " szt." << endl;
    }
}

// Funkcja wyświetlająca menu i obsługująca wybory użytkownika
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
