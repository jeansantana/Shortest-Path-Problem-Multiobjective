#include <bits/stdc++.h>
#include "Point.h"
#include "Label.h"
#include "LLabel.h"

using namespace std;

//============MACROS================
#define FORR(i, a, b) for (int i = a; i < b; ++i)
#define FOR(i, a) FORR(i, 0, a)

Point M[1000][1000];
/*typedef pair<int, Point> element;
typedef vector<element> Graph;*/
int n, m; // vértices, número de objetivos
typedef vector<int> vi;

string filename;

/*void printPoint(Point p) {
	cout << "[";
	for (int i = 0; i < p.size() - 1; ++i) {
		cout << p[i] << ", ";
	}
	cout << p[p.size() - 1] << "]";
}*/

void printPoint(Point p) {
	for ( int i = 0; i < p.size() - 1; i++ ) {
		cout << p[i] << ", ";
	}
	cout << p[ p.size() - 1 ] << endl;
}

void printVi(vi v) {
	for ( int i = 0; i < v.size() - 1; i++ ) {
		cout << v[i] << ", ";
	}
	cout << v[ v.size() - 1 ] << endl;
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
			cout << "\"";
			for (int k = 0; k < M[i][j].size() - 1; ++k) {
				cout << M[i][j][k] << ", " ;
			}
			cout << M[i][j][M[i][j].size()-1] << "\",";
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

bool AllTempListIsEmptyFrom1(LLabel verticesList[]) {
	for (int i = 1; i < n; ++i) {
		if (!verticesList[i].isEmpty())
			return false;
	}
	return true;
}

Label getSmallerLexicografically(int *vId, LLabel temp[]) {
	vi l(m, INT_MAX);
	Label menor(l, INT_MAX, INT_MAX);
	int idxToRemove = -1;
	for ( int i = 0; i < n; ++i ) {
		for ( int j = 0; j < temp[i].size(); ++j ) {
			if ( temp[i][j] < menor ) {
				menor = temp[i][j];
				*vId = i;
				idxToRemove = j;
			}
		}
	}

	if ( idxToRemove != -1 ) {
		temp[*vId].remove(idxToRemove);
	}

	return menor;
}

bool canAdd(LLabel temp[], LLabel permanentes[], int vId, Label l) {
	/*if (vId == 29) {
		cout << "L29: ";
		printLabel(l);
		cout << endl;
	}*/ 
	/*if ( vId == 29 && l.costs[0] == 64 && l.costs[1] == 145 ) {
		cout << "TESTE ENTRADA: \n";
		cout << temp[vId].labelIsAvailabelToIn(l) << endl;
		cout << permanentes[vId].labelIsAvailabelToIn(l) << endl;
	}*/
	return temp[vId].labelIsAvailabelToIn(l) && permanentes[vId].labelIsAvailabelToIn(l);
}

int countLabelNumber(LLabel ls[]) {
	int num = 0;
	for (int i = 0; i < n; ++i) {
		num+= ls[i].size();
		/*for (int i = 0; i < ls[i].size(); ++i) {
		}*/
	}
	return num;
}

bool isZero(Point p) {
	for (int i = 0; i < m; ++i) {
		if (p[i] != 0) return false;
	}
	return true;
}

void printAllLabels(LLabel ls[]) {
	cout << "----------\nLabel list: " << endl;
	for (int i = 0; i < n; ++i) {
		cout << "Labels do vértice " << i << ":\n";
		printLLabel(ls[i]); 
		cout << endl;
	}
	cout << "----------\n";
}

void printPathFromZeroAux(LLabel p[], int f, int i) {
	int g, j;
	while ( f != 0 ) {
		g = p[f][i].parent;
		j = p[f][i].idxOnListLabelParent;

		//printPoint(M[g][f]);
		cout << g << " " << endl;

		f = g, i = j;
	}  
}

void printPathFromZero(LLabel p[], int tam, int f) {

	for (int i = 0; i < tam; ++i) {
		cout << "\nCaminho:\n";
		printPathFromZeroAux(p, f, i);
	}

}

void createFile(string name, string content) {
	ofstream outfile ("paretos/martins/" + name);
	outfile << content << endl;
	outfile.close();
}

string solutionToString(vi v) {
	
	string res="";

	FOR ( i, v.size() - 1 ) {
		res+= to_string(v[i]) + " ";
	} 
	res+= to_string( v[ v.size() - 1 ] );
	//cout << res << endl;
	return res;
}

int run(int n, int m, int f) {
	clock_t tStart = clock();
	LLabel permanentes[n], temp[n];

	//printPointMatrix();
	
	/*cout << "Número de vértices: " << n << ". Labels (0, ..., " << n - 1 << ")" << endl;
	cout << "Número de objetivos: " << m << endl;*/

	int l0[m] = {0};
	Label s(l0, m, -1, -1);
	temp[0].add(s);

	int vId = 0;
	int count = 0;
	while ( !AllTempListIsEmpty(temp) ) {
		/*cout << "\nTemporário de " << f << endl;
		printLLabel(temp[f]);
		cout << "\nPermanentes de " << f << endl;
		printLLabel(permanentes[f]);*/
		
		//cout << "\n\nIteração " << ++count << endl << "temp size: " << countLabelNumber(temp) << endl;
		//remove e pega o menor rótulo lexicograficamente
		//cout << "Pegando rótulo elegível... size temp: " << countLabelNumber(temp) << endl;
		Label current = getSmallerLexicografically(&vId, temp);//temp[vId].labelToVisit();
		
		//cout << "Visitando vértice: " << vId << endl << "temp size: " << countLabelNumber(temp) << endl;
		//cout << "Label permante: \n";
		//printLabel(current);
		//adiciona current na lista de permantes de vId
		//cout << "[FEITO!]Pegando rótulo elegível... size temp: " << countLabelNumber(temp) << endl;
		int h = permanentes[vId].add(current);
		/*if (vId == 29) {
			printLabel(current); cout << endl;
		}*/
		//cout << "\nLabels dos vértices adjacentes: \n";
		//rotuala os sucessores de current
		for (int j = 0; j < n; ++j) {
			Point aux = M[vId][j];
			if (vId != j) {
				Label lj(current.costs.sum(aux), vId, h);
				if (canAdd(temp, permanentes, j, lj)) {
					//printLabel(lj);
					//cout << " was added in " << j << endl; 
					temp[j].add(lj);
				}
				//printLabel(lj); cout << endl;
			}
		}

		//printAllLabels(temp);

	}

	set<vi> pareto;
	for ( int i = 0; i < permanentes[f].size(); ++i ) {
		pareto.insert(permanentes[f][i].costs.values);
		//printPoint(permanentes[f][i].costs);
	}

	/*cout << "Número de vértices: " << n << "\nNúmero de objetivos: " << m << endl;
	cout << "Número de soluções não dominadas: " << countLabelNumber(permanentes) << endl;*/
	
	/* nome do arquivo (impresso na main), 
	número de objetivos, número de vértice, vértice final, número de soluções não dominadas, tempo*/

	double tempo = (double)(clock() - tStart)/CLOCKS_PER_SEC;
	cout << m << ", " << n << ", " << f << ", " << pareto.size() << ", ";
	printf("%.2fs\n", tempo);

	//create file
    string content = to_string(pareto.size()) + "\n";
    
    set<vi>::iterator it;
	for ( it = pareto.begin(); it != pareto.end(); ++it ) {
    	content+= solutionToString(*it) + "\n";
	}

    createFile(filename, content);
    //end create file

	//printPathFromZero(permanentes, permanentes[f].size(), f);



	//printPareto
	

	//imprimir pareto
	//printAllLabels(permanentes);
	//cout << "res: \n" << countLabelNumber(permanentes) - 1 << endl;
}

int getNvalue(int L) {
	return ( 1 + sqrt(2*L*4 + 1) ) / 2;
}

void converterMatrix() {

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << M[i][j][0] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << M[i][j][1] << " ";
		}
		cout << endl;
	}

}

int main(int argc, char const *argv[]) {
	//num obj e tam grafo
	/*cout << "no. temp labels: " << countLabelNumber(temp) << endl;*/
	int f, x, y, a, b;

	freopen (argv[1], "r", stdin);

	int nLinhas = 0;
	cin >> f;

	string fname(argv[1]);
	int idx = fname.rfind("/");
	if (idx != -1) fname = fname.substr(idx + 1, fname.length());

	cout << fname << ", ";
	filename = fname;

	while ( cin >> x >> y >> a >> b ) {

		nLinhas++;

		vi points;
		points.push_back(a);
		points.push_back(b);

		M[x][y] = Point(points);
		M[y][x] = Point(points);

		/*for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				vector<int> v;
				for (int k = 0; k < m; k++) {
					int aux;
					cin >> aux;
					v.push_back(aux);
				}
				M[i][j] = Point(v);
			}
		}*/

	}
	
	n = getNvalue(nLinhas);
	m = 2;

	vi pointZero(m, 0);
	for (int i = 0; i < n; ++i) {
		M[i][i] = pointZero;
	}

	
    run(n, m, f);
    //printf("Tempo de Execução: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

   	//printPointMatrix();
   	//converterMatrix();

	return 0;
}