#include <bits/stdc++.h>
#include "Point.h"
#include "Label.h"
#include "LLabel.h"

using namespace std;

Point M[1000][1000];
int n, m;

void printPoint(Point p) {
	cout << "[";
	for (int i = 0; i < p.size() - 1; ++i) {
		cout << p[i] << ", ";
	}
	cout << p[p.size() - 1] << "]";
}

void printLabel(Label l) {
	cout << "[";
	for (int i = 0; i < l.costs.size(); ++i) {
		cout << l.costs[i] << ", ";
	}
	cout << l.parent << ", " << l.idxOnListLabelParent << "]";
}

void printLLabel(LLabel lista) {
	for (int i = 0; i < lista.size(); ++i) {
		printLabel(lista[i]);
	}
}

void printPointMatrix() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			printPoint(M[i][j]);
			cout << " ";
		}
		cout << endl;
	}
}

bool AllTempListIsEmpty(LLabel verticesList[]) {
	for (int i = 0; i < n; ++i) {
		if (!verticesList[i].isEmpty())
			return false;
	}
	return true;
}

Label getSmallerLexicografically(int *vId, LLabel temp[]) {

	//percorrer todos os labels para achar o menor lexicograficamente
	*vId = 0;
	int auxVId;
	Label menor = temp[0].labelToVisit(&auxVId);
	Label lAux;
	for (int i = 1; i < n; ++i) {
		if ( temp[i].size() > 0 ){
			lAux = temp[i].labelToVisit(&auxVId);
			if ( lAux < menor ) {
				menor = lAux;
				*vId = i;
			} 
		}
	}

	temp[*vId].remove(auxVId);

	return menor;
}

int main() {

	cin >> n >> m;
	LLabel permanentes[n], temp[n];

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			vector<int> v;
			for (int k = 0; k < m; k++) {
				int aux;
				cin >> aux;
				v.push_back(aux);
			}
			M[i][j] = Point(v);
		}
	}

	printPointMatrix();
	
	cout << "Número de vértices: " << n << ". Labels (0, ..., " << n - 1 << ")" << endl;
	cout << "Número de objetivos: " << m << endl;

	int l0[m] = {0};
	Label s(l0, 3, -1, -1);
	temp[0].add(s);

	int vId = 0;

	while (!AllTempListIsEmpty(temp)) {
		//remove e pega o menor rótulo lexicograficamente
		Label current = getSmallerLexicografically(&vId, temp);//temp[vId].labelToVisit();
		//adiciona current na lista de permantes de vId
		int h = permanentes[vId].add(current);
		//rotuala os sucessores de current
		for (int j = 0; j < n; ++j) {
			Point aux = M[vId][j];
			Label lj(current.costs.sum(aux), vId, h);
			temp[j].add(lj);
		}
		cout << "vId: " << vId << endl;

		for (int i = 0; i < n; ++i) {
			printLLabel(temp[i]);
		}

	}

	/*int a[5] = {1, 1, 2, 1, 4};
	Point pa(a, 5);
	Label la(pa, 2, 3);

	int b[5] = {1, 1, 2, 1, 4};
	Point pb(b, 5);
	Label lb(pb, 2, 3);

	int c[5] = {0, 0, 0, 0, 0};
	Point pc(c, 5);
	Label lc(pc, 2, 3);

	l.add(la);
	l.add(lb);
	l.add(lc);*/

	

	//int d[5] = {2, 2, 4, 0, 5};
	//Point ld(a, 5);

	return 0;
}