#include <iostream>
#include <iomanip>

using namespace std;
template <typename T, size_t N, size_t M>
class Matrice {
private:
    T data[N][M];

public:
    Matrice() {
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < M; j++) {
                data[i][j] = T(0);
            }
        }
    }
    T& get(size_t i, size_t j) {
        return data[i][j];
    }

    const T& get(size_t i, size_t j) const {
        return data[i][j];
    }
    Matrice<T, N, M> operator+(const Matrice<T, N, M>& autre) const {
        Matrice<T, N, M> resultat;
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < M; j++) {
                resultat.data[i][j] = this->data[i][j] + autre.data[i][j];
            }
        }
        return resultat;
    }
    template <size_t P>
    Matrice<T, N, P> operator*(const Matrice<T, M, P>& autre) const {
        Matrice<T, N, P> resultat;
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < P; j++) {
                for (size_t k = 0; k < M; k++) {
                    resultat.get(i, j) += this->data[i][k] * autre.get(k, j);
                }
            }
        }
        return resultat;
    }
    template <typename U, size_t L, size_t C>
    friend ostream& operator<<(ostream& os, const Matrice<U, L, C>& mat);
};
template <typename T, size_t N, size_t M>
ostream& operator<<(ostream& os, const Matrice<T, N, M>& mat) {
    os << "[\n";
    for (size_t i = 0; i < N; i++) {
        os << "  [ ";
        for (size_t j = 0; j < M; j++) {
            os << setw(6) << mat.data[i][j] << " ";
        }
        os << "]\n";
    }
    os << "]";
    return os;
}

int main() {
    cout << "Test 1 : Matrices d'entiers" << endl;
    Matrice<int, 2, 2> m1;
    Matrice<int, 2, 2> m2;
    m1.get(0, 0) = 1; m1.get(0, 1) = 2;
    m1.get(1, 0) = 3; m1.get(1, 1) = 4;
    m2.get(0, 0) = 5; m2.get(0, 1) = 6;
    m2.get(1, 0) = 7; m2.get(1, 1) = 8;
    cout << "Matrice M1 :" << endl << m1 << endl;
    cout << "Matrice M2 :" << endl << m2 << endl;
    Matrice<int, 2, 2> somme = m1 + m2;
    cout << "\nSomme (M1 + M2) :" << endl << somme << endl;
    Matrice<int, 2, 2> produit = m1 * m2;
    cout << "\nProduit (M1 * M2) :" << endl << produit << endl;
    cout << "\nTest 2 : Matrices de doubles" << endl;
    Matrice<double, 2, 3> md1; 
    Matrice<double, 3, 2> md2;
    md1.get(0, 0) = 1.5; md1.get(0, 1) = 2.0; md1.get(0, 2) = 1.0;
    md1.get(1, 0) = 0.5; md1.get(1, 1) = 1.0; md1.get(1, 2) = 2.5;
    md2.get(0, 0) = 1.0; md2.get(0, 1) = 2.0;
    md2.get(1, 0) = 3.0; md2.get(1, 1) = 0.0;
    md2.get(2, 0) = 1.0; md2.get(2, 1) = 1.0;
    cout << "Matrice MD1 (2x3) :" << endl << md1 << endl;
    cout << "Matrice MD2 (3x2) :" << endl << md2 << endl;
    Matrice<double, 2, 2> produitDouble = md1 * md2;
    cout << "\nProduit MD1 * MD2 (Donne une matrice 2x2) :" << endl << produitDouble << endl;

    return 0;
}