#include <iostream>
#include <cstdio> 
#include <cstring>

#define ITEM_LIMIT 100
#define MAX_LENGTH 50

using namespace std;

// Globalne tablice do przechowywania danych produktów
int itemID[ITEM_LIMIT];
char itemName[ITEM_LIMIT][MAX_LENGTH];
char itemCategory[ITEM_LIMIT][MAX_LENGTH];
float itemPrice[ITEM_LIMIT];
int itemStock[ITEM_LIMIT];
int totalItems = 0;

// Deklaracje funkcji
void showMenu();
void addItem();
void removeItem();
void listItems();
void saveDatabase();
void loadDatabase();

int main() {
    // Próba wczytania bazy na starcie programu
    loadDatabase();
    
    int choice;
    bool isRunning = true;
    
    while (isRunning) {
        showMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: addItem(); break;
            case 2: removeItem(); break;
            case 3: listItems(); break;
            case 4: saveDatabase(); break;
            case 5: loadDatabase(); break;
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
void addItem() {
    if (totalItems >= ITEM_LIMIT) {
        cout << "Błąd: Baza danych jest pełna!" << endl;
        return;
    }
    
    // Generowanie ID (po prostu zwiększamy numer)
    itemID[totalItems] = totalItems + 1;
    
    // Pobieranie danych produktu
    cout << "Podaj nazwę produktu: ";
    cin.ignore();
    cin.getline(itemName[totalItems], MAX_LENGTH);
    
    cout << "Podaj kategorię produktu: ";
    cin.getline(itemCategory[totalItems], MAX_LENGTH);
    
    cout << "Podaj cenę produktu: ";
    cin >> itemPrice[totalItems];
    
    cout << "Podaj dostępną ilość: ";
    cin >> itemStock[totalItems];
    
    totalItems++;
    cout << "Produkt został dodany pomyślnie!" << endl;
}

// Usuwanie produktu na podstawie ID
void removeItem() {
    if (totalItems == 0) {
        cout << "Baza danych jest pusta!" << endl;
        return;
    }
    
    int id;
    cout << "Podaj ID produktu do usunięcia: ";
    cin >> id;
    
    // Wyszukiwanie produktu o podanym ID
    int position = -1;
    for (int i = 0; i < totalItems; i++) {
        if (itemID[i] == id) {
            position = i;
            break;
        }
    }
    
    if (position == -1) {
        cout << "Produkt o podanym ID nie istnieje!" << endl;
        return;
    }
    
    // Przesuwanie produktów w tablicy aby usunąć wybrany
    for (int i = position; i < totalItems - 1; i++) {
        itemID[i] = itemID[i + 1];
        strcpy(itemName[i], itemName[i + 1]);
        strcpy(itemCategory[i], itemCategory[i + 1]);
        itemPrice[i] = itemPrice[i + 1];
        itemStock[i] = itemStock[i + 1];
    }
    
    totalItems--;
    cout << "Produkt został usunięty pomyślnie!" << endl;
}

// Wyświetlanie wszystkich produktów
void listItems() {
    if (totalItems == 0) {
        cout << "Baza danych jest pusta!" << endl;
        return;
    }
    
    cout << "\nLista wszystkich produktów:\n";
    cout << "ID | Nazwa | Kategoria | Cena | Ilość\n";
    cout << "-----------------------------------\n";
    
    for (int i = 0; i < totalItems; i++) {
        cout << itemID[i] << " | " << itemName[i] << " | " 
             << itemCategory[i] << " | " << itemPrice[i] << " zł | " 
             << itemStock[i] << " szt." << endl;
    }
}

// Zapisywanie bazy danych do pliku
void saveDatabase() {
    FILE* file = fopen("products.txt", "w");
    if (!file) {
        cout << "Błąd: Nie można otworzyć pliku do zapisu!" << endl;
        return;
    }
    
    for (int i = 0; i < totalItems; i++) {
        fprintf(file, "%d %s %s %.2f %d\n", 
                itemID[i], itemName[i], itemCategory[i], 
                itemPrice[i], itemStock[i]);
    }
    
    fclose(file);
    cout << "Baza danych została zapisana pomyślnie!" << endl;
}

// Wczytywanie bazy danych z pliku
void loadDatabase() {
    FILE* file = fopen("products.txt", "r");
    if (!file) {
        cout << "Informacja: Plik bazy danych nie istnieje." << endl;
        return;
    }
    
    totalItems = 0;
    while (fscanf(file, "%d %s %s %f %d", 
                  &itemID[totalItems], itemName[totalItems], 
                  itemCategory[totalItems], &itemPrice[totalItems], 
                  &itemStock[totalItems]) != EOF && totalItems < ITEM_LIMIT) {
        totalItems++;
    }
    
    fclose(file);
    cout << "Wczytano " << totalItems << " produktów z pliku." << endl;
}
