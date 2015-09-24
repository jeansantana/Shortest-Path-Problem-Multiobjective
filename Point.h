using namespace std;

class Point {
public:

	vector<int> values;

	Point() {}
	~Point(){}

	/*v.size() - número de objetivos*/
	Point(vector<int> v) {
		this->values = v;
	}

	/*n - número de objetivos*/
	Point(int v[], int n) {
		for (int i = 0; i < n; ++i) {
			this->values.push_back(v[i]);
		}
	}

	int size() {
		return values.size();
	}

	//minimização
	//Não é pior que p em todos os objetivos
	bool isNotWorseAtAll(Point p) {
		for (int i = 0; i < size(); ++i) {
			if (this->values[i] > p[i]) {
				return false;
			}
		}
		return true;
	}

	bool existsAtLeastOneBetter(Point p) {
		for (int i = 0; i < size(); ++i) {
			if (this->values[i] < p[i] ) {
				return true;
			}
		}
	}

	//Este vetor domina p?
	bool dominate(Point p) {
		return this->isNotWorseAtAll(p) && this->existsAtLeastOneBetter(p);
	}

	int operator[](int i) {
		return values[i];
	}

	Point sum(Point p) {
		Point temp;
		for (int i = 0; i < size(); ++i) {
			temp.values.push_back(this->values[i] + p[i]);
		}
		return temp;
	}

	/*inline std::ostream & operator<<(Object const & v) { 
		std::ostream Str; 
		string res = "[";
		for (int i = 0; i < v.size() - 1; ++i) {
			res = v[i] + ", ";
		}
		res+= values[ v.size() - 1 ] + "]";
  		return Str << res;
	}*/
	
	/*Point<T> operator+ (const Point<int>& a, const Point<int>& b) {

		Point<int> temp;

		for (int i = 0; i < a.size(); ++i) {
			temp.values.push_back(a[i] + b[i]);
		}

		return temp;
	}*/

};