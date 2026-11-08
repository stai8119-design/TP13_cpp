#include <iostream>
#include <memory>    
#include <stdexcept>  
#include <vector> 

using namespace std;

class StackOverflow : public exception {
public:
    const char* what() const noexcept override {
        return "Erreur : Stack Overflow (La pile est pleine) !";
    }
};

class StackUnderflow : public exception {
public:
    const char* what() const noexcept override {
        return "Erreur : Stack Underflow (La pile est vide) !";
    }
};

template <typename T>
class Stack {
private:
    std::unique_ptr<T[]> data;
    size_t capacity;             
    size_t top;             

public:
    Stack(size_t cap = 100) {
        capacity = (cap == 0) ? 1 : cap;
        data = std::make_unique<T[]>(capacity);
        top = 0;
    }
    
    template <typename Iterator>
    Stack(Iterator begin, Iterator end, size_t cap = 100) {
        size_t distance = 0;
        for (auto it = begin; it != end; ++it) {
            distance++;
        }

        capacity = (cap > distance) ? cap : distance + 10;
        data = std::make_unique<T[]>(capacity);
        top = 0;
        
        for (auto it = begin; it != end; ++it) {
            if (top >= capacity) {
                break;
            }
            data[top++] = *it;
        }
    }
    
    void push(const T& element) {
        if (top >= capacity) {
            throw StackOverflow();
        }
        data[top++] = element;
    }
    
    void pop() {
        if (empty()) {
            throw StackUnderflow();
        }
        top--;
    }
    
    T& peek() {
        if (empty()) {
            throw StackUnderflow();
        }
        return data[top - 1];
    }
    
    const T& peek() const {
        if (empty()) {
            throw StackUnderflow();
        }
        return data[top - 1];
    }
    
    bool empty() const {
        return top == 0;
    }
    
    size_t size() const {
        return top;
    }
    
    size_t getCapacity() const {
        return capacity;
    }
};

int main() {
    cout << "Test 1 : Utilisation basique de la Stack<int>" << endl;
    try {
        Stack<int> maPile(5);

        cout << "Est-ce que la pile est vide ? " << (maPile.empty() ? "Oui" : "Non") << endl;

        maPile.push(10);
        maPile.push(20);
        maPile.push(30);

        cout << "Sommet de la pile (peek) : " << maPile.peek() << endl;
        cout << "Taille actuelle : " << maPile.size() << endl;

        maPile.pop();
        cout << "Apres un pop, nouveau sommet : " << maPile.peek() << endl;

    } catch (const exception& e) {
        cout << "Exception : " << e.what() << endl;
    }

    cout << "\nTest 2 : Test des exceptions" << endl;
    try {
        Stack<int> petitePile(2);
        petitePile.push(1);
        petitePile.push(2);
        
        cout << "Tentative d'ajouter un 3eme element dans une pile de capacite 2..." << endl;
        petitePile.push(3);

    } catch (const exception& e) {
        cout << "Attrapé -> " << e.what() << endl;
    }

    try {
        Stack<int> pileVide;
        pileVide.pop();

    } catch (const exception& e) {
        cout << "Attrapé -> " << e.what() << endl;
    }

    cout << "\nTest 3 : Initialisation via itérateurs" << endl;
    vector<string> noms = {"C++", "Templates", "SmartPointers", "Stack"};
    Stack<string> pileStr(noms.begin(), noms.end(), 10);

    cout << "Elements depiles de la pile:" << endl;
    while (!pileStr.empty()) {
        cout << "  -> " << pileStr.peek() << endl;
        pileStr.pop();
    }

    cout << "\nTest 4 : Gros nombre d'objets" << endl;
    {
        size_t grosVolume = 50000;
        Stack<int> grossePile(grosVolume);

        for (size_t i = 0; i < grosVolume; i++) {
            grossePile.push(i);
        }
        cout << "Succes : " << grosVolume << " elements ajoutes et geres automatiquement par std::unique_ptr" << endl;
        cout << "Sommet final : " << grossePile.peek() << endl;
    }
    cout << "Fin du programme sans fuite de memoire." << endl;
    return 0;
}