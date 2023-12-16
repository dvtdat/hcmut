#include "main.h"

const int inf = (int)1e9;

typedef Restaurant::customer Node;

class LList {
public:
	Node* head;
	Node* tail;
	Node* curr;
	int cnt, size;

	void init() {
		curr = head = new Node("", 0, nullptr, nullptr);
		tail = new Node("", 0, nullptr, nullptr);
		head->next = tail;
		tail->prev = head;
		cnt = 0;
	}
	void removeAll() {
		if (head == nullptr) return;

		Node* tmp = head;
		while (tmp->next != head && tmp->next != nullptr) {
			Node* nxt = tmp->next;

			if (tmp) {
				tmp->next = nullptr;
				tmp->prev = nullptr;
				delete tmp;
			}

			tmp = nxt;
		}
		
		if (tmp) {
			tmp->next = nullptr;
			tmp->prev = nullptr;
			delete tmp;
		}
		
		head = tail = curr = nullptr;
	}
public:
	LList(): size(0) {};
	LList(int size): size(size) { init(); }
	~LList() { removeAll(); }

	void append(const string& name, const int& energy) {
		cnt++;
		Node* tmp = new Node(name, energy, tail->prev, tail);
		tail->prev->next = tmp;
		tail->prev = tmp;
	}

	void remove(const int& indicies, LList* Order) {
		if (cnt == 0) return;
		Node* ptr = Order->head->next;
		do {
			Node* pp = ptr->next;
			if (find(ptr->name)) {
				if ((ptr->energy < 0 && indicies < 0) || (ptr->energy > 0 && indicies >= 0)) {
					ptr = pp;
					continue;
				}
				Node* tmp = head->next;
				for (; tmp->name != ptr->name; tmp = tmp->next);
				Node* del = tmp;
				tmp->prev->next = del->next;
				tmp->next->prev = del->prev;
				cnt--;

				if (del->energy < 0) curr = tmp->prev;
				else curr = tmp->next;

				if (head->next == del) head->next = tmp->prev;

				del->next = nullptr;
				del->prev = nullptr;
				delete del;
			}
			ptr = pp;
		} while (ptr != Order->tail && cnt > 0 && Order->cnt > 0);
	}

	void removeByOrder(const int& indicies) {
		if (cnt == 0) return;
		Node* ptr = tail->prev;

		do {
			Node* pp = ptr->prev;
			if ((ptr->energy < 0 && indicies >= 0) || (ptr->energy > 0 && indicies < 0)) {
				Node* del = ptr;
				ptr->prev->next = del->next;
				ptr->next->prev = del->prev;
				cnt--;

				if (del->energy < 0) curr = ptr->prev;
				else curr = ptr->next;

				if (head->next == del) head->next = ptr->prev;

				del->print();
				del->next = nullptr;
				del->prev = nullptr;
				delete del;
			}
			ptr = pp;
		} while (ptr != head && cnt > 0);
	}

	void pop() {
		if (cnt == 0) return;
		Node* tmp = head->next;
		head->next = tmp->next;
		tmp->next->prev = head;
		curr = head;
		cnt--;

		tmp->next = nullptr;
		tmp->prev = nullptr;
		delete tmp;
	}

	bool compare(Node* a, Node* b, LList* order) {
		if (abs(a->energy) > abs(b->energy)) return true;
		if (abs(a->energy) < abs(b->energy)) return false;

		int pos1 = 0, pos2 = 0, idx = 0;
		Node* tmp = order->head;
		while (tmp != nullptr) {
			if (pos1 && pos2) break;
			if (tmp->name == a->name) pos1 = idx;
			if (tmp->name == b->name) pos2 = idx;
			idx++;
			tmp = tmp->next;
		}

		if (pos1 < pos2) return true;
		return false;
	}

	void swapNodes(Node* a, Node* b, bool isCircular) {
		if (a == b || (a->next == b && b->next == a)) return;
		if (a->next == b) {
			a->prev->next = b;
			b->next->prev = a;
			a->next = b->next;
			b->prev = a->prev;
			a->prev = b;
			b->next = a;
		} else if (b->next == a) {
			b->prev->next = a;
			a->next->prev = b;
			b->next = a->next;
			a->prev = b->prev;
			b->prev = a;
			a->next = b;
		} else {
			a->prev->next = b;
			a->next->prev = b;
			b->prev->next = a;
			b->next->prev = a;
			swap(a->next, b->next);
			swap(a->prev, b->prev);
		}

		if (isCircular) {
			if (head == a) head = b;
			else if (head == b) head = a;
			if (curr == a) curr = b;
			else if (curr == b) curr = a;
			return;
		}	
	}

	int insertionSort(int n, int begin, int gap, LList* order) {
		int moves = 0;

		for (int i = gap; i < n; i += gap) {
			for (int j = i; j >= gap; j -= gap) {
				Node* x = head->next;
				Node* y = head->next;
				for (int c = 0; c < j + begin; ++c) x = x->next;
				for (int c = 0; c < j + begin - gap; ++c) y = y->next;

				if (compare(x, y, order)) {
					swapNodes(x, y, false);
					moves++;
				}
			}
		}

		return moves;
	}

	int shellSort(int n, LList* order) {
		int moves = 0;
		Node* tmp = head;
		for (int i = n / 2; i > 2; i /= 2) {
			for (int j = 0; j < i; ++j) {
				moves += insertionSort(n - j, j, i, order);
			}
		}
		moves += insertionSort(n, 0, 1, order);
		return moves;
	}
	
	int getTotal(bool onlyPositive) const {
		if (cnt == 0) return 0;
		int total = 0;
		Node* tmp = head;
		do {
			total += tmp->energy;
			if (onlyPositive && tmp->energy < 0) total -= tmp->energy; 
			tmp = tmp->next;
		} while (tmp != head && tmp != tail);
		return total;
	}

	void moveToStart() { curr = head; }
	void moveToEnd() { curr = tail; }
	void moveToPtr(Node* ptr) { curr = ptr; }
	void next() { if (curr->next != tail) curr = curr->next; }
	void prev() { if (curr->prev != head) curr = curr->prev; }
	int getLength() const { return cnt; }
	int getLimit() const { return size; }
	bool isFull() const { return (cnt >= size); }

	string getName() const { return curr->next->name; }
	int getEnergy() const {	return curr->next->energy; }
	Node* getCurrent() const { return curr->next; }

	void moveToPtrByName(string name) {
		if (cnt == 0) return;
		Node* tmp = head;
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
		Node* tmp = head;
		while (tmp != tail) {
			if (tmp->next->name == name) return true;
			tmp = tmp->next;
		}
		return false;
	}

	Node* locateMax() const {
		if (cnt == 0) return nullptr;
		Node* ptr = head;
		Node* tmp = head;
		
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
		if (cnt <= 0) return;
		Node* tmp = head;
		while (tmp->next != tail && tmp->next != head) {
			tmp->next->print();
			tmp = tmp->next;
		}
		// cout << '\n';
	}
};

class CLList : public LList {
private:
public:
	CLList(int size) {
		curr = head = nullptr;
		cnt = 0;
		this->size = size;
	}
	~CLList() { 
		removeAll();
	}

	void insert(const string& name, const int& energy) {
		Node* newNode = new Node(name, energy, nullptr, nullptr);

		if (cnt == 0) {
			curr = head = newNode;
			newNode->next = newNode;
			newNode->prev = newNode;
		} else {
			newNode->prev = curr;
			newNode->next = curr->next;
			curr->next->prev = newNode;
			curr->next = newNode;
		}

		cnt++;
	}

	void remove(const int& indicies, LList* Order) {
		if (cnt == 0) return;
		Node* ptr = Order->head->next;
		do {
			Node* pp = ptr->next;
			if (find(ptr->name)) {
				if ((ptr->energy < 0 && indicies < 0) || (ptr->energy > 0 && indicies >= 0)) {
					ptr = pp;
					continue;
				}
				Node* tmp = head;
				for (; tmp->name != ptr->name; tmp = tmp->next);
				Node* del = tmp;
				tmp->prev->next = del->next;
				tmp->next->prev = del->prev;
				cnt--;

				if (del->energy < 0) curr = tmp->prev;
				else curr = tmp->next;
				
				if (head == del) head = tmp->prev;

				del->next = nullptr;
				del->prev = nullptr;
				delete del;
			}
			ptr = pp;
		} while (ptr != Order->tail && cnt > 0 && Order->cnt > 0);
	}


	void removeByName(int n, LList* Order) {
		if (cnt == 0) return;
		Node* ptr = Order->head->next;
		do {
			Node* pp = ptr->next;
			if (find(ptr->name)) {
				Node* tmp = head;
				for (; tmp->name != ptr->name; tmp = tmp->next);
				n--;
				Node* del = tmp;
				tmp->prev->next = del->next;
				tmp->next->prev = del->prev;
				cnt--;

				if (del->energy < 0) curr = tmp->prev;
				else curr = tmp->next;
				if (head == del) head = tmp->prev;

				del->next = nullptr;
				del->prev = nullptr;
				delete del;

				del = ptr;
				ptr->prev->next = del->next;
				ptr->next->prev = del->prev;
				
				del->next = nullptr;
				del->prev = nullptr;
				delete del;
				Order->cnt--;
			}
			ptr = pp;
		} while (ptr != Order->tail && n > 0 && cnt > 0 && Order->cnt > 0);
	}

	void next() { curr = curr->next; }
	void prev() { curr = curr->prev; }

	string getName() const { return (curr ? curr->name : ""); }
	int getEnergy() const {	return (curr ? curr->energy : -inf); }
	
	Node* locateMaxDiff(int& energy) const {
		if (cnt == 0) return nullptr;
		Node* ptr = curr;
		Node* tmp = curr;
		int mx = 0;
		do {
			if (abs(tmp->energy - energy) > mx) {
				mx = abs(tmp->energy - energy);
				ptr = tmp;
			}
			tmp = tmp->next;
		} while (tmp != curr);
		return ptr;
	}

	bool find(string& name) {
		if (cnt == 0) return false;
		Node* tmp = head->next;
		do {
			if (tmp->name == name) return true;
			tmp = tmp->next;
		} while (tmp != head->next);
		return false;
	}

	void reversal() {
		if (cnt <= 1) return;
		Node* tmp = curr;
		Node* a = curr->next;
		Node* b = curr;
		int i = 0;
		int j = cnt - 1;

		while (j > i) {
			while (a->energy > 0 && a != b) a = a->next, i++;
			while (b->energy > 0 && a != b) b = b->prev, j--;
			Node* aa = a->next;
			Node* bb = b->prev;
			if (a->energy < 0 && b->energy < 0) swapNodes(a, b, true);

			if (j <= i) break;
			a = aa; i++;
			b = bb; j--;
		}

		i = 0;
		j = cnt - 1;
		a = curr->next;
		b = curr;
		while (j > i) {
			while (a->energy < 0 && a != b) a = a->next, i++;
			while (b->energy < 0 && a != b) b = b->prev, j--;
			Node* aa = a->next;
			Node* bb = b->prev;
			if (a->energy > 0 && b->energy > 0) swapNodes(a, b, true);

			if (j <= i) break;
			a = aa; i++;
			b = bb; j--;
		}
		
		curr = tmp;
	}

	void findSubarrary() {
		if (cnt < 4) return;

		Node* tmp = curr;
		Node* minStart = nullptr;
		Node* minEnd = nullptr;
		int sum = 0;
		int minSum = inf;
		int minLength = 0;

		do {
			for (int length = 4; length <= cnt; ++length) {
				Node* x = tmp;
				sum = 0;
				int i = 1;
				while (i <= length) {
					sum += x->energy;
					i++;
					x = x->next;
				}
				// cout << length << ' ' << sum << ' ' << tmp->name << ' ' << x->prev->name << '\n';
				if ((sum < minSum) || (sum == minSum && length >= minLength)) {
					minSum = sum;
					minLength = length;
					minStart = tmp;
					minEnd = x;
				}
			}
			
			tmp = tmp->next;
		} while (tmp != curr);

		tmp = minStart;
		int minVal = inf;
		Node* minNode = nullptr;
		do {
			if (tmp->energy < minVal) {
				minVal = tmp->energy;
				minNode = tmp;
			}
			tmp = tmp->next;
		} while (tmp != minEnd);


		tmp = minNode;
		do {
			tmp->print();
			tmp = tmp->next;
		} while (tmp != minEnd);

		if (minNode == minStart) {
			// cout << '\n';
			return;
		}
		
		tmp = minStart;
		do {
			tmp->print();
			tmp = tmp->next;
		} while (tmp != minNode);
		// cout << '\n';
	}

	void printCWise() const {
		if (cnt == 0) return;
		Node* tmp = curr;
		do {
			tmp->print();
			tmp = tmp->next;
		} while (tmp != curr);
		// cout << '\n';
	}

	void printCounterCWise() const {
		if (cnt == 0) return;
		Node* tmp = curr;
		do {
			tmp->print();
			tmp = tmp->prev;
		} while (tmp != curr);
		// cout << '\n';
	}
};

class imp_res : public Restaurant {
private:
	CLList* Table = nullptr;
	LList* Queue = nullptr;
	LList* Order = nullptr;
	bool isQueue = false;
public:	
	imp_res() {};
	~imp_res() {
		Table->removeAll();
		Queue->removeAll();
		Order->removeAll();
	}

	void RED(string name, int energy) {
		if (!Table || !Queue || !Order) {
			Table = new CLList(MAXSIZE);
			Queue = new LList(MAXSIZE);
			Order = new LList(200000);
		}

		if (energy == 0) return;

		if (Table->getLength() == 0 && !Table->isFull()) {
			Table->insert(name, energy);
			if (!isQueue) Order->append(name, energy);
			isQueue = false;
			Table->next();
			return;
		}

		if (Table->find(name) || Queue->find(name)) return;

		if (Table->isFull() && Queue->isFull()) return;

		if (!isQueue) Order->append(name, energy);
		isQueue = false;

		if (Table->isFull()) {
			if (!Queue->isFull()) Queue->append(name, energy);
			return;
		}

		if (Table->getLength() >= Table->getLimit() / 2) {
			Node* pos = Table->locateMaxDiff(energy);
			Table->moveToPtr(pos);
			if (energy - Table->getEnergy() < 0) Table->prev();
			Table->insert(name, energy);
			Table->next();
			return;
		}

		// cout << Table->getName() << ' ' << Table->getEnergy() << " - " << name << ' ' << energy << '\n';

		if (energy < Table->getEnergy()) Table->prev();
		Table->insert(name, energy);
		Table->next();
	}

	void BLUE(int num) {
		if (num <= 0) return;
		if (!Table || Table->getLength() <= 0) return;
		Table->removeByName(num, Order);
		
		if (Queue->getLength() <= 0) return;

		Queue->moveToStart();
		while (Queue->getLength() && !Table->isFull()) {
			string name = Queue->getName();
			int energy = Queue->getEnergy(); 
			Queue->pop();
			isQueue = true;
			RED(name, energy);
		}
	}

	void PURPLE() {
		if (!Table || !Queue || Queue->getLength() <= 0) return;
		Node* tmp = Queue->locateMax();
		Queue->moveToStart();
		int cnt = 1;
		while (Queue->getName() != tmp->name) {
			cnt++; Queue->next();
		}
		int moves = Queue->shellSort(cnt, Order);
		
		// cout << "PURPLE MOVES: " << moves << "\n\n";
		BLUE(moves % MAXSIZE);
	}

	void REVERSAL()	{
		if (!Table || Table->getLength() <= 0) return;
		Table->reversal();
	}

	void UNLIMITED_VOID() {
		if (!Table || Table->getLength() < 4) return;
		Table->findSubarrary();
	}

	void DOMAIN_EXPANSION()	{
		if (!Table || Table->getLength() <= 0) return;
		
		// int total1 = abs(Table->getTotal(true)) + abs(Queue->getTotal(true));
		// int total2 = abs(Table->getTotal(false) + Queue->getTotal(false));
		// int total = total1 - total2;

		int total = Table->getTotal(false) + Queue->getTotal(false);

		Table->remove(total, Order);
		Queue->remove(total, Order);
		Order->removeByOrder(total);

		if (Queue->getLength() <= 0) return;
		
		Queue->moveToStart();
		while (Queue->getLength() && !Table->isFull()) {
			string name = Queue->getName();
			int energy = Queue->getEnergy(); 
			Queue->pop();
			isQueue = true;
			RED(name, energy);
		}
	}

	void LIGHT(int num)	{
		if (!Table || Table->getLength() <= 0) return;
		if (num > 0) Table->printCWise();
		if (num < 0) Table->printCounterCWise();
		if (num == 0) Queue->print();
	}

	void ORDER() {
		Order->print();
	}
};