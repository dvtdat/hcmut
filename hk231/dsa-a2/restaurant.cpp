#include "main.h"

using ii = pair<int, int>;
template<typename T> using sptr = shared_ptr<T>;
#define debug(X) { auto _X = (X); std::cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << std::endl; }

const int INF = 1e9 + 7;

int MAXSIZE;

class Name {
private:
    vector<int> frequencyList;
    vector<int> characterList;
    vector<int> firstAppear;
    vector<int> compress;
    int result = 0;
public:
    Name() = default;
    Name(string s) {
        frequencyList.assign(500, 0);
        firstAppear.assign(500, 0);
        vector<int> cnt(500, 0);

        for (char c : s) {
            if (!cnt[c]) compress.push_back(c);
            cnt[c]++;
        }

        if ((int)compress.size() < 3) return;
        
        result = 1;

        for (int i : compress) {
            if (!frequencyList[encode(i, cnt)]) characterList.push_back(encode(i, cnt));
            frequencyList[encode(i, cnt)] += cnt[i];
        }

        for (auto &x : s) {
            x = encode(x, cnt);
        }
        compress.clear();
        compress.assign(s.begin(), s.end());

        sort(characterList.begin(), characterList.end(), [&] (int x, int y) {
            if (frequencyList[x] == frequencyList[y]) {
                if ((x >= 'a' && x <= 'z' && y >= 'a' && y <= 'z') || (x >= 'A' && x <= 'Z' && y >= 'A' && y <= 'Z')) return x < y;
                else return x > y;
            }
            return frequencyList[x] < frequencyList[y];
        });

        for (int i = 0; i < (int)characterList.size(); ++i) {
            firstAppear[characterList[i]] = i;
        }
    }

    char encode(char x, vector<int> cnt) {
        char tmp = x;
        
        if (x >= 'a' && x <= 'z') x -= 'a';
        else x -= 'A';

        x += cnt[tmp]; x %= 26;
        if (tmp >= 'a' && tmp <= 'z') x += 'a';
        else x += 'A';
        
        return x;
    }

    vector<int> getCharacterList() {
        return characterList;
    }

    vector<int> getFrequencyList() {
        return frequencyList;
    }

    vector<int> getFirstAppear() {
        return firstAppear;
    }

    vector<int> getCompress() {
        return compress;
    }

    int getResult() {
        return result;
    }

    bool isValid() {
        return result != 0;
    }

};

class HuffTree {
private:
    class HuffTreeNode {
    public:
        char key;
        int frequency, firstAppear, height;
        sptr<HuffTreeNode> left, right;

        HuffTreeNode(char key, int freq, int firstAppear): 
            key(key), frequency(freq), firstAppear(firstAppear), height(0), left(nullptr), right(nullptr) {};

        HuffTreeNode(char key, int freq, int firstAppear, int height, sptr<HuffTreeNode> left, sptr<HuffTreeNode> right): 
            key(key), frequency(freq), firstAppear(firstAppear), height(height), left(left), right(right) {};      
    };

    struct comparator {
        bool operator () (sptr<HuffTreeNode> left, sptr<HuffTreeNode> right) {
            if (left->frequency == right->frequency) return left->firstAppear > right->firstAppear;
            else return left->frequency > right->frequency;
        }
    };

    vector<int> characterList;
    vector<int> frequencyList;
    vector<int> firstAppear;
    sptr<HuffTreeNode> root;
    unordered_map<char, string> huffmanCode;

    void rightRotation(sptr<HuffTreeNode> &A) {
        sptr<HuffTreeNode> B = A->left;
        A->left = B->right;
        B->right = A;

        A->height = 1 + max(getDepth(A->left), getDepth(A->right));
        B->height = 1 + max(getDepth(B->left), getDepth(B->right));
        A = B;
    }

    void leftRotation(sptr<HuffTreeNode> &A) {
        sptr<HuffTreeNode> B = A->right;
        A->right = B->left;
        B->left = A;

        A->height = 1 + max(getDepth(A->left), getDepth(A->right));
        B->height = 1 + max(getDepth(B->left), getDepth(B->right));
        A = B;
    }

public:
    int treeSize;
    HuffTree() = default;

    HuffTree(vector<int> characterList, vector<int> frequencyList, vector<int> firstAppear) :
        characterList(characterList), frequencyList(frequencyList), firstAppear(firstAppear)
    {
        priority_queue<shared_ptr<HuffTreeNode>, vector<shared_ptr<HuffTreeNode>>, comparator> pq;
        for (auto x : characterList) {
            pq.push(make_shared<HuffTreeNode>(x, frequencyList[x], firstAppear[x]));
        }

        int counter = (int)characterList.size() - 1;

        while (pq.size() != 1) {
            sptr<HuffTreeNode> left = pq.top(); pq.pop();
            sptr<HuffTreeNode> right = pq.top(); pq.pop();

            int sum = left->frequency + right->frequency;
            counter++;

            int hi = 1 + max(getDepth(left), getDepth(right));
            sptr<HuffTreeNode> newRoot(new HuffTreeNode('.', sum, counter, hi, left, right));

            balance(newRoot);
            pq.push(newRoot);
        }

        root = pq.top();
        treeSize = getSize(root);

        encode(root, "", huffmanCode);
    }

    void balance(sptr<HuffTreeNode> &root) {
        for (int attempt = 0; attempt < 3; ++attempt) {
            bool isRoot = false;
            auto tmp = findFistUnbalancedNode(root);
            bool flag = false;

            isRoot = (tmp == root);
            if (!tmp) break;

            int balanceFactor = getBalanceFactor(tmp);
            if (balanceFactor > 1) {
                flag = true;
                if (getBalanceFactor(tmp->left) >= 0) {
                    rightRotation(tmp);
                    if (isRoot) root = tmp;
                } else {
                    auto nextTmp = tmp->left->right;
                    leftRotation(tmp->left);
                    if (++attempt == 3) break;
                    rightRotation(tmp);
                    if (isRoot) root = nextTmp;
                }
            } else if (balanceFactor < -1) {
                flag = true;
                if (getBalanceFactor(tmp->right) <= 0) {
                    leftRotation(tmp);
                    if (isRoot) root = tmp;
                } else {
                    auto nextTmp = tmp->right->left;
                    rightRotation(tmp->right);
                    if (++attempt == 3) break;
                    leftRotation(tmp);
                    if (isRoot) root = nextTmp;
                }
            }
        }
    }

    void printTree() {
        printTree(root);
    }

    int getSize(sptr<HuffTreeNode> root) {
        if (!root) return 0;
        return 1 + getSize(root->left) + getSize(root->right);
    }

    int getDepth(sptr<HuffTreeNode> root) {
        if (!root) return 0;
        return root->height;
    }

    int getBalanceFactor(sptr<HuffTreeNode> root) {
        if (!root) return 0;
        return getDepth(root->left) - getDepth(root->right);
    }

    sptr<HuffTreeNode> findFistUnbalancedNode(sptr<HuffTreeNode> root) {
        if (!root) return nullptr;

        int balanceFactor = getBalanceFactor(root);
        if (balanceFactor < -1 || balanceFactor > 1) return root;
        sptr<HuffTreeNode> leftNode = findFistUnbalancedNode(root->left);
        sptr<HuffTreeNode> rightNode = findFistUnbalancedNode(root->right);
        
        if (leftNode && (getBalanceFactor(leftNode) < -1 || getBalanceFactor(rightNode) > 1))	return leftNode;
        if (rightNode && (getBalanceFactor(rightNode) < -1 || getBalanceFactor(rightNode) > 1))	return rightNode;
        return nullptr;
    }

    void printTree(sptr<HuffTreeNode> root) {
        if (!root) return;
        if (!root->left && !root->right) {
            cout << root->key;
            return;
        }
        cout << root->key << "(";
        printTree(root->left);
        cout << ", ";
        printTree(root->right);
        cout << ")";
    }

    void encode(sptr<HuffTreeNode> root, string str, unordered_map<char, string> &huffmanCode) {
        if (treeSize == 1)	{
            huffmanCode[root->key] = "0";
            return;
        }
        if (root == nullptr) return;
        if (root -> key != '.') {
            huffmanCode[root->key] = str;
        }
        encode(root->left, str + "0", huffmanCode);
        encode(root->right, str + "1", huffmanCode);
	}

    unsigned long long getResult(Name name) {
        if (getSize(root) == 1) return 0;
        
        vector<int> list(name.getCompress());

        string result = "";
        for (auto i : list) result += huffmanCode[i];

        int endIdx = (int)result.size();
        int startIdx = max(0, endIdx - 10);

        string tmp(result, startIdx, endIdx - startIdx);
        reverse(tmp.begin(), tmp.end());

        bitset<20> bit(tmp);
        return bit.to_ulong();
    }

    void printInOrder(sptr<HuffTreeNode> root) {
        if (!root) return;

        printInOrder(root->left);
        if (!root->left && !root->right) cout << root->key << '\n';
        else cout << root->frequency << '\n';
        printInOrder(root->right);
    }

    void printInOrder() {
        printInOrder(root);
    }
};

class Customer {
private:
    Name name;
    sptr<HuffTree> huffTree;
    unsigned long long result;
public:
    Customer() = default;
    Customer(Name name): name(name) {
        huffTree = make_shared<HuffTree>(name.getCharacterList(), name.getFrequencyList(), name.getFirstAppear());
        result = huffTree->getResult(name);
    }

    Customer(const Customer& newCustomer) {
        this->name = newCustomer.name;
        this->huffTree = newCustomer.huffTree;
        this->result = newCustomer.result;
    }

    void printTree() {
        huffTree->printTree();
    }

    Name getName() {
        return name;
    }

    unsigned long long getResult() {
        return result;
    }

    int getID() {
        return (result % MAXSIZE + 1);
    }

    void printInOrder() {
        huffTree->printInOrder();
    }
};

class BSTree {
private:
    class BSTNode {
    public:
        unsigned long long value;
        sptr<BSTNode> left;
        sptr<BSTNode> right;

        BSTNode(): left(nullptr), right(nullptr) {};
        BSTNode(unsigned long long value, sptr<BSTNode> left = nullptr, sptr<BSTNode> right = nullptr): value(value), left(left), right(right) {};
    };

    sptr<BSTNode> root;
    vector<int> inputOrder;
    vector<vector<long long>> table;
    
    void insert(sptr<BSTNode>& root, unsigned long long value) {
        if (!root) {
            root = make_shared<BSTNode>(value, nullptr, nullptr);
            return;
        }
        if (value < root->value) insert(root->left, value);
        else insert(root->right, value);
    }

    sptr<BSTNode> getMin(sptr<BSTNode> root) {
        if (!root->left) return root;
        return getMin(root->left);
    }

    sptr<BSTNode> remove(sptr<BSTNode> root, unsigned long long value) {
        if (!root) return nullptr;
        else if (value < root->value) root->left = remove(root->left, value);
        else if (value > root->value) root->right = remove(root->right, value);
        else {
            sptr<BSTNode> tmp = root;
            if (!root->left) {
                root = root->right;
            } else if (!root->right) {
                root = root->left;
            } else {
                sptr<BSTNode> mn = getMin(root->right);
                root->value = mn->value;
                root->right = remove(root->right, mn->value);
            }
        }
        
        return root;
    }

    void fact(vector<unsigned long long>& f) {
        if (f.empty()) return;
        f[0] = 1ULL;
        for (int i = 1; i < (int)f.size(); ++i) {
            f[i] = f[i - 1] * 1ULL * i;
        }
    }

    long long dfs(vector<int> &nums){
        if (nums.size() < 3) return 1;
        int m = nums.size();

        vector<int> leftNodes, rightNodes;
        for(int i = 1; i < m; ++i){
            if (nums[i] <= nums[0]) {
                leftNodes.push_back(nums[i]);
            } else {
                rightNodes.push_back(nums[i]);
            }
        }
		
        long long left = dfs(leftNodes) % MAXSIZE;
        long long right = dfs(rightNodes) % MAXSIZE;

        return (((left * right) % MAXSIZE) * table[m - 1][leftNodes.size()]) % MAXSIZE;
    }

public:
    BSTree(): root(nullptr) {}

    unsigned long long getPermutation() {
        vector<int> preorder;
        getPreOrder(root, preorder);

        int m = preorder.size();
        table.resize(m + 1);

        for (int i = 0; i < m + 1; ++i) {
            table[i] = vector<long long>(i + 1, 1);
            for (int j = 1; j < i; ++j) {
                table[i][j] = (table[i - 1][j - 1] + table[i - 1][j]) % MAXSIZE;
            }
        }

        return dfs(preorder) % MAXSIZE;
    }

    bool isEmpty() {
        return (root == nullptr);
    }

    void printTree(sptr<BSTNode> root) {
        if (!root) return;
        cout << root->value;

        if (root->left || root->right) {
            cout << " (";
            if (root->left) printTree(root->left);
            else cout << "null";
            cout << ", ";
            if (root->right) printTree(root->right);
            else cout << "null";
            cout << ")";
        }
    }

    void getPreOrder(sptr<BSTNode>& root, vector<int>& preorder) {
        if (!root) return;
        preorder.push_back(root->value);
        getPreOrder(root->left, preorder);
        getPreOrder(root->right, preorder);
    }

    void printInOrder(sptr<BSTNode>& root) {
        if (!root) return;
        printInOrder(root->left);
        cout << root->value << '\n';
        printInOrder(root->right);
    }
    
    void addCustomer(Customer customer) {
        inputOrder.push_back(customer.getResult());
        insert(root, customer.getResult());
    }

    void addCustomer(int result) {
        inputOrder.push_back(result);
        insert(root, result);
    }

    void remove(int quantity) {
        if (isEmpty()) return;
        for (int i = 0; i < quantity && !isEmpty() && i < (int)inputOrder.size(); ++i) {
            root = remove(root, inputOrder[i]);
        }

        if (quantity > (int)inputOrder.size()) inputOrder.clear();
        else inputOrder = vector<int>(inputOrder.begin() + quantity, inputOrder.end());
    }

    void printTree() {
        printTree(root);
        cout << '\n';
    }

    void printInOrder() {
        printInOrder(root);
    }

    vector<int> getInputOrder() {
        return inputOrder;
    }
};

class Heap {
private:
    class Area {
    private:
        int size;
        int capacity;
        deque<Customer> customer;
        int turn;
        int label;
        int add;

    public:
        Area(): size(INF), capacity(MAXSIZE), customer(deque<Customer>()), turn(-1), label(-1), add(-1) {}

        void addCustomer(Customer newCustomer) {
            turn = ++Heap::time;
            customer.push_back(newCustomer);

            if (size == INF) size = 1;
            else size++;
        }

        void removeCustomer(int id, int num) {
            turn = ++Heap::time;
            for (int i = 0; i < num && (int)customer.size(); ++i) {
                cout << customer.front().getResult() << '-' << id << '\n';
                size--;
                customer.pop_front();
            }
        }

        void printCustomerLIFO(int id, int num) {
            deque<Customer> tmp = customer;

            for (int i = 0; i < num && (int)tmp.size(); ++i) {
                cout << id << '-' << tmp.back().getResult() << '\n';
                tmp.pop_back();
            }
        }

        void printCustomerFIFO(int id, int num) {
            deque<Customer> tmp = customer;

            for (int i = 0; i < num && (int)tmp.size(); ++i) {
                cout << tmp.front().getResult() << '-' << id << '\n';
                tmp.pop_front();
            }
        }

        Customer latestCustomer() {
            return customer.back();
        }

        Customer earliestCustomer() {
            return customer.front();
        }

        int getTurn() {
            return turn;
        }

        int getLabel() {
            return label;
        }

        int getSize() {
            return size;
        }

        bool isAdd() {
            return (add != -1);
        }

        int getAdd() {
            return add;
        }

        void setAdd(int i) {
            add = i;
        }

        void setLabel(int i) {
            label = i;
        }
    };

    vector<sptr<Area>> heap;
    int size;
    int capacity;
    static int time;
    static int add;

public:
    Heap(): size(0), capacity(MAXSIZE) {
        heap = vector<sptr<Area>>();
    }

    bool compare(sptr<Area> A, sptr<Area> B) {
        if (A->getSize() == B->getSize()) {
            return (A->getTurn() < B->getTurn());
        } else return (A->getSize() < B->getSize());
    }

    void reheapUp(int position) {
        // debug(position);
        if (position <= 0 || position >= capacity) return;
        int parent = (position - 1) / 2;

        if (compare(heap[position], heap[parent])) {
            swap(heap[parent], heap[position]);
            reheapUp(parent);
        }
    }

    void reheapDown(int position) {
        if (position < 0 || position > (int)heap.size() / 2) return;
        int smallest = -1;
        
        // debug(heap[2 * position + 1]->getSize());
        // debug(heap[2 * position + 2]->getSize());

        if (2 * position + 1 < (int)heap.size()) {
            if (2 * position + 2 < (int)heap.size()) {
                if (compare(heap[2 * position + 1], heap[2 * position + 2])) smallest = 2 * position + 1;
                else smallest = 2 * position + 2; 
            } else smallest = 2 * position + 1;
        } else return;


        if (compare(heap[smallest], heap[position])) {
            swap(heap[position], heap[smallest]);
            reheapDown(smallest);
        }
    }

    void addCustomer(Customer customer) {
        if (customer.getID() <= 0 || customer.getID() >= capacity) return;

        int index = -1;
        for (int i = 0; i < (int)heap.size(); ++i) {
            if (customer.getID() == heap[i]->getLabel()) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            heap.push_back(make_shared<Area>());
            heap.back()->setLabel(customer.getID());
            index = heap.size() - 1;

            heap[index]->setAdd(++Heap::add);
            heap[index]->addCustomer(customer);
            reheapUp(index );
        } else {
            heap[index]->addCustomer(customer);
            reheapDown(index);
            reheapUp(index);
        }
    }

    int getMin(vector<int>& idx) {
        int index = -1;
        int mnSize = INF;
        int mnTurn = INF;

        for (int j = 0; j < (int)heap.size(); ++j) {
            if (find(idx.begin(), idx.end(), j) != idx.end()) continue;

            if (mnSize > heap[j]->getSize()) {
                mnSize = heap[j]->getSize();
                mnTurn = heap[j]->getTurn();
                index = j;
            } else if (mnSize == heap[j]->getSize() && mnTurn > heap[j]->getTurn()) {
                mnTurn = heap[j]->getTurn();
                index = j;
            }
        }

        return index;
    }

    void removeRootArea() {
        if ((int)heap.size() < 1) return;

        swap(heap[0], heap[heap.size() - 1]);
        heap.erase(heap.begin() + (heap.size() - 1));
        size--;
        reheapDown(0);
    }

    void removeCustomer(int num) {
        if (heap.empty()) return;

        vector<int> idx;
        vector<sptr<Area>> ptr;
        for (int i = 0; i < num; ++i) {
            idx.push_back(getMin(idx));
            ptr.push_back(heap[idx.back()]);
        }
        
        for (sptr<Area> area : ptr) {
            int i;
            for (i = 0; i < (int)heap.size(); ++i) {
                if (heap[i] == area) break;
            }

            heap[i]->removeCustomer(heap[i]->getLabel(), num);
            reheapUp(i);
            if (heap[i]->getSize() == 0) removeRootArea();
        }
    }
    
    void printPreOrder(int num, int position) {
        if (position < 0 || position >= (int)heap.size()) return;
        heap[position]->printCustomerLIFO(heap[position]->getLabel(), num);
        printPreOrder(num, position * 2 + 1);
        printPreOrder(num, position * 2 + 2);
    }

    void printHeap() {
        debug(heap.size());
        for (int i = 0; i < (int)heap.size(); ++i) {
            debug(heap[i]->getLabel());
            // cout << i << ' ' << heap[i]->getLabel() << ' ' << heap[i]->getSize() << ' ' << heap[i]->getTurn() << '\n';
        }
    }

    void printPreOrder(int num) {
        // printHeap();
        printPreOrder(num, 0);
    }
};

int Heap::time = 0;
int Heap::add = 0;

class Simulate {
private:
    vector<Customer> customerList;
    vector<BSTree> GojoRestaurant;
    Heap SukanaRestaurant;
    sptr<Customer> latestCustomer;
public:
    Simulate() {
        latestCustomer = nullptr;
        for (int i = 0; i < MAXSIZE; ++i) GojoRestaurant.push_back(BSTree());
    }

    void lapse(string name) {
        Name customerName(name);
        if ((int)customerName.getCharacterList().size() < 3) return;
        Customer customer(customerName);
        latestCustomer = make_shared<Customer>(customer);

        debug(customer.getResult());
        debug(customer.getID());
        customer.printTree();

        if (customer.getResult() & 1) {
            GojoRestaurant[customer.getID()].addCustomer(customer);
        } else {
            SukanaRestaurant.addCustomer(customer);
        }
    }

    void kokusen() {
        for (BSTree area : GojoRestaurant) {
            if (area.isEmpty()) continue;
            unsigned long long permutationResult = area.getPermutation();
            debug(permutationResult);
            area.printTree();
            area.remove((int)min(permutationResult, (unsigned long long)MAXSIZE));
            area.printTree();
        }
    }

    void keiteiken(int num) {
        SukanaRestaurant.removeCustomer(num);
    }

    void hand() {
        if (!latestCustomer) return;
        latestCustomer->printInOrder();
    }

    void limitless(int num) {
        GojoRestaurant[num].printInOrder();
    }

    void cleave(int num) {
        SukanaRestaurant.printPreOrder(num);
    }

    void test() {
        // cout << "You're as beautiful as the day I lost you\n";
        SukanaRestaurant.printHeap();
    }
};


void simulate(string filename)
{
    ifstream ss(filename);
    string str;

    ss >> str;
    ss >> MAXSIZE;

    Simulate simulation;

    while (ss >> str) {
        if (str == "LAPSE") {
            string name; ss >> name;
            simulation.lapse(name);
        } else if (str == "KOKUSEN") {
            simulation.kokusen();
        } else if (str == "KEITEIKEN") {
            int num; ss >> num;
            simulation.keiteiken(num);
        } else if (str == "HAND") {
            simulation.hand();
        } else if (str == "LIMITLESS") {
            int num; ss >> num;
            simulation.limitless(num);
        } else if (str == "CLEAVE") {
            int num; ss >> num;
            simulation.cleave(num);
        } else if (str == "TEST") {
            simulation.test();
        }
    }
    return;
}