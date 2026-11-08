#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;
template <typename T>
class ArrayDyn {
private:
    T* data;           
    size_t capacite;   
    size_t taille;  

public:
    ArrayDyn(size_t cap = 10) {
        capacite = (cap == 0) ? 1 : cap;
        taille = 0;
        data = new T[capacite];
    }
    
    ArrayDyn(const ArrayDyn& autre) {
        capacite = autre.capacite;
        taille = autre.taille;
        data = new T[capacite];
        for (size_t i = 0; i < taille; i++) {
            data[i] = autre.data[i];
        }
    }
    
    ArrayDyn& operator=(const ArrayDyn& autre) {
        if (this != &autre) { 
            delete[] data;
            capacite = autre.capacite;
            taille = autre.taille;
            data = new T[capacite];
            for (size_t i = 0; i < taille; i++) {
                data[i] = autre.data[i];
            }
        }
        return *this;
    }
    
    ~ArrayDyn() {
        delete[] data;
    }
    
    size_t getTaille() const {
        return taille;
    }

    size_t getCapacite() const {
        return capacite;
    }
    
    void push_back(const T& element) {
        if (taille >= capacite) {
            capacite *= 2;
            T* newData = new T[capacite];
            for (size_t i = 0; i < taille; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[taille++] = element;
    }
    
    void pop_back() {
        if (taille > 0) {
            taille--;
        }
    }
    
    T& operator[](size_t index) {
        if (index >= taille) {
            throw out_of_range("Erreur : Index hors des limites du conteneur");
        }
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= taille) {
            throw out_of_range("Erreur : Index hors des limites du conteneur");
        }
        return data[index];
    }
    
    class Iterator {
    private:
        T* ptr;

    public:
        Iterator(T* p) : ptr(p) {}
        
        T& operator*() {
            return *ptr;
        }
        
        Iterator& operator++() {
            ptr++;
            return *this;
        }
        
        Iterator& operator--() {
            ptr--;
            return *this;
        }
        
        bool operator!=(const Iterator& autre) const {
            return ptr != autre.ptr;
        }
    };
    
    Iterator begin() {
        return Iterator(data);
    }

    Iterator end() {
        return Iterator(data + taille);
    }
};
class Etudiant {
private:
    string nom;
    double moyenne;

public:
    Etudiant(string n = "", double m = 0.0) : nom(n), moyenne(m) {}
    
    friend ostream& operator<<(ostream& os, const Etudiant& etu) {
        os << "[Etudiant : " << etu.nom << " | Moyenne : " << etu.moyenne << "/20]";
        return os;
    }
};
int main() {
    cout << "Test 1 : Avec des int" << endl;
    ArrayDyn<int> tabInt(2);
    tabInt.push_back(10);
    tabInt.push_back(20);
    tabInt.push_back(30);
    cout << "Elements de tabInt : ";
    for (auto& e : tabInt) {
        cout << e << " ";
    }
    cout << endl;

    cout << "\nTest 2 : Avec des std::string" << endl;
    ArrayDyn<string> tabStr;
    tabStr.push_back("C++");
    tabStr.push_back("Templates");
    tabStr.push_back("Iterateurs");

    cout << "Elements de tabStr : ";
    for (auto& e : tabStr) {
        cout << e << " | ";
    }
    cout << endl;

    cout << "\nTest 3 : Avec un objet maison" << endl;
    ArrayDyn<Etudiant> tabEtu;
    tabEtu.push_back(Etudiant("Fatima", 15.5));
    tabEtu.push_back(Etudiant("Mehdi", 14.0));

    cout << "Liste des etudiants :" << endl;
    for (auto& e : tabEtu) {
        cout << "  -> " << e << endl;
    }

    cout << "\nTest du controle de bornes" << endl;
    try {
        cout << tabInt[10] << endl;
    } catch (const exception& ex) {
        cout << "Exception attrapee : " << ex.what() << endl;
    }
    return 0;
}