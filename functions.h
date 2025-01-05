//Raccolta delle funzioni per l'analisi dati

/*
1. Funzione per il calcolo del valore massimo.....................................max
2. Funzione per il calcolo del valore minimo......................................min
3. Funzione per il calcolo della media..........................................media
4. Funzione per il calcolo della deviazione standard..........................dev_std
5. Funzione per la reiezione dei dati a k-sigma.............................rejection
6. Funzione per il calcolo della media pesata..................................pesata
7. Funzione per il calcolo dell'errore sulla media pesata......................errore
8. Funzione per la creazione del grafico di dispersione (istogramma).......istogramma
9. Funzione per il calcolo della moda............................................moda
10. Funzione per il calcolo della mediana......................................mediana
11. Funzione per l'interpolazione lineare di dati (con errori a priori).......interp1
12. Funzione per l'interpolazione lineare di dati (senza errori a priori).....interp2
13. Funzione per il fit quadratico di dati........................................fit
14. Funzione per il calcolo della compatibilità gaussiana........................comp
15. Funzione per la verifica delle ipotesi con il test del chi quadro......chi_quadro
*/

#include <cmath>
#include <vector>

using namespace std;

// 1. Funzione per il calcolo del valore massimo

double max(vector <double> v) {
	
	double massimo = v[0];
	for(auto c : v) {
		if(c > massimo) {
			massimo = c;
			}
		}
	
	return massimo;
	}

// 2. Funzione per il calcolo del valore minimo

double min(vector <double> v) {
	
	double minimo = v[0];
	for(auto c : v) {
		if(c < minimo) {
			minimo = c;
			}
		}
	
	return minimo;
	}

// 3. Funzione per il calcolo della media

double media(vector <double> v) {
	
	double somma = 0;
	for(auto c : v) {
		somma = somma + c;
		}
	
	double average = somma/v.size();
	return average;
	}

// 4. Funzione per il calcolo della deviazione standard

double dev_std(vector <double> v) {
	
	double MSE = 0;
	for(auto c : v) {
		MSE = MSE + (c - media(v))*(c - media(v));
		}
	
	double sigma = sqrt(MSE/(v.size()-1));
	return sigma;
	}

// 5. Funzione per la reiezione dei dati a k-sigma

vector <double> rejection(vector <double> v, int k) {
	
	double m = media(v);
	double s = dev_std(v);
	
	for(int i = 0; i < v.size(); i++) {
		if(v[i] < m - k*s || v[i] > m + k*s) {
			v.erase(v.begin() + i);
			}
		}
	
	return v;
	}

// 6. Funzione per il calcolo della media pesata

double pesata(vector <double> v, vector <double> s) {
	
	double somma1 = 0;
	double somma2 = 0;
	for(int i = 0; i < v.size(); i++) {
		somma1 = somma1 + v[i]/(s[i]*s[i]);
		somma2 = somma2 + 1/(s[i]*s[i]);
		}
	
	double average = somma1/somma2;
	return average;
	}

// 7. Funzione per il calcolo dell'errore sulla media pesata

double errore(vector <double> s) {
	
	double somma = 0;
	for(int i = 0; i < s.size(); i++) {
		somma = somma + 1/(s[i]*s[i]);
		}
	
	double err = sqrt(1/somma);
	return err;
	}

// 8. Funzione per la creazione del grafico di dispersione (istogramma)

vector <int> istogramma(vector <double> v, int h) {
	
	double maxv = max(v);
	double minv = min(v);
	
	vector <int> histo(h, 0);
	double delta = (maxv - minv)/h;
	
	for(int i = 0; i < h; i++) {
		for(auto c : v) {
			if(c >= minv + i*delta && c <= minv + (i+1)*delta) {
				++histo[i];
				}
			}
		}

	return histo;
	}

// 9. Funzione per il calcolo della moda

double moda(vector <double> v, int h) {
	
	vector <int> f = istogramma(v, h);
	
	double maxf = f[0];
	int i = 0;
	for(int n = 0; n < f.size(); n++) {
		if(f[n] > maxf) {
			maxf = f[n];
			i = n;
			}
		}

	double maxv = max(v);
	double minv = min(v);

	double delta = (maxv - minv)/h;
	
	double mode = minv + (i+0.5)*delta;
	return mode;
	}

// 10. Funzione per il calcolo della mediana

double mediana(vector <double> v, int h) {
	
	double maxv = max(v);
	double minv = min(v);
	
	double delta = (maxv - minv)/h;
	vector <int> f = istogramma(v, h);
	
	double somma = 0;
	int k = 0;
	while(somma < v.size()/2) {
		somma = somma + f[k];
		k++;
		}
	
	double x = minv + k*delta + ((v.size() - 2*somma)*delta)/(2*f[k]);
	return x;
	}

// 11. Funzione per l'interpolazione lineare di dati (con errori a priori)

vector <double> interp1(vector <double> x, vector <double> y, vector <double> s) {
	
	vector <double> a, b;
	double a0, b0, m = 0, q = 0, err_m = 0, err_q = 0, cov = 0;
	double somma0 = 0, somma1 = 0, somma2 = 0, somma3 = 0, somma4 = 0, somma5 = 0;
	
	for(int j = 0; j < x.size(); j++) {
		somma0 = somma0 + 1/(s[j]*s[j]);
		somma1 = somma1 + x[j]/(s[j]*s[j]);
		somma2 = somma2 + (x[j]*x[j])/(s[j]*s[j]);
		somma3 = somma3 + (x[j] - media(x))*(y[j] - media(y));
		somma4 = somma4 + (x[j] - media(x))*(x[j] - media(x));
		somma5 = somma5 + (y[j] - media(y))*(y[j] - media(y));
		}
	
	for(int i = 0; i < y.size(); i++) {
		a0 = 1/(s[i]*s[i])*somma2 - x[i]/(s[i]*s[i])*somma1;
		a.push_back(a0);
		b0 = x[i]/(s[i]*s[i])*somma0 - 1/(s[i]*s[i])*somma1;
		b.push_back(b0);
		}
	
	for(int i = 0; i < y.size(); i++) {
		m = m + b[i]*y[i];
		err_m = err_m + pow(b[i]*s[i], 2);
		q = q + a[i]*y[i];
		err_q = err_q + pow(a[i]*s[i], 2);
		cov = cov + a[i]*b[i]*s[i]*s[i];
		}
	
	double delta = somma0*somma2 - somma1*somma1;
	m = (1/delta)*m;
	err_m = (1/delta)*sqrt(err_m);
	q = (1/delta)*q;
	err_q = (1/delta)*sqrt(err_q);
	cov = cov/(delta*delta);
	
	double post = 0;
	for(int i = 0; i < x.size(); i++) {
		post = post + (m*x[i] + q - y[i])*(m*x[i] + q - y[i]);
		}
	
	double err_post = sqrt(post/(x.size() - 2));
	double pearson = somma3/sqrt(somma4*somma5);

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

// 12. Funzione per l'interpolazione lineare di dati (senza errori a priori)

vector <double> interp2(vector <double> x, vector <double> y) {
	
	vector <double> a, b;
	double a0, b0, m = 0, q = 0, err_m = 0, err_q = 0, cov = 0, post = 0;
	double somma1 = 0, somma2 = 0, somma3 = 0, somma4 = 0, somma5 = 0;
	
	for(int j = 0; j < x.size(); j++) {
		somma1 = somma1 + x[j];
		somma2 = somma2 + x[j]*x[j];
		somma3 = somma3 + (x[j] - media(x))*(y[j] - media(y));
		somma4 = somma4 + (x[j] - media(x))*(x[j] - media(x));
		somma5 = somma5 + (y[j] - media(y))*(y[j] - media(y));
		}
	
	for(int i = 0; i < y.size(); i++) {
		a0 = somma2 - x[i]*somma1;
		a.push_back(a0);
		b0 = x[i]*x.size() - somma1;
		b.push_back(b0);
		}
	
	for(int i = 0; i < y.size(); i++) {
		m = m + b[i]*y[i];
		q = q + a[i]*y[i];
		}
	
	double delta = x.size()*somma2 - somma1*somma1;
	m = (1/delta)*m;
	q = (1/delta)*q;
	
	for(int i = 0; i < x.size(); i++) {
		post = post + (m*x[i] + q - y[i])*(m*x[i] + q - y[i]);
		}
	
	post = sqrt(post/(x.size() - 2));
	
	for(int i = 0; i < y.size(); i++) {
		err_m = err_m + pow(b[i]*post, 2);
		err_q = err_q + pow(a[i]*post, 2);
		cov = cov + a[i]*b[i]*post*post;
		}
	
	err_m = (1/delta)*sqrt(err_m);
	err_q = (1/delta)*sqrt(err_q);
	cov = cov/(delta*delta);
	double pearson = somma3/sqrt(somma4*somma5);

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

// 13. Funzione per il fit quadratico di dati

vector <long double> fit(vector <double> x, vector <double> y) {
	
	vector <long double> a, b, c;
	long double a0, b0, c0;
	long double A = 0, B = 0, C = 0, post = 0, errA = 0, errB = 0, errC = 0, covAB = 0, covAC = 0, covBC = 0;
	long double s1 = 0, s2 = 0, s3 = 0, s4 = 0;
	
	for(int j = 0; j < x.size(); j++) {
		s1 = s1 + x[j];
		s2 = s2 + (x[j]*x[j]);
		s3 = s3 + (x[j]*x[j]*x[j]);
		s4 = s4 + (x[j]*x[j]*x[j]*x[j]);
		}
	
	long double delta = s4*(s2*x.size()-s1*s1) - s3*(s3*x.size()-s2*s1) + s2*(s3*s1-s2*s2);
	
	for(int i = 0; i < x.size(); i++) {
		a0 = (1/delta)*(x[i]*x[i]*(s2*x.size()-s1*s1) - s3*(x[i]*x.size()-s1) + s2*(x[i]*s1-s2));
		a.push_back(a0);
		b0 = (1/delta)*(s4*(x[i]*x.size()-s1) - x[i]*x[i]*(s3*x.size()-s2*s1) + s2*(s3-x[i]*s2));
		b.push_back(b0);
		c0 = (1/delta)*(s4*(s2-x[i]*s1) - s3*(s3-x[i]*s2) + x[i]*x[i]*(s3*s1-s2*s2));
		c.push_back(c0);
		}
	
	for(int i = 0; i < y.size(); i++) {
		A = A + a[i]*y[i];
		B = B + b[i]*y[i];
		C = C + c[i]*y[i];
		}
	
	for(int i = 0; i < y.size(); i++) {
		post = post + (A*x[i]*x[i] + B*x[i] + C - y[i])*(A*x[i]*x[i] + B*x[i] + C - y[i]);
		}
	
	post = post/(y.size()-3);
	
	for(int i = 0; i < y.size(); i++) {	
		errA = errA + a[i]*a[i]*post;
		errB = errB + b[i]*b[i]*post;
		errC = errC + c[i]*c[i]*post;
		covAB = covAB + a[i]*b[i]*post;
		covAC = covAC + a[i]*c[i]*post;
		covBC = covBC + b[i]*c[i]*post;
		}
	
	errA = sqrt(errA);
	errB = sqrt(errB);
	errC = sqrt(errC);
	post = sqrt(post);
	
	vector <long double> inter(10);
	inter[0] = A;
	inter[1] = errA;
	inter[2] = B;
	inter[3] = errB;
	inter[4] = C;
	inter[5] = errC;
	inter[6] = covAB;
	inter[7] = covAC;
	inter[8] = covBC;
	inter[9] = post;

	return inter;
	}

// 14. Funzione per il calcolo della compatibilità

double comp(double a, double err_a, double b, double err_b) {
	
	double lambda = sqrt((a-b)*(a-b))/sqrt(err_a*err_a + err_b*err_b);
	return lambda;
	}

// 15. Funzione per la verifica delle ipotesi con il test del chi quadro

bool chi_quadro(vector <double> v, vector <double> s, double chi0) {
	
	double eta = pesata(v, s);
	double chi2 = 0;
	for(int i = 0; i < v.size(); i++) {
		chi2 = chi2 + (v[i] - eta)*(v[i] - eta)/(s[i]*s[i]);
		}

	return chi2 < chi0;
	}