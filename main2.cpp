#include <iostream>
#include <cstdio> 
#include <cstring>

#define PRODUCT_LIMIT 100
#define MAX_LENGTH 50

using namespace std;

// Globalne tablice do przechowywania danych produktów
int productID[PRODUCT_LIMIT];
char productName[PRODUCT_LIMIT][MAX_LENGTH];
char productCategory[PRODUCT_LIMIT][MAX_LENGTH];
float productPrice[PRODUCT_LIMIT];
int productStock[PRODUCT_LIMIT];
int totalProducts = 0;

// Deklaracje funkcji
void showMenu();
void addProduct();
void removeProduct();
void listProducts();
void saveData();
void loadData();

int main() {
    // Próba wczytania bazy na starcie programu
    loadData();
    
    int choice;
    bool isRunning = true;
    
    while (isRunning) {
        showMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: addProduct(); break;
            case 2: removeProduct(); break;
            case 3: listProducts(); break;
            case 4: saveData(); break;
            case 5: loadData(); break;
            case 6: 
                cout << "Kończenie programu. Do widzenia!" << endl;
                isRunning = false;
                break;
            default: cout << "Nieprawidłowa opcja! Spróbuj ponownie." << endl;
        }
    }
    
    return 0;
}

// Wyświetlanie menu głównego
void showMenu() {
    cout << "\n===== SYSTEM BAZY PRODUKTÓW =====\n"
         << "1. Dodaj nowy produkt\n"
         << "2. Usuń produkt\n"
         << "3. Pokaż wszystkie produkty\n"
         << "4. Zapisz bazę danych\n"
         << "5. Wczytaj bazę danych\n"
         << "6. Wyjdź z programu\n"
         << "Wybierz opcję: ";
}

// Dodawanie nowego produktu do bazy
void addProduct() {
    if (totalProducts >= PRODUCT_LIMIT) {
        cout << "Błąd: Baza danych jest pełna!" << endl;
        return;
    }
    
    // Generowanie ID (po prostu zwiększamy numer)
    productID[totalProducts] = totalProducts + 1;
    
    // Pobieranie danych produktu
    cout << "Podaj nazwę produktu: ";
    cin.ignore();
    cin.getline(productName[totalProducts], MAX_LENGTH);
    
    cout << "Podaj kategorię produktu: ";
    cin.getline(productCategory[totalProducts], MAX_LENGTH);
    
    cout << "Podaj cenę produktu: ";
    cin >> productPrice[totalProducts];
    
    cout << "Podaj dostępną ilość: ";
    cin >> productStock[totalProducts];
    
    totalProducts++;
    cout << "Produkt został dodany pomyślnie!" << endl;
}

// Usuwanie produktu na podstawie ID
void removeProduct() {
    if (totalProducts == 0) {
        cout << "Baza danych jest pusta!" << endl;
        return;
    }
    
    int id;
    cout << "Podaj ID produktu do usunięcia: ";
    cin >> id;
    
    // Wyszukiwanie produktu o podanym ID
    int position = -1;
    for (int i = 0; i < totalProducts; i++) {
        if (productID[i] == id) {
            position = i;
            break;
        }
    }
    
    if (position == -1) {
        cout << "Produkt o podanym ID nie istnieje!" << endl;
        return;
    }
    
    // Przesuwanie produktów w tablicy aby usunąć wybrany
    for (int i = position; i < totalProducts - 1; i++) {
        productID[i] = productID[i + 1];
        strcpy(productName[i], productName[i + 1]);
        strcpy(productCategory[i], productCategory[i + 1]);
        productPrice[i] = productPrice[i + 1];
        productStock[i] = productStock[i + 1];
    }
    
    totalProducts--;
    cout << "Produkt został usunięty pomyślnie!" << endl;
}

// Wyświetlanie wszystkich produktów
void listProducts() {
    if (totalProducts == 0) {
        cout << "Baza danych jest pusta!" << endl;
        return;
    }
    
    cout << "\nLista wszystkich produktów:\n";
    cout << "ID | Nazwa | Kategoria | Cena | Ilość\n";
    cout << "-----------------------------------\n";
    
    for (int i = 0; i < totalProducts; i++) {
        cout << productID[i] << " | " << productName[i] << " | " 
             << productCategory[i] << " | " << productPrice[i] << " zł | " 
             << productStock[i] << " szt." << endl;
    }
}

// Zapisywanie bazy danych do pliku
void saveData() {
    FILE* file = fopen("products.txt", "w");
    if (!file) {
        cout << "Błąd: Nie można otworzyć pliku do zapisu!" << endl;
        return;
    }
    
    for (int i = 0; i < totalProducts; i++) {
        fprintf(file, "%d %s %s %.2f %d\n", 
                productID[i], productName[i], productCategory[i], 
                productPrice[i], productStock[i]);
    }
    
    fclose(file);
    cout << "Baza danych została zapisana pomyślnie!" << endl;
}

// Wczytywanie bazy danych z pliku
void loadData() {
    FILE* file = fopen("products.txt", "r");
    if (!file) {
        cout << "Informacja: Plik bazy danych nie istnieje." << endl;
        return;
    }
    
    totalProducts = 0;
    while (fscanf(file, "%d %s %s %f %d", 
                  &productID[totalProducts], productName[totalProducts], 
                  productCategory[totalProducts], &productPrice[totalProducts], 
                  &productStock[totalProducts]) != EOF && totalProducts < PRODUCT_LIMIT) {
        totalProducts++;
    }
    
    fclose(file);
    cout << "Wczytano " << totalProducts << " produktów z pliku." << endl;
}
