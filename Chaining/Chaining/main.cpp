#include <iostream>
#include <list>
#include <algorithm> // ✅ Required for std::find
using namespace std;

const int TABLE_SIZE = 10;

class HashTable {
private:
    list<int>* table;

public:
    HashTable() {
        table = new list<int>[TABLE_SIZE];
    }

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

    void insert(int key) {
        int index = hashFunction(key);
        table[index].push_back(key);
        cout << "Inserted " << key << " at index " << index << " (chained)" << endl;
    }

    bool search(int key) {
        int index = hashFunction(key);
        for (int val : table[index]) {
            if (val == key)
                return true;
        }
        return false;
    }

    void remove(int key) {
        int index = hashFunction(key);
        auto& chain = table[index];
        auto it = find(chain.begin(), chain.end(), key);
        if (it != chain.end()) {
            chain.erase(it);
            cout << "Removed " << key << " from index " << index << endl;
        } else {
            cout << "Key " << key << " not found." << endl;
        }
    }

    void display() {
        cout << "Hash Table:\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << ": ";
            for (int val : table[i])
                cout << val << " -> ";
            cout << "NULL\n";
        }
    }

    ~HashTable() {
        delete[] table;
    }
};

int main() {
    HashTable ht;

    ht.insert(10);
    ht.insert(20);
    ht.insert(30);
    ht.insert(25);  // Will chain at the same index as 25 % 10 = 5
    ht.insert(35);  // Will chain if same index

    ht.display();

    cout << "\nSearching for 25: " << (ht.search(25) ? "Found" : "Not Found") << endl;
    cout << "Searching for 99: " << (ht.search(99) ? "Found" : "Not Found") << endl;

    ht.remove(25);
    ht.display();

    return 0;
}
