//Raccolta delle funzioni per l'inizializzazione e la stampa di variabili

/*
1. Funzione per l'inizializzazione di una variabile intera.....................create_int
2. Funzione per l'inizializzazione di una variabile decimale................create_double
3. Funzione per l'inizializzazione di un vettore di decimali................create_vector
4. Funzione per l'inizializzazione di una matrice di decimali...............create_matrix
5. Funzione per la stampa di una variabile decimale..........................print_double
6. Funzione per la stampa di un vettore di interi..............................print_vint
7. Funzione per la stampa di un vettore di decimali (precisione minore).....print_vdouble
8. Funzione per la stampa di un vettore di decimali (precisione maggiore).....print_vlong
9. Funzione per la stampa di una matrice di decimali.........................print_matrix
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// 1. Funzione per l'inizializzazione di una variabile intera

int create_int() {

	int m;
	cout << endl << "1. Inserimento variabile intera da tastiera" << endl;
	cout << "2. Inserimento variabile intera da file" << endl << endl;
	cout << "Selezionare l'opzione desiderata: ";
	cin >> m;

	int i;
	if		(m == 1)	{
		cout << endl << "Inserire l'intero desiderato: ";
		cin >> i;
		}
	else if	(m == 2)	{
		string input;
		cout << endl << "Inserire il nome del file contenente l'intero: ";
		cin >> input;
		ifstream inputfile(input);
		inputfile >> i;
		}

	return i;
	}

// 2. Funzione per l'inizializzazione di una variabile decimale

double create_double() {

	int m;
	cout << endl << "1. Inserimento variabile decimale da tastiera" << endl;
	cout << "2. Inserimento variabile decimale da file" << endl << endl;
	cout << "Selezionare l'opzione desiderata: ";
	cin >> m;

	double d;
	if		(m == 1)	{
		cout << endl << "Inserire il decimale desiderato: ";
		cin >> d;
		}
	else if	(m == 2)	{
		string input;
		cout << endl << "Inserire il nome del file contenente il decimale: ";
		cin >> input;
		ifstream inputfile(input);
		inputfile >> d;
		}

	return d;
	}

// 3. Funzione per l'inizializzazione di un vettore di decimali

vector <double> create_vector() {

	int m;
	cout << endl << "1. Inserimento vettore da tastiera" << endl;
	cout << "2. Inserimento vettore da file" << endl << endl;
	cout << "Selezionare l'opzione desiderata: ";
	cin >> m;

	double d;
	vector <double> v;

	if		(m == 1)	{
        string input;
        cout << "Inserire gli elementi del vettore: (scrivere 'stop' per interrrompere gli input)" << endl;
		while(cin >> input && input != "stop") {
		    d = stod(input);
			v.push_back(d);
        }
    return v;
	}

	else if	(m == 2)	{
		string input;
		cout << "Inserire il nome del file contenente gli elementi del vettore: ";
		cin >> input;
		ifstream inputfile(input);
		while(inputfile >> d) {
			v.push_back(d);
        }
	return v;
	}
}

// 4. Funzione per l'inizializzazione di una matrice di decimali

vector <vector <double>> create_matrix() {

	int m, p, q;
	cout << endl << "1. Inserimento matrice da tastiera" << endl;
	cout << "2. Inserimento matrice da file" << endl << endl;
	cout << "Selezionare l'opzione desiderata: ";
	cin >> m;
	cout << "Inserire le dimensioni della matrice: ";
	cin >> p >> q;

	double d;
	vector <vector <double>> matr(p, vector <double>(q));
	if		(m == 1)	{
		cout << "Inserire gli elementi della matrice:" << endl;
		for(int i = 0; i < p; i++) {
			for(int j = 0; j < q; j++) {
				cin >> d;
				matr[i][j] = d;
				}
			};
		}
	else if	(m == 2)	{
		string input;
		cout << "Inserire il nome del file contenente gli elementi della matrice: ";
		cin >> input;
		ifstream inputfile(input);
		for(int i = 0; i < p; i++) {
			for(int j = 0; j < q; j++) {
				inputfile >> d;
				matr[i][j] = d;
				}
			};
		}

	return matr;
	}

// 5. Funzione per la stampa di una variabile decimale

void print_double(double d) {

	int m;
	cout << endl << "1. Stampa risultati a schermo" << endl;
	cout << "2. Stampa risultati su file" << endl << endl;
	cout << "Selezionare l'opzione desiderata: ";
	cin >> m;

	if		(m == 1)	{
		cout << endl << "L'operazione risulta: " << d << endl << endl;
		}
	else if	(m == 2)	{
		string output;
		cout << endl << "Inserire il nome del file su cui stampare i risultati: ";
		cin >> output;
		ofstream outputfile(output, ios::app);
		outputfile << d << endl;
		cout << endl;
		}

	}

// 6. Funzione per la stampa di un vettore di interi

void print_vint(vector <int> v) {

	int m;
	cout << endl << "1. Stampa risultati a schermo" << endl;
	cout << "2. Stampa risultati su file" << endl << endl;
	cout << "Selezionare l'opzione desiderata: ";
	cin >> m;

	if		(m == 1)	{
		cout << endl << "Il vettore risultato dell'operazione è:" << endl;
		for(auto c : v) {
			cout << c << "\t";
			}
		cout << endl << endl;
		}
	else if	(m == 2)	{
		string output;
		cout << endl << "Inserire il nome del file su cui stampare i risultati: ";
		cin >> output;
		ofstream outputfile(output, ios::app);
		for(auto c : v) {
			outputfile << c << "\t";
			}
		outputfile << endl;
		cout << endl;
		}

	}

// 7. Funzione per la stampa di un vettore di decimali (precisione minore)

void print_vdouble(vector <double> v) {

	int m;
	cout << endl << "1. Stampa risultati a schermo" << endl;
	cout << "2. Stampa risultati su file" << endl << endl;
	cout << "Selezionare l'opzione desiderata: ";
	cin >> m;

	if		(m == 1)	{
		cout << endl << "Il vettore risultato dell'operazione è:" << endl;
		for(auto c : v) {
			cout << c << "\t";
			}
		cout << endl << endl;
		}
	else if	(m == 2)	{
		string output;
		cout << endl << "Inserire il nome del file su cui stampare i risultati: ";
		cin >> output;
		ofstream outputfile(output, ios::app);
		for(auto c : v) {
			outputfile << c << "\t";
			}
		outputfile << endl;
		cout << endl;
		}

	}

// 8. Funzione per la stampa di un vettore di decimali (precisione maggiore)

void print_vlong(vector <long double> v) {

	int m;
	cout << endl << "1. Stampa risultati a schermo" << endl;
	cout << "2. Stampa risultati su file" << endl << endl;
	cout << "Selezionare l'opzione desiderata: ";
	cin >> m;

	if		(m == 1)	{
		cout << endl << "Il vettore risultato dell'operazione è:" << endl;
		for(auto c : v) {
			cout << c << "\t";
			}
		cout << endl << endl;
		}
	else if	(m == 2)	{
		string output;
		cout << endl << "Inserire il nome del file su cui stampare i risultati: ";
		cin >> output;
		ofstream outputfile(output, ios::app);
		for(auto c : v) {
			outputfile << c << "\t";
			}
		outputfile << endl;
		cout << endl;
		}

	}

// 9. Funzione per la stampa di una matrice di decimali

void print_matrix(vector <vector <double>> matr) {

	int m;
	cout << endl << "1. Stampa risultati a schermo" << endl;
	cout << "2. Stampa risultati su file" << endl << endl;
	cout << "Selezionare l'opzione desiderata: ";
	cin >> m;

	if		(m == 1)	{
		cout << endl << "La matrice risultato dell'operazione è:" << endl;
		for(int i = 0; i < matr.size(); i++) {
			for(int j = 0; j < matr[i].size(); j++) {
				cout << matr[i][j] << "\t";
				}
			cout << endl;
			}
		cout << endl;
		}
	else if	(m == 2)	{
		string output;
		cout << endl << "Inserire il nome del file su cui stampare i risultati: ";
		cin >> output;
		ofstream outputfile(output, ios::app);
		for(int i = 0; i < matr.size(); i++) {
			for(int j = 0; j < matr[i].size(); j++) {
				outputfile << matr[i][j] << "\t";
				}
			outputfile << endl;
			}
		outputfile << endl;
		cout << endl;
		}

	}
