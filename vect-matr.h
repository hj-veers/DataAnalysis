//Raccolta delle funzioni per le operazioni con vettori e matrici

/*
1. Funzione per la somma tra vettori.......................................vector_sum
2. Funzione per la differenza tra vettori.................................vector_diff
3. Funzione per la moltiplicazione di un vettore per uno scalare...............scalar
4. Funzione per il calcolo del prodotto scalare standard tra due vettori.....dot_prod
5. Funzione per il calcolo della norma di un vettore............................norma
6. Funzione per il calcolo del prodotto vettoriale in R3....................vect_prod
7. Funzione per il calcolo del prodotto misto in R3..........................mix_prod
8. Funzione per la somma tra matrici.......................................matrix_sum
9. Funzione per la differenza tra matrici.................................matrix_diff
10. Funzione per la moltiplicazione di una matrice per uno scalare........matrix_scal
11. Funzione per la trasposizione di una matrice...........................transposal
12. Funzione per la moltiplicazione tra due matrici.....................matrix_matrix
13. Funzione per il prodotto vettore-matrice............................vector_matrix
14. Funzione per il prodotto matrice-vettore............................matrix_vector
15. Funzione per la propagazione degli errori casuali............................prop
16. Funzione per calcolare il determinante di una matrice 3x3...................det33
*/

#include <cmath>
#include <vector>
#include <array>

using namespace std;

// 1. Funzione per la somma tra vettori

vector <double> vector_sum(vector <double> a, vector <double> b) {

	vector <double> c;
	double d;

	for(int i = 0; i < a.size(); i++) {
		d = a[i] + b[i];
		c.push_back(d);
		}

	return c;
	}

// 2. Funzione per la differenza tra vettori

vector <double> vector_diff(vector <double> a, vector <double> b) {

	vector <double> c;
	double d;

	for(int i = 0; i < a.size(); i++) {
		d = a[i] - b[i];
		c.push_back(d);
		}

	return c;
	}

// 3. Funzione per la moltiplicazione di un vettore per uno scalare

vector <double> scalar(double c, vector <double> a) {

	vector <double> b;
	double d;

	for(int i = 0; i < a.size(); i++) {
		d = c*a[i];
		b.push_back(d);
		}

	return b;
	}

// 4. Funzione per il calcolo del prodotto scalare standard tra due vettori

double dot_prod(vector <double> a, vector <double> b) {

	double c = 0;
	for(int i = 0; i < a.size(); i++) {
		c = c + a[i]*b[i];
		}

	return c;
	}

// 5. Funzione per il calcolo della norma di un vettore

double norma(vector <double> v) {

	double n = sqrt(dot_prod(v, v));

	return n;
	}

// 6. Funzione per il calcolo del prodotto vettoriale in R3

vector <double> vect_prod(vector <double> a, vector <double> b) {

	vector <double> c(3);

	c[0] = a[2]*b[3] - a[3]*b[2];
	c[1] = a[3]*b[1] - a[1]*b[3];
	c[2] = a[1]*b[2] - a[2]*b[1];

	return c;
	}

// 7. Funzione per il calcolo del prodotto misto in R3

double mix_prod(vector <double> a, vector <double> b, vector <double> c) {

	double d = dot_prod(vect_prod(a, b), c);

	return d;
	}

// 8. Funzione per la somma tra matrici

vector <vector <double>> matrix_sum(vector <vector <double>> a, vector <vector <double>> b) {

	vector <vector <double>> c;
	vector <double> d;

	for(int i = 0; i < a.size(); i++) {
		d = vector_sum(a[i], b[i]);
		c.push_back(d);
		}

	return c;
	}

// 9. Funzione per la differenza tra matrici

vector <vector <double>> matrix_diff(vector <vector <double>> a, vector <vector <double>> b) {

	vector <vector <double>> c;
	vector <double> d;

	for(int i = 0; i < a.size(); i++) {
		d = vector_diff(a[i], b[i]);
		c.push_back(d);
		}

	return c;
	}

// 10. Funzione per la moltiplicazione di una matrice per uno scalare

vector <vector <double>> matrix_scal(double c, vector <vector <double>> a) {

	vector <vector <double>> b;
	vector <double> d;

	for(int i = 0; i < a.size(); i++) {
		d = scalar(c, a[i]);
		b.push_back(d);
		}

	return b;
	}

// 11. Funzione per la trasposizione di una matrice

vector <vector <double>> transposal(vector <vector <double>> m) {

	vector <vector <double>> t(m[0].size());
	double c;

	for(int i = 0; i < m.size(); i++) {
		for(int j = 0; j < m[i].size(); j++) {
			c = m[i][j];
			t[j].push_back(c);
			}
		}

	return t;
	}

// 12. Funzione per la moltiplicazione tra due matrici

vector <vector <double>> matrix_matrix(vector <vector <double>> a, vector <vector <double>> b) {

	vector <vector <double>> t = transposal(b);
	vector <vector <double>> c(a.size());
	double d;

	for(int i = 0; i < a.size(); i++) {
		for(int j = 0; j < t.size(); j++) {
			d = dot_prod(a[i], t[j]);
			c[i].push_back(d);
			}
		}

	return c;
	}

// 13. Funzione per il prodotto vettore-matrice

vector <double> vector_matrix(vector <double> v, vector <vector <double>> m) {

	vector <vector <double>> t = transposal(m);
	vector <double> r;
	double c;

	for(int i = 0; i < m.size(); i++) {
		c = dot_prod(v, m[i]);
		r.push_back(c);
		}

	return r;
	}

// 14. Funzione per il prodotto matrice-vettore

vector <double> matrix_vector(vector <vector <double>> m, vector <double> v) {

	vector <double> r;
	double c;

	for(int i = 0; i < m.size(); i++) {
		c = dot_prod(m[i], v);
		r.push_back(c);
		}

	return r;
	}

// 15. Funzione per la propagazione degli errori casuali

double prop(vector <double> v, vector <vector <double>> m) {

	double err = sqrt(dot_prod(v, vector_matrix(v, m)));

	return err;
	}

// 16. Funzione per calcolare il determinante di una matrice 3x3

double det33(const array<array<double, 3>, 3>& matrice) {
    return matrice[0][0] * (matrice[1][1] * matrice[2][2] - matrice[1][2] * matrice[2][1]) -
           matrice[0][1] * (matrice[1][0] * matrice[2][2] - matrice[1][2] * matrice[2][0]) +
           matrice[0][2] * (matrice[1][0] * matrice[2][1] - matrice[1][1] * matrice[2][0]);
}















