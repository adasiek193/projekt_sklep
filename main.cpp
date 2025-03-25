#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Produkt {
public:
    int id;
    string nazwa;
    string kategoria;
    float cena;
    int stan;

    void wyswietl() {
        cout << "ID: " << id << endl;
        cout << "Nazwa: " << nazwa << endl;
        cout << "Kategoria: " << kategoria << endl;
        cout << "Cena: " << cena << " zł" << endl;
        cout << "Stan: " << stan << endl;
    }
};

class MenadzerProduktow {
private:
    vector<Produkt> produkty;
    int nastepneId = 1;

public:
    void dodaj() {
        Produkt p;
        p.id = nastepneId++;

        cout << "Nazwa produktu: ";
        cin.ignore();
        getline(cin, p.nazwa);

        cout << "Kategoria: ";
        getline(cin, p.kategoria);

        cout << "Cena: ";
        cin >> p.cena;

        cout << "Stan magazynowy: ";
        cin >> p.stan;

        produkty.push_back(p);
        cout << "Dodano produkt." << endl;
    }

    void usun() {
        if (produkty.empty()) {
            cout << "Brak produktów." << endl;
            return;
        }

        int id;
        cout << "Podaj ID produktu do usunięcia: ";
        cin >> id;

        auto it = find_if(produkty.begin(), produkty.end(), 
            [id](const Produkt& p) { return p.id == id; });

        if (it != produkty.end()) {
            produkty.erase(it);
            cout << "Usunięto produkt." << endl;
        } else {
            cout << "Nie znaleziono produktu." << endl;
        }
    }

    void wyswietl() {
        if (produkty.empty()) {
            cout << "Brak produktów." << endl;
            return;
        }

        for (const auto& p : produkty) {
            p.wyswietl();
            cout << "---" << endl;
        }
    }
};

int main() {
    MenadzerProduktow m;

    m.dodaj();
    m.dodaj();
    
    cout << "\nProdukty:" << endl;
    m.wyswietl();

    m.usun();

    cout << "\nPozostałe produkty:" << endl;
    m.wyswietl();

    return 0;
}
