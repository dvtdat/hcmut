#include "main.h"

typedef pair<int, char> ic;
typedef pair<int, int> ii;

template <typename E>
class HuffNode {
public:
    virtual ~HuffNode() {}
    virtual int weight() const = 0;
    virtual bool isLeaf() const = 0;
};

template <typename E>
class LeafNode : public HuffNode<E> {
private:
    E it;
    int wgt;

public:
    LeafNode(const E& val, int freq) { it = val; wgt = freq; }
    int weight() const override { return wgt; }
    E val() const { return it; }
    bool isLeaf() const override { return true; }
};

template <typename E>
class InternalNode : public HuffNode<E> {
private:
    HuffNode<E>* lc;
    HuffNode<E>* rc;
    int wgt;

public:
    InternalNode(HuffNode<E>* l, HuffNode<E>* r): lc(l), rc(r) {
        wgt = l->weight() + r->weight();
    }
    int weight() const override { return wgt; }
    bool isLeaf() const override { return false; }
    HuffNode<E>* left() const { return lc; }
    HuffNode<E>* right() const { return rc; }
    void setLeft(HuffNode<E>* b) { lc = b; }
    void setRight(HuffNode<E>* b) { rc = b; }
};

template <typename E>
class HuffTree {
private:
    HuffNode<E>* Root;

public:
    HuffTree(E& val, int freq) {
        Root = new LeafNode<E>(val, freq);
    }
    
    HuffTree(HuffTree<E>* l, HuffTree<E>* r) {
        Root = new InternalNode<E>(l->root(), r->root());
    }

    ~HuffTree() {}
    HuffNode<E>* root() { return Root; }
    int weight() { return Root->weight(); }
};

template <typename E>
HuffTree<E>* buildHuffmanTree(HuffTree<E>** TreeArray, int count) {
    priority_queue<HuffTree<E>*> forest(TreeArray, TreeArray + count);
    HuffTree<E> *temp1, *temp2, *temp3 = nullptr;
    
    while (forest.size() > 1) {
        temp1 = forest.top();
        forest.pop();
        
        temp2 = forest.top();
        forest.pop();
        
        temp3 = new HuffTree<E>(temp1, temp2);
        forest.push(temp3);
    }
    
    return temp3;
}

void lapse(string name) {
    auto calculateCharacterFrequencies = [](const string &inputString) -> vector<ic> {
        vector<ic> frequencyList;
        for (char character : inputString) {
            auto it = find_if(frequencyList.begin(), frequencyList.end(), [character](const ic &element) {
                return element.second == character;
            });

            if (it != frequencyList.end()) {
                it->first--;
            } else {
                frequencyList.push_back(ic(-1, character));
            }
        }

        sort(frequencyList.begin(), frequencyList.end());
        for (ic &character : frequencyList) character.first = -character.first;
        return frequencyList;
    };

    auto ceasarCiperCharacter = [](vector<ic> &frequencyList) {
        for (ic &character : frequencyList) {
            if (islower(character.second)) {
                character.second = 'a' + (character.second - 'a' + character.first) % 26;
            } else if (isupper(character.second)) {
                character.second = 'A' + (character.second - 'A' + character.first) % 26;
            }
        }
    };

    auto isFrequencyListValid = [](vector<ic> &frequencyList) -> bool {
        return frequencyList.size() > 2;
    };

    auto printFrequencyList = [](vector<ic> &frequencyList) {
        for (ic character : frequencyList) {
            cout << character.second << ": " << character.first << '\n';
        }
    };

    vector<ic> frequencyList = calculateCharacterFrequencies(name);
    ceasarCiperCharacter(frequencyList);

    
    HuffTree<char>* customerHufftree; // = buildHuffmanTree(vector<ic> frequencyList)
    bool isCustomerValid; // = isHuffmanTreeValid(Hufftree<E>* customerHufftree) || isFrequencyListValid(vector<ic> frequencyList)

    if (!isCustomerValid) {
        // if not valid then exit
    }

    int customerCode; // = getHuffmanCode(Hufftree<E>* customerHufftree)

    if (customerCode & 1) {
        // go to restaurant G
        // go in slot ID = customerCode % MAXSIZE + 1
        // add customer by customerCode the BST corresponding to that slot
    } else {
        // go to restaurant S
        // heap?
    }
}

void kokusen() {
    // apply to restaurant G
    // count valid permutation
}

void keitenken(string name) {

}

void hand() {

}

void limitless() {

}

void cleave() {

}

void simulate(string filename)
{
    ifstream ss(filename);
    string str;
    while (ss >> str) {
        cout << "hello\n";
        if (str == "LAPSE") {
            string name; ss >> name;
            lapse(name);
        } else if (str == "KOKUSEN") {
            kokusen();
        } else if (str == "KEITENKEN") {
            string name; ss >> name;
            keitenken(name);
        } else if (str == "HAND") {
            hand();
        } else if (str == "LIMITLESS") {
            limitless();
        } else if (str == "CLEAVE") {
            cleave();
        } 
    }
    return;
}