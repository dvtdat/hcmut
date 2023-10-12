#include "main.h"
#include <assert.h>

const int MAXSZ = 10;
const int inf = (int)1e9;

class LList {
protected:
	Restaurant::customer* head;
	Restaurant::customer* tail;
	Restaurant::customer* curr;
	int cnt, size;

	void init() {
		curr = head = new Restaurant::customer("", 0, nullptr, nullptr);
		tail = new Restaurant::customer("", 0, nullptr, nullptr);
		head->next = tail;
		tail->prev = head;
		cnt = 0;
	}

	void removeAll() {
		Restaurant::customer* tmp = head->next;
        while (tmp != tail && tmp != nullptr) {
            Restaurant::customer* nxt = tmp->next;
            delete tmp;
            tmp = nxt;
        }
        delete head;
        delete tail;
	}
public:
	LList(int size = MAXSZ): size(size) { init(); }
	~LList() { removeAll(); }

	void clear() { removeAll(); init(); }

	void append(const string& name, const int& energy) {
		Restaurant::customer* tmp = new Restaurant::customer(name, energy, tail->prev, tail);
		tail->prev->next = tmp;
		tail->prev = tmp;
		cnt++;
	}

	Restaurant::customer* remove(const int& indicies, bool print) {
		if (cnt == 0) return nullptr;
		Restaurant::customer* tmp = head->next;
		Restaurant::customer* ptr = nullptr;
		while (tmp != tail && tmp != head) {
			if ((tmp->energy < 0 && indicies < 0) || (tmp->energy > 0 && indicies >= 0)) {
				tmp = tmp->next;
				continue;
			}

			Restaurant::customer* del = tmp;
			tmp->prev->next = del->next;
			tmp->next->prev = del->prev;
			cnt--;
			if (curr == del) curr = tmp->prev;
			if (print) del->print();
			// delete del;

			ptr = tmp;
			tmp = tmp->next;
		}

		return ptr;
	}

	void pop() {
		if (cnt == 0) return;
		Restaurant::customer* tmp = head->next;
		head->next = tmp->next;
		tmp->next->prev = head;
		curr = head;
		cnt--;
		// delete tmp;
	}

	int insertionSort(Restaurant::customer* tmp, int n, int gap) {
		Restaurant::customer* x = tmp;
		int inc, moves = 0;
		for (int i = gap; i < n; i += gap) {
			for (inc = 0; inc < gap; ++inc) x = x->next;
			Restaurant::customer* y = x;
			int j = i;
			while (j >= gap) {
				Restaurant::customer* z = y;
				// cout << z->next->name << ' ' << y->next->name << '\n';
				for (inc = 0; inc < gap; ++inc) z = z->prev;
				if (abs(z->next->energy) >= abs(y->next->energy)) {
					swap(y->next->energy, z->next->energy);
					swap(y->next->name, z->next->name);
					moves += 3;
				}
				j -= gap;
				for (inc = 0; inc < gap; ++inc) y = y->prev;
			}
		}

		return moves;
	}

	int shellSort(int n) {
		int moves = 0;	
		Restaurant::customer* tmp = head;
		for (int i = n / 2; i > 2; i /= 2) {
			for (int j = 0; j < i; ++j) {
				moves += insertionSort(tmp, n - j, i);
				tmp = tmp->next;
			}
		}
		moves += insertionSort(head, n, 1);
		return moves;
	}
	
	int getTotal() const {
		if (cnt == 0) return 0;
		int total = 0;
		Restaurant::customer* tmp = head;
		do {
			total += tmp->energy;
			tmp = tmp->next;
		} while (tmp != head && tmp != tail);
		return total;
	}

	void moveToStart() { curr = head; }
	void moveToEnd() { curr = tail; }
	void moveToPtr(Restaurant::customer* ptr) { curr = ptr; }
	void next() { if (curr->next != tail) curr = curr->next; }
	void prev() { if (curr->prev != head) curr = curr->prev; }
	int length() const { return cnt; }
	int limit() const { return size; }
	bool full() const { return (cnt >= size); }

	string getName() const { return curr->next->name; }
	int getEnergy() const {	return curr->next->energy; }
	Restaurant::customer* getCurrent() const { return curr->next; }

	void moveToPtrByName(string name) {
		if (cnt == 0) return;
		Restaurant::customer* tmp = head;
		while (tmp != tail && tmp != head) {
			if (tmp->next->name == name) {
				curr = tmp;
				return;
			}
			tmp = tmp->next;
		}
		return;
	}

	bool find(string& name) {
		if (cnt == 0) return false;
		Restaurant::customer* tmp = head;
		while (tmp != tail && tmp != head) {
			if (tmp->next->name == name) return true;
			tmp = tmp->next;
		}
		return false;
	}

	Restaurant::customer* locateMax() const {
		if (cnt == 0) return nullptr;
		Restaurant::customer* ptr = head;
		Restaurant::customer* tmp = head;
		
		int mx = 0;
		while (tmp->next != tail && tmp->next != head) {
			if (abs(tmp->next->energy) >= mx) {
				mx = abs(tmp->next->energy);
				ptr = tmp;
			}
			tmp = tmp->next;
		}

		return ptr->next;
	}

	void print() const {
		if (cnt <= 0) {
			cout << '\n'; return;
		}
		Restaurant::customer* tmp = head;
		while (tmp->next != tail && tmp->next != head) {
			tmp->next->print();
			tmp = tmp->next;
		}
		cout << '\n';
	}
};

class CLList : public LList {
private:
	Restaurant::customer* start;
public:
	CLList(int size = MAXSZ) {
		curr = head = nullptr;
		start = new Restaurant::customer();
		cnt = 0;
		this->size = size;
	}
	~CLList() { removeAll(); }

	void insert(const string& name, const int& energy) {
		if (cnt == 0) {
			Restaurant::customer* tmp = new Restaurant::customer(name, energy, nullptr, nullptr);
			start->next = tmp; 
			tmp->prev = tmp; tmp->next = tmp;
			head = tmp; curr = start;
			cnt++;
			return;
		}
		Restaurant::customer* tmp = new Restaurant::customer(name, energy, curr, curr->next);
		curr->next->prev = tmp; curr->next = tmp;
		cnt++;
	}

	void remove(const int& indicies, bool print) {
		if (cnt == 0) return;
		Restaurant::customer* tmp = start->next;
		do {
			if ((tmp->energy < 0 && indicies < 0) || (tmp->energy > 0 && indicies >= 0)) {
				tmp = tmp->next;
				continue;
			}
			Restaurant::customer* del = tmp;
			tmp->prev->next = del->next;
			tmp->next->prev = del->prev;
			cnt--;

			if (curr == del) curr = tmp->prev;
			if (head == del) {
				head = tmp->prev;
				start->next = tmp->prev;
			}
			// delete del;
			tmp = tmp->next;
		} while (tmp != start->next);

		if ((start->next->energy < 0 && indicies < 0) || (start->next->energy > 0 && indicies >= 0)) return;

		Restaurant::customer* del = tmp;
		tmp->prev->next = del->next;
		tmp->next->prev = del->prev;
		cnt--;

		if (curr == del) curr = tmp->prev;
		head = del->prev;
		start->next = del->prev;
		// delete del;
		return;
	}

	void removeByName(const string& name) {
		if (cnt == 0) return;
		Restaurant::customer* tmp = head;
		do {
			if (tmp->name == name) {
				Restaurant::customer* del = tmp;
				tmp->prev->next = del->next;
				tmp->next->prev = del->prev;
				cnt--;
				if (curr == del) curr = tmp->prev;
				if (head == del) head = tmp->prev;
				// delete del;
				return;
			}
			tmp = tmp->next;
		} while (tmp != head);
	}

	void next() { curr = curr->next; }
	void prev() { curr = curr->prev; }

	string getName() const { return (curr ? curr->name : ""); }
	int getEnergy() const {	return (curr ? curr->energy : -inf); }
	
	Restaurant::customer* locateMaxDiff(int& energy) const {
		if (cnt == 0) return nullptr;
		Restaurant::customer* ptr = curr;
		Restaurant::customer* tmp = curr;
		int mx = 0;
		do {
			if (abs(tmp->energy - energy) > mx) {
				mx = abs(tmp->energy - energy);
				ptr = tmp;
			}
			tmp = tmp->next;
		} while (tmp != curr);
		return ptr;
		cout << '\n';
	}

	void printCWise() const {
		if (cnt == 0) {
			cout << '\n'; return;
		}
		Restaurant::customer* tmp = curr;
		do {
			tmp->print();
			tmp = tmp->next;
		} while (tmp != curr);
		cout << '\n';
	}

	void printCounterCWise() const {
		if (cnt == 0) {
			cout << '\n'; return;
		}
		Restaurant::customer* tmp = curr;
		do {
			tmp->print();
			tmp = tmp->prev;
		} while (tmp != curr);
		cout << '\n';
	}
};

class imp_res : public Restaurant {
private:
	LList* Queue = new LList(100);
	CLList* Table = new CLList(10);
	LList* Order = new LList(100);
public:	
	imp_res() {};
	void RED(string name, int energy) {
		if (energy == 0) return;

		if (Table->length() == 0 && !Table->full()) {
			Table->insert(name, energy);
			Order->append(name, energy);
			Table->next();
			return;
		}

		if (Table->find(name) || Queue->find(name)) return;

		if (Table->full()) {
			if (!Queue->full()) Queue->append(name, energy);
			return;
		}

		if (Table->length() >= Table->limit() / 2) {
			Restaurant::customer* pos = Table->locateMaxDiff(energy);
			Table->moveToPtr(pos);
			if (energy - Table->getEnergy() < 0) Table->prev();
			Table->insert(name, energy);
			Order->append(name, energy);
			Table->next();
			return;
		}

		// cout << Table->getName() << ' ' << Table->getEnergy() << " - " << name << ' ' << energy << '\n';

		if (energy < Table->getEnergy()) Table->prev();
		Table->insert(name, energy);
		Order->append(name, energy);
		Table->next();
	}

	void BLUE(int num) {
		while (num--) {
			Order->moveToStart();
			Table->removeByName(Order->getName());
			Order->pop();
		}

		while (Queue->length() && !Table->full()) {
			string name = Queue->getName();
			int energy = Queue->getEnergy(); 
			Queue->pop();
			RED(name, energy);
		}
	}

	void PURPLE() {
		Restaurant::customer* tmp = Queue->locateMax();
		Queue->moveToStart();
		int cnt = 0;
		while (Queue->getName() != tmp->name) {
			cnt++; Queue->next();
		}
		int moves = Queue->shellSort(cnt);
		BLUE(moves % MAXSZ);
	}

	void REVERSAL()	{
		cout << "reversal" << endl;
	}

	void UNLIMITED_VOID() {

	}

	void DOMAIN_EXPANSION()	{
		int total = Table->getTotal() + Queue->getTotal();
		Restaurant::customer* a;
		a = Order->remove(total, true);
		Table->moveToPtrByName(a->name);
		Table->remove(total, false);
		Queue->remove(total, true);
	}

	void LIGHT(int num)	{
		if (num > 0) Table->printCWise();
		if (num < 0) Table->printCounterCWise();
		if (num == 0) Queue->print();
	}

	void PRINT() {
		cout << '\n';
		cout << "Table:\n";
		Table->printCWise();

		cout << "Queue:\n";
		Queue->print();

		// cout << "Order:\n";
		// Order->print();
		cout << "--------------\n";
	}
};