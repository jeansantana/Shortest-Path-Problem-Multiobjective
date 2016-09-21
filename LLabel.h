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
		return labels.size();
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
			} /*else {
				cout << "(" << labels[i].costs[0] << ", " << labels[i].costs[1] << ") was removed by " ;
				cout << "(" << l.costs[0] << ", " << l.costs[1] << ")\n";
			}*/
		}

		labels = temp;
	}

	//return the position where lable was inserted on the list
	int add(Label l) {
		if (labels.size() == 0) {
			labels.push_back(l);
			return 0;
		} else {
			removeAllDominated(l);
			labels.push_back(l);
			return labels.size() - 1;
		}
	}

	int add(Label l, bool remove) {
		if (labels.size() == 0) {
			labels.push_back(l);
			return 0;
		} else {
			if (remove) removeAllDominated(l);
			labels.push_back(l);
			return labels.size() - 1;
		}
	}

	Label operator[](int i) {
		return labels[i];
	}

	bool isEmpty() {

		return labels.size() == 0;
	}

	//In lexicografic order
	/*
	 * return the smaller label in lexicografical order, and idx on the list
	 */
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
		/*cout << "here\n";
		cout << "i = " << i << "\n";
		if (labels.size() != 0) {
			cout << "REMOVED: \n";
			Label l = labels[i];
			cout << "(" << l.costs[0] << ", " << l.costs[1] << ")\n";
		}*/
		labels.erase(labels.begin() + i);
	}

};