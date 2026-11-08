#include <iostream>
#include <vector>
#include <string>
#include <functional>

using namespace std;
template <typename T>
struct Asc {
    bool operator()(const T& a, const T& b) const {
        return a < b;
    }
};
template <typename T>
struct Desc {
    bool operator()(const T& a, const T& b) const {
        return a > b;
    }
};

template <typename T, typename Comp>
int partitionner(vector<T>& tab, int bas, int haut, Comp comp) {
    T pivot = tab[haut];
    int i = (bas - 1);

    for (int j = bas; j <= haut - 1; j++) {
        if (comp(tab[j], pivot)) {
            i++;
            T temp = tab[i];
            tab[i] = tab[j];
            tab[j] = temp;
        }
    }
    T temp = tab[i + 1];
    tab[i + 1] = tab[haut];
    tab[haut] = temp;
    return (i + 1);
}
template <typename T, typename Comp>
void quickSortRecursif(vector<T>& tab, int bas, int haut, Comp comp) {
    if (bas < haut) {
        int pi = partitionner(tab, bas, haut, comp);
        quickSortRecursif(tab, bas, pi - 1, comp);
        quickSortRecursif(tab, pi + 1, haut, comp);
    }
}
template <typename T, typename Comp = Asc<T>>
void quickSort(vector<T>& tab, Comp comp = Comp{}) {
    if (!tab.empty()) {
        quickSortRecursif(tab, 0, tab.size() - 1, comp);
    }
}

class Point {
private:
    int x, y;

public:
    Point(int px = 0, int py = 0) : x(px), y(py) {}
    
    bool operator<(const Point& autre) const {
        if (x != autre.x) {
            return x < autre.x;
        }
        return y < autre.y;
    }
    
    friend ostream& operator<<(ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

template <typename T>
void afficherVecteur(const vector<T>& tab) {
    cout << "[ ";
    for (const auto& e : tab) {
        cout << e << " ";
    }
    cout << "]" << endl;
}

int main() {
    cout << "Test 1 : std::vector<int>" << endl;
    vector<int> tabInt = {42, 7, 19, 3, 55, 12};
    cout << "Avant tri : ";
    afficherVecteur(tabInt);
    
    quickSort(tabInt, Asc<int>());
    cout << "Apres QuickSort Ascendant : ";
    afficherVecteur(tabInt);
    
    quickSort(tabInt, Desc<int>());
    cout << "Apres QuickSort Descendant : ";
    afficherVecteur(tabInt);

    cout << "\nTest 2 : std::vector<std::string>" << endl;
    vector<string> tabStr = {"C++", "Algorithme", "Templates", "Concepts", "Zebra"};
    cout << "Avant tri : ";
    afficherVecteur(tabStr);

    quickSort(tabStr, Asc<string>());
    cout << "Apres QuickSort (Ascendant) : ";
    afficherVecteur(tabStr);

    cout << "\nTest 3 : Structure utilisateur" << endl;
    vector<Point> tabPoints = {Point(3, 4), Point(1, 2), Point(3, 1), Point(0, 5)};
    cout << "Avant tri :" << endl;
    for (const auto& p : tabPoints) { cout << "  " << p; }
    cout << endl;

    quickSort(tabPoints, Asc<Point>());
    cout << "Apres QuickSort (tries par x puis y) :" << endl;
    for (const auto& p : tabPoints) { cout << "  " << p; }
    cout << endl;

    cout << "\nTest 4 : Vérification unitaire" << endl;
    vector<int> testTri = {9, 1, 5, 3, 7};
    quickSort(testTri);
    
    bool estTrie = true;
    for (size_t i = 0; i < testTri.size() - 1; i++) {
        if (testTri[i] > testTri[i + 1]) {
            estTrie = false;
            break;
        }
    }

    if (estTrie) {
        cout << "Test unitaire reussi : Le vecteur est correctement trie !" << endl;
    } else {
        cout << "Test unitaire echoue !" << endl;
    }
    return 0;
}