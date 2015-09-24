using namespace std;

class LLabel {
	
	vector<Label> labels;

public: 
	
	LLabel() {}

	~LLabel() {}

	LLabel(vector<Label> v) {
		this->labels = v;
	}

	int size() {
		labels.size();
	}

	bool labelIsAvailabelToIn(Label l) {
		for (int i = 0; i < size(); ++i) {
			if (labels[i].costs.dominate(l.costs)) {
				return false;
			}
		}
		return true;
	}

	bool removeAllDominated(Label l) {
		vector<Label> temp;
		for (int i = 0; i < labels.size(); ++i) {
			if (!l.costs.dominate(labels[i].costs)) {
				temp.push_back(labels[i]);
			}
		}

		labels = temp;
	}

	int add(Label l) {
		if (labels.size() == 0) {
			labels.push_back(l);
			return 0;
		} else if (labelIsAvailabelToIn(l)) {
			removeAllDominated(l);
			labels.push_back(l);
			return labels.size() - 1;
		}
	}

	Label operator[](int i) {
		return labels[i];
	}

	bool isEmpty() {
		return size() == 0;
	}

	//In lexicografic order
	Label labelToVisit(int *idx) {
		Label l = labels[0];
		*idx = 0;
		for (int i = 1; i < size(); ++i) {
			if (labels[i] < l) {
				l = labels[i];
				*idx = i;
			}
		}

		//labels.erase(labels.begin() + idx);

		return l;
	}

	void remove(int i) {
		labels.erase(labels.begin() + i);
	}

};