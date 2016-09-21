using namespace std;

class Label {
public:

	Point costs;
	int parent;//A partir de que vértice o vértice que detém esse label em suas lista foi rotulado.
	int idxOnListLabelParent;

	Label() {}
	~Label(){}
	
	Label(Point costs, int parent, int idxOnListLabelParent) {
		this->costs = costs;
		this->parent = parent;
		this->idxOnListLabelParent = idxOnListLabelParent;
	}	

	Label(int v[], int n, int parent, int idxOnListLabelParent) {

		for (int i = 0; i < n; ++i) {
			costs.values.push_back(v[i]);
		}

		this->parent = parent;
		this->idxOnListLabelParent = idxOnListLabelParent;
	}

	Label(vector<int> v, int parent, int idxOnListLabelParent) {

		for (int i = 0; i < v.size(); ++i) {
			costs.values.push_back(v[i]);
		}

		this->parent = parent;
		this->idxOnListLabelParent = idxOnListLabelParent;
	}

	int operator[](int i) {
		return costs[i];
	}

	bool operator <(Label &l2) {
		for (int i = 0; i < this->costs.size(); ++i) {
			if (this->costs[i] == l2.costs[i]) continue;
			if (this->costs[i] < l2.costs[i]) return true;
			return false;
		}

		if (this->parent == l2.parent) {
			return this->idxOnListLabelParent < l2.idxOnListLabelParent;
		} else {
			return this->parent < l2.parent;
		}
	}

};