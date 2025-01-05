//Programma per analisi dati di laboratorio
//Gruppo III-4:
//Alessandro Jelveh, numero di matricola 2125416;
//Vittorio Giannerini, numero di matricola 2110860;
//Francesco Canella, numero di matricola 2210866.
//Universita' degli Studi di Padova
//Dipartimento di Fisica e Astronomia "Galileo Galilei" - Corso di studi di Fisica.
//Ultimo aggiornamento: 5/1/2025

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <array>

using namespace std;

//PROTOTIPI DELLE FUNZIONI:
vector <double> input_vettore();
double max(vector <double> v);
double min(vector <double> v);
double media(vector <double> a);
void cout_double(double b);
void print_vint(vector <int> v);
void print_vdouble(vector <double> v);
double stdev_campione(vector <double> c);
double stdev_pop(vector <double> v);
int input_freq();
vector <int> istogramma(vector <double> v, int classi);
double moda(vector <double> v, int a);
double mediana(vector<double> dati);
vector <int> classi(vector <double> dati);
vector <double> tresigma(vector <double> dati);
vector <double> interp_con(vector <double> x, vector <double> y, vector <double> s);
vector <double> interp_0(vector <double> x, vector <double> y, vector <double> s);
vector <double> interp_senza(vector <double> x, vector <double> y);
double media_pes(vector <double> x, vector <double> y);
bool chi_quadro1(vector <double> x, vector <double> y, double chi0);
bool chi_quadro2(vector <double> x, vector <double> y, vector <double> s, double chi0, double q, double m);
void fitParpost(vector <double> x, vector <double> y);
void fitParPri(vector <double> x, vector <double> y, vector <double> z);
double det33(const array<array<double, 3>, 3>& matrice);
double comp(double x, double y, double errx, double erry);

//MAIN:
int main() {

	bool check = true;
	bool boo;
	char keep = 'y';
	int opt;

	int freq;
	double d, m, q, a, b, c, x, y, errx, erry, l;
	vector <double> v, v2, v3, v4;
	vector <int> k;
	array<array<double, 3>, 3> matrice;

	cout << "Questo e' un programma di analisi dati di laboratorio." << endl << endl;

	do {

		cout << "Digita 1 e invia per calcolare la MEDIA." << endl;
		cout << "Digita 2 e invia per calcolare la DEVIAZIONE STANDARD SU UN CAMPIONE." << endl;
		cout << "Digita 3 e invia per calcolare la DEVIAZIONE STANDARD SULLA POPOLAZIONE." << endl;
		cout << "Digita 4 e invia per calcolare la MODA." << endl;
		cout << "Digita 5 e invia per calcolare la MEDIANA COME PUNTO MEDIO DI UNA CLASSE DI FREQUENZA." << endl;
		cout << "Digita 6 e invia per calcolare il NUMERO IDEALE DI CLASSI DI FREQUENZA SECONDO STURGES E SECONDO SCOTT." << endl;
		cout << "Digita 7 e invia per calcolare gli OUTLIERS DI UN CAMPIONE DI DATI SECONDO IL METODO 3-SIGMA." << endl;
		cout << "Digita 8 e invia per calcolare l'INTERPOLAZIONE LINEARE CON ERRORI A PRIORI." << endl;
		cout << "Digita 9 e invia per calcolare l'INTERPOLAZIONE LINEARE SENZA ERRORI A PRIORI." << endl;
		cout << "Digita 10 e invia per calcolare la MEDIA PESATA." << endl;
		cout << "Digita 11 e invia per eseguire il TEST DEL CHI-QUADRO, CASO MISURE RIPETUTE. " << endl;
		cout << "Digita 12 e invia per eseguire il TEST DEL CHI-QUADRO, CASO INTERPOLAZIONE Y=MX+Q. " << endl;
		cout << "Digita 13 e invia per eseguire la INTERPOLAZIONE PARABOLICA CON ERRORI A POSTERIORI. " << endl;
		cout << "Digita 14 e invia per eseguire la RILEVAZIONE DI MASSIMI SU UNA SINUSOIDE. " << endl;
		cout << "Digita 15 e invia per eseguire la RILEVAZIONE DI MINIMI SU UNA SINUSOIDE. " << endl;
		cout << "Digita 16 e invia per eseguire la INTERPOLAZIONE PARABOLICA CON ERRORI A PRIORI. " << endl;
		cout << "Digita 17 e invia per eseguire la INTERPOLAZIONE LINEARE PASSANTE PER L'ORIGINE. " << endl;
		cout << "Digita 18 e invia per eseguire la COMPATIBILITA' GAUSSIANA TRA DUE STIME. " << endl;


		cout << endl << "Come posso aiutare? " << endl;

		if (!(cin >> opt)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Input non valido, riprova." << endl << endl;
			continue;
		}

		else if (opt == 1) {
			cout << "Hai selezionato MEDIA. Occorre inserire gli elementi sui quali eseguire il calcolo. " << endl;
			v = input_vettore();
			d = media(v);
			cout_double(d);
		}

		else if (opt == 2) {
			cout << "Hai selezionato DEVIAZIONE STANDARD SU UN CAMPIONE. Occorre inserire gli elementi sui quali eseguire il calcolo. " << endl;
			v = input_vettore();
			d = stdev_campione(v);
			cout_double(d);
		}

		else if (opt == 3) {
			cout << "Hai selezionato DEVIAZIONE STANDARD SULLA POPOLAZIONE. Occorre inserire gli elementi sui quali eseguire il calcolo. " << endl;
			v = input_vettore();
			d = stdev_pop(v);
			cout_double(d);
		}

		else if (opt == 4) {
			cout << "Hai selezionato MODA. Occorre inserire gli elementi sui quali eseguire il calcolo e la classe di frequenza desiderata. " << endl;
			v = input_vettore();
			freq = input_freq();
			d = moda(v, freq);
			cout_double(d);

		}

		else if (opt == 5) {
			cout << "Hai selezionato MEDIANA COME PUNTO MEDIO DI UNA CLASSE DI FREQUENZA. Occorre inserire gli elementi sui quali eseguire il calcolo. " << endl;
			v = input_vettore();
			d = mediana(v);
			cout_double(d);
		}

		else if (opt == 6) {
			cout << "Hai selezionato NUMERO IDEALE DI CLASSI DI FREQUENZA SECONDO STURGES E SCOTT. Occorre inserire le misure sulle quali eseguire il calcolo. " << endl;
			v = input_vettore();
			k = classi(v);
			cout << endl << "Secondo la REGOLA DI STURGES, il numero di classi di frequenza risulta: " << k[0];
			cout << endl << "Secondo la REGOLA DI SCOTT, il numero di classi di frequenza risulta: " << k[1] << endl << endl;
		}

		else if (opt == 7) {
			cout << "Hai selezionato OUTLIERS DI UN CAMPIONE DI DATI SECONDO IL METODO 3-SIGMA. Occorre inserire le misure sulle quali eseguire il calcolo. " << endl;
			v = input_vettore();
			v2 = tresigma(v);
			if (v != v2) {
				cout << "Si procede con la stampa dei dati aggiornati." << endl;
				print_vdouble(v2);
				cout << "La media aggiornata risulta: " << media(v2) << endl;
				cout << "La deviazione standard sulla popolazione aggiornata risulta: " << stdev_pop(v2) << endl;
				cout << "La deviazione standard sul campione aggiornato risulta: " << stdev_campione(v2) << endl;
			}
		}

		else if (opt == 8) {
			cout << "Hai selezionato INTERPOLAZIONE LINEARE CON ERRORI A PRIORI. Occorre inserire i due set di dati sui quali eseguire il calcolo, e infine il set di errori. " << endl;

			cout << endl << "Inserire i valori dell'ascissa: " << endl;
			v = input_vettore();
			cout << endl << "Inserire i valori dell'ordinata: " << endl;
			v2 = input_vettore();
			cout << endl << "Inserire il set di errori: " << endl;
			v3 = input_vettore();

			v4 = interp_con(v, v2, v3);
			cout << "Il coefficente angolare risulta: " << v4[0] << endl;
			cout << "L'errore sul coefficente angolare risulta: " << v4[1] << endl;
			cout << "Il punto di intersezione con l'asse delle ordinate risulta: " << v4[2] << endl;
			cout << "L'errore sul punto di intersezione con l'asse delle ordinate risulta: " << v4[3] << endl;
			cout << "La covarianza tra m e q risulta: " << v4[4] << endl;
			cout << "L'errore nuovo calcolato risulta: " << v4[5] << endl;
			cout << "Il coefficente di correlazione di Pearson risulta: " << v4[6] << endl;
		}

		else if (opt == 9) {
			cout << "Hai selezionato INTERPOLAZIONE LINEARE SENZA ERRORI A PRIORI. Occorre inserire i due set di dati sui quali eseguire il calcolo. " << endl;

			cout << endl << "Inserire i valori dell'ascissa: " << endl;
			v = input_vettore();
			cout << endl << "Inserire i valori dell'ordinata: " << endl;
			v2 = input_vettore();

			v3 = interp_senza(v, v2);
			cout << "Il coefficente angolare risulta: " << v3[0] << endl;
			cout << "L'errore sul coefficente angolare risulta: " << v3[1] << endl;
			cout << "Il punto di intersezione con l'asse delle ordinate risulta: " << v3[2] << endl;
			cout << "L'errore sul punto di intersezione con l'asse delle ordinate risulta: " << v3[3] << endl;
			cout << "La covarianza risulta: " << v3[4] << endl;
			cout << "L'errore nuovo calcolato risulta: " << v3[5] << endl;
			cout << "Il coefficente di correlazione di Pearson risulta: " << v3[6] << endl;
		}

		else if (opt == 10) {
			cout << "Hai selezionato MEDIA PESATA." << endl;
			cout << "Il calcolo della media pesata richiede in input due set contenenti rispettivamente i dati e i corrispettivi pesi." << endl;

			cout << endl << "Inserire il set di misure: " << endl;
			v = input_vettore();
			cout << endl << "Inserire i corrispettivi pesi: " << endl;
			v2 = input_vettore();

			d = media_pes(v, v2);
			cout << "La media pesata risulta: " << d << endl;
		}

		else if (opt == 11) {
			cout << "Hai selezionato TEST DEL CHI-QUADRO (per misure ripetute)." << endl;
			cout << "Per eseguire il test sono necessari in input il set di dati, il set degli errori, e il valore soglia chi-0. " << endl;

			cout << endl << "Inserire il set di misure: " << endl;
			v = input_vettore();
			cout << endl << "Inserire il set di errori: " << endl;
			v2 = input_vettore();
			cout << endl << "Inserire il valore di soglia chi-0: " << endl;
			cin >> d;
			b = chi_quadro1(v, v2, d);
			if (b) {
				cout << endl << "Le ipotesi sono state accettate." << endl << endl;
			}
			else if (!b) {
				cout << endl << "Le ipotesi sono state rigettate." << endl << endl;
			}
		}

		else if (opt == 12) {
			cout << "Hai selezionato TEST DEL CHI-QUADRO (per interpolazione y = mx+q)." << endl;
			cout << "Per eseguire il test sono necessari in ordine: asse x, asse y, errori sulle y, coefficente angolare, intercetta, e valore soglia chi-0. " << endl;

			cout << endl << "Inserire i valori dell'ascissa: " << endl;
			v = input_vettore();
			cout << endl << "Inserire i valori dell'ordinata: " << endl;
			v2 = input_vettore();
			cout << endl << "Inserire il set di errori sulle y: " << endl;
			v3 = input_vettore();
			cout << endl << "Inserire il coefficente angolare: " << endl;
			cin >> m;
			cout << endl << "Inserire il valore dell'intercetta: " << endl;
			cin >> q;
			cout << endl << "Inserire il valore di soglia chi-0: " << endl;
			cin >> d;
			boo = chi_quadro2(v, v2, v3, d, q, m);
			if (boo) {
				cout << endl << "Le ipotesi sono state accettate." << endl << endl;
			}
			else {
				cout << endl << "Le ipotesi sono state rigettate." << endl << endl;
			}
		}

		else if (opt == 13) {
			cout << "Hai selezionato FIT PARABOLICO CON ERRORI A POSTERIORI." << endl;
			cout << "Inserire i valori dell'ascissa dei punti: " << endl;
			v = input_vettore();
			cout << "Inserire i valori dell'ordinata dei punti: " << endl;
			v2 = input_vettore();

			fitParpost(v, v2);
		}

		else if (opt == 14) {
			cout << "Hai selezionato RILEVAZIONE DI MASSIMI SU UNA SINUSOIDE." << endl;
			cout << "Inserire i valori dell'ascissa dei punti: " << endl;
			v2 = input_vettore(); //ascissa
			cout << "Inserire i valori dell'ordinata dei punti: " << endl;
			v = input_vettore(); //ordinata
			for (int i = 4; i < v2.size() - 4; i++) {
				if (v[i] >= v[i - 1] && v[i] >= v[i - 2] && v[i] >= v[i - 3] && v[i] >= v[i - 4] &&
					v[i] >= v[i + 1] && v[i] >= v[i + 2] && v[i] >= v[i + 3] && v[i] >= v[i + 4])
				{
					v3.push_back(v[i]); // ordinata rilevata
					v4.push_back(v2[i]); //ascissa rilevata
				}
			}
			cout << endl << "Si procede con la stampa dei punti di massimo rilevati." << endl;
			for (int i = 0; i < v3.size(); i++) {
				cout << v4[i] << '\t' << v3[i] << endl;
			}
		}

		else if (opt == 15) {
			cout << "Hai selezionato RILEVAZIONE DI MINIMI SU UNA SINUSOIDE." << endl;
			cout << "Inserire i valori dell'ascissa dei punti: " << endl;
			v2 = input_vettore(); //ascissa
			cout << "Inserire i valori dell'ordinata dei punti: " << endl;
			v = input_vettore(); //ordinata
			for (int i = 4; i < v2.size() - 4; i++) {
				if (v[i] <= v[i - 1] && v[i] <= v[i - 2] && v[i] <= v[i - 3] && v[i] <= v[i - 4] &&
					v[i] <= v[i + 1] && v[i] <= v[i + 2] && v[i] <= v[i + 3] && v[i] <= v[i + 4])
				{
					v3.push_back(v[i]); // ordinata rilevata
					v4.push_back(v2[i]); //ascissa rilevata
				}
			}
			cout << endl << "Si procede con la stampa dei punti di minimo rilevati." << endl;
			for (int i = 0; i < v3.size(); i++) {
				cout << v4[i] << '\t' << v3[i] << endl;
			}
		}

		else if (opt == 16) {
			cout << "Hai selezionato FIT PARABOLICO CON ERRORI A PRIORI." << endl;
			cout << "Inserire i valori dell'ascissa dei punti: " << endl;
			v = input_vettore();
			cout << "Inserire i valori dell'ordinata dei punti: " << endl;
			v2 = input_vettore();
			cout << "Inserire gli errori sull'ordinata: " << endl;
			v3 = input_vettore();

			fitParPri(v, v2, v3);
		}

		else if (opt == 17) {
			cout << "Hai selezionato INTERPOLAZIONE LINEARE PASSANTE PER L'ORIGINE. Inserire i due set di dati sui quali eseguire il calcolo, e infine il set di errori. " << endl;

			cout << endl << "Inserire i valori dell'ascissa: " << endl;
			v = input_vettore();
			cout << endl << "Inserire i valori dell'ordinata: " << endl;
			v2 = input_vettore();
			cout << endl << "Inserire il set di errori: " << endl;
			v3 = input_vettore();

			v4 = interp_0(v, v2, v3);
			cout << "Il coefficente angolare risulta: " << v4[0] << endl;
			cout << "L'errore sul coefficente angolare risulta: " << v4[1] << endl;

		}

		else if (opt == 18) {
			cout << "Hai selezionato COMPATIBILITA' GAUSSIANA. Inserire le stime con i relativi errori. " << endl;

			cout << "Inserire il primo valore: " << endl;
			cin >> x;
			cout << "Inserire l'errore del primo valore: " << endl;
			cin >> errx;
			cout << "Inserire il secondo valore: " << endl;
			cin >> y;
			cout << "Inserire l'errore del secondo valore: " << endl;
			cin >> erry;

			l = comp(x, y, errx, erry);

			cout << endl << "L'indice di compatibilita' k = " << l << endl;
		}

		else {
			cout << endl << "Opzione inesistente. " << endl << endl;
			continue;
		}

		cout << "Posso aiutare ancora? y/n ";
		do {
			cin >> keep;

			if (keep == 'y') {
				check = true;
				break;
			}

			else if (keep == 'n') {
				cout << endl << "Programma in chiusura. Arrivederci!" << endl;
				check = false;
				break;
			}

			else if (keep != 'y' && keep != 'n') {
				cout << endl << "Inserire un input valido: 'y' in caso affermativo, 'n' in caso contrario." << endl;
				cout << "Posso aiutare ancora? y/n ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}

		} while (1);


	} while (check == true);

	cout << endl;


	return 0;
}

//DEFINIZIONI DELLE FUNZIONI:

//Input vettore:
vector <double> input_vettore() {

	int opt;
	cout << endl << "Per inserire gli elementi da tastiera, digita 1 e invia." << endl;
	cout << "Per inserire gli elementi da un file, digita 2 e invia." << endl << endl;
	double d;

	vector <double> v;

	do {

		if (!(cin >> opt)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Input non valido, riprova." << endl;
			continue;
		}

		else if (opt == 1) {
			string input;
			cout << "Inserire gli elementi del vettore: (inviare 'stop' per concludere l'inserimento)" << endl;

			while (cin >> input && input != "stop") {
				try {
					d = stod(input);
					v.push_back(d);
				}
				catch (const invalid_argument e) {
					cout << "Errore: Inserire un valore numerico valido." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin.sync();
				}
			}

			return v;

		}

		else if (opt == 2) {

			bool check;
			string input;
			do {
				cout << "Inserire il nome del file contenente gli elementi del vettore: ";
				cin >> input;
				ifstream inputfile(input);
				if (inputfile.is_open()) {
					check = true;
					while (inputfile >> d) {
						v.push_back(d);
					}
					inputfile.close();
				}
				else {
					cout << "Impossibile aprire il file, ricontrolla e riprova." << endl;
					check = false;
				}
			} while (check == false);


			return v;
		}

		else {
			cout << "Opzione inesistente, ricontrolla e riprova." << endl;
		}

	} while (opt != 1 && opt != 2);
}

//Calcolo del valore massimo
double max(vector <double> v) {

	double massimo = v[0];
	for (auto c : v) {
		if (c > massimo) {
			massimo = c;
		}
	}

	return massimo;
}

//Calcolo del valore minimo
double min(vector <double> v) {

	double minimo = v[0];
	for (auto c : v) {
		if (c < minimo) {
			minimo = c;
		}
	}

	return minimo;
}

//Calcolo della media:
double media(vector <double> v) {

	double somma = 0;
	for (auto c : v) {
		somma = somma + c;
	}

	double med = somma / v.size();
	return med;
}

//Cout di un double:
void cout_double(double d) {

	int opt;
	cout << endl << "Per stampare il risultato sullo schermo, digita 1 e invia." << endl;
	cout << "Per stampare il risultato su un file, digita 2 e invia." << endl << endl;


	do {

		if (!(cin >> opt)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Input non valido, riprova." << endl;
			continue;
		}

		else if (opt == 1) {
			cout << endl << "L'operazione risulta: " << d << endl << endl;
		}
		else if (opt == 2) {
			string destinazione;
			bool check;

			do {
				cout << endl << "Inserire il nome del file nel quale stampare i risultati: ";
				cin >> destinazione;
				ofstream outputfile(destinazione, ios::app);

				if (outputfile.is_open()) {
					check = true;
					outputfile << d << endl;
					outputfile.close();
				}

				else {
					cout << "Impossibile aprire il file, controlla la scrittura e riprova." << endl;
					check = false;
				}
			} while (check == false);
		}

		else {
			cout << "Opzione inesistente, riprova." << endl;
		}

	} while (opt != 1 && opt != 2);

}

//Cout vettore di int:
void print_vint(vector <int> v) {

	int opt;
	cout << endl << "Per stampare i risultati sullo schermo, digita 1 e invia." << endl;
	cout << "Per stampare i risultati su un file, digita 2 e invia." << endl << endl;
	cin >> opt;

	do {

		if (!(cin >> opt)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Input non valido, riprova." << endl;
			continue;
		}

		else if (opt == 1) {
			cout << endl << "Il vettore risulta: " << endl;
			for (auto c : v) {
				cout << c << "\t";
			}
			cout << endl << endl;
		}
		else if (opt == 2) {
			string destinazione;
			bool check;

			do {
				cout << endl << "Inserire il nome del file su cui stampare i risultati: ";
				cin >> destinazione;
				ofstream outputfile(destinazione, ios::app);
				if (outputfile.is_open()) {
					check = true;
					for (auto c : v) {
						outputfile << c << "\t";
					}
					outputfile << endl;
					cout << endl;
				}
				else {
					cout << "Impossibile aprire il file, controlla la scrittura e riprova. " << endl;
					check = false;
				}

			} while (check == false);

		}

		else {
			cout << "Opzione inesistente, riprova." << endl;
		}

	} while (opt != 1 && opt != 2);

}

//Cout vettore di double:
void print_vdouble(vector <double> v) {

	int opt;
	cout << endl << "Per stampare i risultati sullo schermo, digita 1 e invia." << endl;
	cout << "Per stampare i risultati su un file, digita 2 e invia." << endl << endl;
	cin >> opt;

	do {

		if (!(cin >> opt)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Input non valido, riprova." << endl;
			continue;
		}

		else if (opt == 1) {
			cout << endl << "Il vettore risulta: " << endl;
			for (auto c : v) {
				cout << c << "\t";
			}
			cout << endl << endl;
		}
		else if (opt == 2) {
			string destinazione;
			bool check;

			do {
				cout << endl << "Inserire il nome del file su cui stampare i risultati: ";
				cin >> destinazione;
				ofstream outputfile(destinazione, ios::app);
				if (outputfile.is_open()) {
					check = true;
					for (auto c : v) {
						outputfile << c << "\t";
					}
					outputfile << endl;
					cout << endl;
				}
				else {
					cout << "Impossibile aprire il file, controlla la scrittura e riprova. " << endl;
					check = false;
				}

			} while (check == false);

		}

		else {
			cout << "Opzione inesistente, riprova." << endl;
		}

	} while (opt != 1 && opt != 2);

}

//Determinante di una matrice 2x2
double determinant2x2(const vector<vector<double>>& mat) {
    return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
}

//Determinante di una matrice 3x3
double det33(const array<array<double, 3>, 3>& matrice) {
    return matrice[0][0] * (matrice[1][1] * matrice[2][2] - matrice[1][2] * matrice[2][1]) -
           matrice[0][1] * (matrice[1][0] * matrice[2][2] - matrice[1][2] * matrice[2][0]) +
           matrice[0][2] * (matrice[1][0] * matrice[2][1] - matrice[1][1] * matrice[2][0]);
}

// Funzione per calcolare il determinante di una matrice 3x3 per le funzioni dopo
double determinant3x3(const vector<vector<double>>& mat) {
    return mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1])
         - mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0])
         + mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);
}

// Funzione per calcolare la matrice dei cofattori
vector<vector<double>> cofactorMatrix(const vector<vector<double>>& mat) {
    vector<vector<double>> cof(3, vector<double>(3));

    cof[0][0] =  determinant2x2({{mat[1][1], mat[1][2]}, {mat[2][1], mat[2][2]}});
    cof[0][1] = -determinant2x2({{mat[1][0], mat[1][2]}, {mat[2][0], mat[2][2]}});
    cof[0][2] =  determinant2x2({{mat[1][0], mat[1][1]}, {mat[2][0], mat[2][1]}});

    cof[1][0] = -determinant2x2({{mat[0][1], mat[0][2]}, {mat[2][1], mat[2][2]}});
    cof[1][1] =  determinant2x2({{mat[0][0], mat[0][2]}, {mat[2][0], mat[2][2]}});
    cof[1][2] = -determinant2x2({{mat[0][0], mat[0][1]}, {mat[2][0], mat[2][1]}});

    cof[2][0] =  determinant2x2({{mat[0][1], mat[0][2]}, {mat[1][1], mat[1][2]}});
    cof[2][1] = -determinant2x2({{mat[0][0], mat[0][2]}, {mat[1][0], mat[1][2]}});
    cof[2][2] =  determinant2x2({{mat[0][0], mat[0][1]}, {mat[1][0], mat[1][1]}});

    return cof;
}

// Funzione per trasporre una matrice
vector<vector<double>> transposeMatrix(const vector<vector<double>>& mat) {
    vector<vector<double>> transposed(3, vector<double>(3));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            transposed[j][i] = mat[i][j];
        }
    }
    return transposed;
}

// Funzione per calcolare l'inversa di una matrice 3x3
vector<vector<double>> inverseMatrix(const vector<vector<double>>& mat) {
    double det = determinant3x3(mat);
    if (det == 0) {
        throw runtime_error("La matrice non è invertibile (determinante = 0).");
    }

    vector<vector<double>> cof = cofactorMatrix(mat);
    vector<vector<double>> adj = transposeMatrix(cof);

    // Divide ogni elemento dell'adjunta per il determinante
    vector<vector<double>> inverse(3, vector<double>(3));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inverse[i][j] = adj[i][j] / det;
        }
    }

    return inverse;
}

// Funzione di utilità per stampare una matrice
void printMatrix(const vector<vector<double>>& mat) {
    for (const auto& row : mat) {
        for (double val : row) {
            cout << val << "\t";
        }
        cout << endl;
    }
}

//Deviazione standard campionaria:
double stdev_campione(vector <double> v) {

	double a = 0;
	for (auto c : v) {
		a = a + (c - media(v)) * (c - media(v));
	}

	double sigma = sqrt(a / (v.size() - 1));
	return sigma;
}

//Deviazione standard sulla intera popolazione:
double stdev_pop(vector <double> v) {

	double a = 0;
	for (auto c : v) {
		a = a + (c - media(v)) * (c - media(v));
	}

	double sigma = sqrt(a / (v.size()));
	return sigma;
}

//Input classi di frequenza:
int input_freq() {

	cout << endl << "Inserire il numero di classi di frequenza da tastiera: " << endl;
	int classi;
	int temp;
	bool check;

	do {
		cout << endl << "Inserire l'intero desiderato: ";
		if (!(cin >> temp)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Input non valido, riprova." << endl;
			check = false;
		}

		if (temp < 2) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Input troppo piccolo, riprova." << endl;
			check = false;
		}

		else {
			classi = temp;
			check = true;
		}

	} while (check == false);

	return classi;
}

//Calcolo istogramma:
vector <int> istogramma(vector <double> v, int classi) {

	double maxv = max(v);
	double minv = min(v);

	vector <int> histo(classi, 0);
	double delta = (maxv - minv) / classi;

	for (int i = 0; i < classi; i++) {
		for (auto c : v) {
			if (c >= minv + i * delta && c <= minv + (i + 1) * delta) {
				++histo[i];
			}
		}
	}

	return histo;
}

//Calcolo della moda:
double moda(vector <double> v, int classi) {

	vector <int> hist = istogramma(v, classi);

	double maxhist = hist[0];
	int n = 0;
	for (int i = 0; i < hist.size(); i++) {
		if (hist[i] > maxhist) {
			maxhist = hist[i];
			n = i;
		}
	}

	double maxv = max(v);
	double minv = min(v);

	double delta = (maxv - minv) / classi;

	double m = minv + (n + 0.5) * delta;
	return m;
}

//Calcolo della mediana:
double mediana(vector<double> dati) {

	if (dati.empty()) {
		cerr << "Errore: il vettore è vuoto. Impossibile calcolare la mediana." << endl;
		return 0;
	}

	sort(dati.begin(), dati.end());
	size_t dimensione = dati.size();

	if (dati.size() % 2 == 0) {
		return (dati[dimensione / 2 - 1] + dati[dimensione / 2]) / 2;
	}
	else {
		return dati[dimensione / 2];
	}
}

//Calcolo numero classi di frequenza:
vector <int> classi(vector <double> dati) {

	vector <int> k;
	int f1, f2;
	int dim = dati.size();

	f1 = 1 + log2(dim);
	k.push_back(f1);

	vector<double> datiOrdinati = dati;
	sort(datiOrdinati.begin(), datiOrdinati.end());
	double devst = stdev_pop(dati);
	double w = 3.5 * devst / sqrt(dim);
	f2 = static_cast<int>(ceil((datiOrdinati.back() - datiOrdinati.front()) / w));
	k.push_back(f2);

	return k;

}

//Metodo 3 sigma:
vector <double> tresigma(vector <double> dati) {

	double sigma = stdev_pop(dati);
	double average = media(dati);
	vector <double> NewDati;

	for (auto c : dati) {
		if (c >= (average - (3 * sigma)) && c <= (average + (3 * sigma))) {
			NewDati.push_back(c);
		}
	}

	int outliers = dati.size() - NewDati.size();

	if (outliers == 0) {
		cout << endl << "Nessun outlier trovato." << endl;
	}

	else {
		cout << endl << "Numero di outliers trovati e rimossi: " << outliers << endl;
		cout << "Gli outliers sono i seguenti: " << endl;
		for (auto c : dati) {
			if (c < average - (3 * sigma)) {
				cout << c << endl;
			}
			if (c > average + (3 * sigma)) {
				cout << c << endl;
			}
		}
	}

	return NewDati;
}

//Interpolazione lineare con errori a priori:
vector <double> interp_con(vector <double> x, vector <double> y, vector <double> s) {

	vector <double> a, b;
	double a0, b0, c0 = 0, m = 0, q = 0, err_m = 0, err_q = 0, cov = 0;
	double somma0 = 0, somma1 = 0, somma2 = 0, somma3 = 0, somma4 = 0, somma5 = 0, somma6 = 0;

	for (int j = 0; j < x.size(); j++) {
		somma0 = somma0 + 1 / (s[j] * s[j]);
		somma1 = somma1 + x[j] / (s[j] * s[j]);
		somma2 = somma2 + (x[j] * x[j]) / (s[j] * s[j]);
		somma3 = somma3 + (x[j] - media(x)) * (y[j] - media(y));
		somma4 = somma4 + (x[j] - media(x)) * (x[j] - media(x));
		somma5 = somma5 + (y[j] - media(y)) * (y[j] - media(y));
	}

	for (int i = 0; i < y.size(); i++) {
		a0 = 1 / (s[i] * s[i]) * somma2 - x[i] / (s[i] * s[i]) * somma1;
		a.push_back(a0);
		b0 = x[i] / (s[i] * s[i]) * somma0 - 1 / (s[i] * s[i]) * somma1;
		b.push_back(b0);
	}

	for (int i = 0; i < y.size(); i++) {
		m = m + b[i] * y[i];
		err_m = err_m + pow(b[i] * s[i], 2);
		q = q + a[i] * y[i];
		err_q = err_q + pow(a[i] * s[i], 2);
		cov = cov + a[i] * b[i] * s[i] * s[i];
	}

	double delta = somma0 * somma2 - somma1 * somma1;
	m = (1 / delta) * m;
	err_m = (1 / delta) * sqrt(err_m);
	q = (1 / delta) * q;
	err_q = (1 / delta) * sqrt(err_q);
	cov = cov / (delta * delta);

	double post = 0;
	for (int i = 0; i < x.size(); i++) {
		post = post + (m * x[i] + q - y[i]) * (m * x[i] + q - y[i]);
	}

	double err_post = sqrt(post / (x.size() - 2));
	double pearson = somma3 / sqrt(somma4 * somma5);


	vector <double> inter(7);
	inter[0] = m;
	inter[1] = err_m;
	inter[2] = q;
	inter[3] = err_q;
	inter[4] = cov;
	inter[5] = err_post;
	inter[6] = pearson;

	return inter;
}

//Interpolazione lineare per retta passante per l'origine
vector <double> interp_0(vector <double> x, vector <double> y, vector <double> s) {

	vector <double> a, b;
	double m = 0, err_m = 0;
	double somma1 = 0, somma2 = 0;

	for (int j = 0; j < x.size(); j++) {
		somma1 = somma1 + ((x[j]*y[j]) / (s[j] * s[j]));
		somma2 = somma2 + ((x[j] * x[j]) / (s[j] * s[j]));
	}

	m = somma1/somma2;
	err_m = sqrt(1/somma2);

	vector <double> inter(2);
	inter[0] = m;
	inter[1] = err_m;

	return inter;
}

//Interpolazione lineare senza errori a priori
vector <double> interp_senza(vector <double> x, vector <double> y) {

	vector <double> a, b;
	double a0, b0, m = 0, q = 0, err_m = 0, err_q = 0, cov = 0, post = 0;
	double somma1 = 0, somma2 = 0, somma3 = 0, somma4 = 0, somma5 = 0;

	for (int j = 0; j < x.size(); j++) {
		somma1 = somma1 + x[j];
		somma2 = somma2 + x[j] * x[j];
		somma3 = somma3 + (x[j] - media(x)) * (y[j] - media(y));
		somma4 = somma4 + (x[j] - media(x)) * (x[j] - media(x));
		somma5 = somma5 + (y[j] - media(y)) * (y[j] - media(y));
	}

	for (int i = 0; i < y.size(); i++) {
		a0 = somma2 - x[i] * somma1;
		a.push_back(a0);
		b0 = x[i] * x.size() - somma1;
		b.push_back(b0);
	}

	for (int i = 0; i < y.size(); i++) {
		m = m + b[i] * y[i];
		q = q + a[i] * y[i];
	}

	double delta = x.size() * somma2 - somma1 * somma1;
	m = (1 / delta) * m;
	q = (1 / delta) * q;

	for (int i = 0; i < x.size(); i++) {
		post = post + (m * x[i] + q - y[i]) * (m * x[i] + q - y[i]);
	}

	post = sqrt(post / (x.size() - 2));

	for (int i = 0; i < y.size(); i++) {
		err_m = err_m + pow(b[i] * post, 2);
		err_q = err_q + pow(a[i] * post, 2);
		cov = cov + a[i] * b[i] * post * post;
	}

	err_m = (1 / delta) * sqrt(err_m);
	err_q = (1 / delta) * sqrt(err_q);
	cov = cov / (delta * delta);
	double pearson = somma3 / sqrt(somma4 * somma5);

	vector <double> inter(7);
	inter[0] = m;
	inter[1] = err_m;
	inter[2] = q;
	inter[3] = err_q;
	inter[4] = cov;
	inter[5] = post;
	inter[6] = pearson;

	return inter;
}

//Calcolo della media pesata:
double media_pes(vector <double> x, vector <double> y) {

    double somma1 = 0;
	double somma2 = 0;
	for (int i = 0; i < x.size(); i++) {
		somma1 = somma1 + x[i] / (y[i] * y[i]);
		somma2 = somma2 + 1 / (y[i] * y[i]);
	}

	double average = somma1 / somma2;
	double err = sqrt(1/somma2);
	cout << "L'errore sulla media pesata risulta: " << err << endl;
	return average;
}

//Test del chi-quadro, caso di verifica di misure ripetute
bool chi_quadro1(vector <double> x, vector <double> y, double chi0) {

	double eta = media_pes(x, y);

	double chi2 = 0;
	for (int i = 0; i < x.size(); i++) {
		chi2 = chi2 + (x[i] - eta) * (x[i] - eta) / (y[i] * y[i]);
	}
	cout << "X^2 = " << chi2;

	return chi2 < chi0;
}

//Test del chi-quadro, caso di verifica legge y = mx + q
bool chi_quadro2(vector <double> x, vector <double> y, vector <double> s, double chi0, double q, double m) {

	bool b;
	double chi2 = 0;
	for (int i = 0; i < y.size(); i++) {
		chi2 = chi2 + (y[i] - (m * x[i]) - q) * (y[i] - (m * x[i]) - q) / (s[i] * s[i]);
	}
	cout << "X^2 = " << chi2;

	if (chi2 < chi0) {
		return true;
	}
	if (chi2 > chi0) {
		return false;
	}

}

//Interpolazione parabolica errori a posteriori
void fitParpost(vector <double> x, vector <double> y) {

	vector <long double> a, b, c;
	long double a0, b0, c0;
	long double A = 0, B = 0, C = 0, post = 0, errA = 0, errB = 0, errC = 0, covAB = 0, covAC = 0, covBC = 0;
	long double s1 = 0, s2 = 0, s3 = 0, s4 = 0;

	for (int j = 0; j < x.size(); j++) {
		s1 = s1 + x[j];
		s2 = s2 + (x[j] * x[j]);
		s3 = s3 + (x[j] * x[j] * x[j]);
		s4 = s4 + (x[j] * x[j] * x[j] * x[j]);
	}

	long double delta = s4 * (s2 * x.size() - s1 * s1) - s3 * (s3 * x.size() - s2 * s1) + s2 * (s3 * s1 - s2 * s2);

	for (int i = 0; i < x.size(); i++) {
		a0 = (1 / delta) * (x[i] * x[i] * (s2 * x.size() - s1 * s1) - s3 * (x[i] * x.size() - s1) + s2 * (x[i] * s1 - s2));
		a.push_back(a0);
		b0 = (1 / delta) * (s4 * (x[i] * x.size() - s1) - x[i] * x[i] * (s3 * x.size() - s2 * s1) + s2 * (s3 - x[i] * s2));
		b.push_back(b0);
		c0 = (1 / delta) * (s4 * (s2 - x[i] * s1) - s3 * (s3 - x[i] * s2) + x[i] * x[i] * (s3 * s1 - s2 * s2));
		c.push_back(c0);
	}

	for (int i = 0; i < y.size(); i++) {
		A = A + a[i] * y[i];
		B = B + b[i] * y[i];
		C = C + c[i] * y[i];
	}

	for (int i = 0; i < y.size(); i++) {
		post = post + (A * x[i] * x[i] + B * x[i] + C - y[i]) * (A * x[i] * x[i] + B * x[i] + C - y[i]);
	}

	post = post / (y.size() - 3);

	for (int i = 0; i < y.size(); i++) {
		errA = errA + a[i] * a[i] * post;
		errB = errB + b[i] * b[i] * post;
		errC = errC + c[i] * c[i] * post;
		covAB = covAB + a[i] * b[i] * post;
		covAC = covAC + a[i] * c[i] * post;
		covBC = covBC + b[i] * c[i] * post;
	}

	errA = sqrt(errA);
	errB = sqrt(errB);
	errC = sqrt(errC);
	post = sqrt(post);

	cout << endl << "Per f(x) = A*(x^2) + B*(x) + C, abbiamo che: " << endl << endl;
	cout << "f(x) = (" << A << ")*(x^2) + (" << B << ")*(x) + (" << C << ")" << endl;
	cout << "L'errore su A risulta: " << errA << endl;
	cout << "L'errore su B risulta: " << errB << endl;
	cout << "L'errore su C risulta: " << errC << endl;
	cout << "La covarianza tra A e B risulta: " << covAB << endl;
	cout << "La covarianza tra A e C risulta: " << covAC << endl;
	cout << "La covarianza tra B e C risulta: " << covBC << endl;
	cout << "L'errore a posteriori risulta : " << post << endl;

}

//Interpolazione parabolica errori a priori
void fitParPri(vector <double> x, vector <double> y, vector <double> s) {

    double d;
    double Am = 0, Bm = 0, Cm = 0, Dm = 0, Em = 0, r0 = 0, r1 = 0, r2 = 0;
    array<array<double, 3>, 3> matrice;
    array<array<double, 3>, 3> matC;
    array<array<double, 3>, 3> matB;
    array<array<double, 3>, 3> matA;

    for (int i = 0; i < x.size(); i++) {
        Am = Am + (1/(s[i]*s[i]));
        Bm = Bm + ((x[i])/(s[i]*s[i]));
        Cm = Cm + ((x[i]*x[i])/(s[i]*s[i]));
        Dm = Dm + ((x[i]*x[i]*x[i])/(s[i]*s[i]));
        Em = Em + ((x[i]*x[i]*x[i]*x[i])/(s[i]*s[i]));
        r0 = r0 + ((y[i])/(s[i]*s[i]));
        r1 = r1 + ((x[i]*y[i])/(s[i]*s[i]));
        r2 = r2 + ((x[i]*x[i]*y[i])/(s[i]*s[i]));

    }

    matrice[0][0] = Am;
    matrice[0][1] = Bm;
    matrice[0][2] = Cm;
    matrice[1][0] = Bm;
    matrice[1][1] = Cm;
    matrice[1][2] = Dm;
    matrice[2][0] = Cm;
    matrice[2][1] = Dm;
    matrice[2][2] = Em;

    d = det33(matrice);

    vector<vector<double>> mat = {
        {Am, Bm, Cm},
        {Bm, Cm, Dm},
        {Cm, Dm, Em}
    };
        cout << endl << "Matrice di curvatura:" << endl;
        printMatrix(mat);

        vector<vector<double>> inv = inverseMatrix(mat);
        cout << endl << "Matrice di covarianza (inversa della curvatura):" << endl;
        printMatrix(inv);

        double varC = inv[0][0];
        double covCB = inv[0][1];
        double covCA = inv[0][2];
        double covBC = inv[1][0];
        double varB = inv[1][1];
        double covBA = inv[1][2];
        double covAC = inv[2][0];
        double covAB = inv[2][1];
        double varA = inv[2][2];

    matC[0][0] = r0;
    matC[0][1] = Bm;
    matC[0][2] = Cm;
    matC[1][0] = r1;
    matC[1][1] = Cm;
    matC[1][2] = Dm;
    matC[2][0] = r2;
    matC[2][1] = Dm;
    matC[2][2] = Em;

    matB[0][0] = Am;
    matB[0][1] = r0;
    matB[0][2] = Cm;
    matB[1][0] = Bm;
    matB[1][1] = r1;
    matB[1][2] = Dm;
    matB[2][0] = Cm;
    matB[2][1] = r2;
    matB[2][2] = Em;

    matA[0][0] = Am;
    matA[0][1] = Bm;
    matA[0][2] = r0;
    matA[1][0] = Bm;
    matA[1][1] = Cm;
    matA[1][2] = r1;
    matA[2][0] = Cm;
    matA[2][1] = Dm;
    matA[2][2] = r2;

    double C = (det33(matC)/d);
    double B = (det33(matB)/d);
    double A = (det33(matA)/d);

    double errA = sqrt(varA);
	double errB = sqrt(varB);
	double errC = sqrt(varC);

    cout << endl << "Per f(x) = A*(x^2) + B*(x) + C, abbiamo che: " << endl << endl;
	cout << "f(x) = (" << A << ")*(x^2) + (" << B << ")*(x) + (" << C << ")" << endl;
	cout << "L'errore su A risulta: " << errA << endl;
	cout << "L'errore su B risulta: " << errB << endl;
	cout << "L'errore su C risulta: " << errC << endl;
	cout << "La covarianza tra A e B risulta: " << covAB << endl;
	cout << "La covarianza tra A e C risulta: " << covAC << endl;
	cout << "La covarianza tra B e C risulta: " << covBC << endl;


}

//Funzione per calcolare la compatibilità tra due stime
double comp(double x, double y, double errx, double erry) {

    double k = (abs(x-y))/sqrt( errx*errx + erry*erry );

    return k;
}
