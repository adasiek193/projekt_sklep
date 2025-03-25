#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Produkt {
private:
    int id;
    string nazwa;
    string kategoria;
    float cena;
    int stan;

public:
    // Konstruktor
    Produkt(int _id, const string& _nazwa, const string& _kategoria, 
            float _cena, int _stan) 
        : id(_id), nazwa(_nazwa), kategoria(_kategoria), cena(_cena), stan(_stan) {}

    // Gettery
    int getId() const { return id; }
    string getNazwa() const { return nazwa; }
    string getKategoria() const { return kategoria; }
    float getCena() const { return cena; }
    int getStan() const { return stan; }

    // Metoda wyświetlania szczegółów produktu
    void wyswietlSzczegoly() const {
        cout << "ID: " << id << endl;
        cout << "Nazwa: " << nazwa << endl;
        cout << "Kategoria: " << kategoria << endl;
        cout << "Cena: " << cena << " zł" << endl;
        cout << "Stan magazynowy: " << stan << endl;
    }
};

class MenadzerProduktow {
private:
    vector<Produkt> produkty;
    int nastepneId;

public:
    // Konstruktor
    MenadzerProduktow() : nastepneId(1) {}

    // Dodawanie nowego produktu
    void dodajProdukt() {
        string nazwa, kategoria;
        float cena;
        int stan;

        cout << "Podaj nazwę produktu: ";
        cin.ignore();
        getline(cin, nazwa);

        cout << "Podaj kategorię produktu: ";
        getline(cin, kategoria);

        cout << "Podaj cenę produktu: ";
        cin >> cena;

        cout << "Podaj stan magazynowy: ";
        cin >> stan;

        // Utworzenie i dodanie produktu
        produkty.emplace_back(nastepneId++, nazwa, kategoria, cena, stan);
        cout << "Produkt został dodany pomyślnie!" << endl;
    }

    // Usuwanie produktu po ID
    void usunProdukt() {
        if (produkty.empty()) {
            cout << "Brak produktów do usunięcia." << endl;
            return;
        }

        int id;
        cout << "Podaj ID produktu do usunięcia: ";
        cin >> id;

        // Znalezienie i usunięcie produktu
        auto it = find_if(produkty.begin(), produkty.end(), 
            [id](const Produkt& p) { return p.getId() == id; });

        if (it != produkty.end()) {
            produkty.erase(it);
            cout << "Produkt został usunięty pomyślnie!" << endl;
        } else {
            cout << "Nie znaleziono produktu!" << endl;
        }
    }

    // Wyświetlanie wszystkich produktów
    void wyswietlProdukty() const {
        if (produkty.empty()) {
            cout << "Brak produktów w bazie." << endl;
            return;
        }

        for (const auto& produkt : produkty) {
            produkt.wyswietlSzczegoly();
            cout << "-------------------" << endl;
        }
    }
};

int main() {
    MenadzerProduktow menadzer;

    // Przykładowe użycie funkcjonalności
    menadzer.dodajProdukt();
    menadzer.dodajProdukt();
    
    cout << "\nAktualne produkty:" << endl;
    menadzer.wyswietlProdukty();

    menadzer.usunProdukt();

    cout << "\nPozostałe produkty:" << endl;
    menadzer.wyswietlProdukty();

    return 0;
}
