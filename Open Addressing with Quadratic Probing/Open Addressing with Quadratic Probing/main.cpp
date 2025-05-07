#include <iostream>
using namespace std;

const int TABLE_SIZE = 10;

class HashTable {
private:
    int* table;
    bool* occupied;

public:
    HashTable() {
        table = new int[TABLE_SIZE];
        occupied = new bool[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = -1;
            occupied[i] = false;
        }
    }

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

    void insert(int key) {
        int index = hashFunction(key);
        int i = 0;
        int newIndex;

        while (i < TABLE_SIZE) {
            newIndex = (index + i * i) % TABLE_SIZE;
            if (!occupied[newIndex]) {
                table[newIndex] = key;
                occupied[newIndex] = true;
                cout << "Inserted " << key << " at index " << newIndex << endl;
                return;
            }
            i++;
        }

        cout << "Hash Table is full! Cannot insert " << key << endl;
    }

    bool search(int key) {
        int index = hashFunction(key);
        int i = 0;
        int newIndex;

        while (i < TABLE_SIZE) {
            newIndex = (index + i * i) % TABLE_SIZE;
            if (!occupied[newIndex]) {
                return false;
            }
            if (table[newIndex] == key) {
                return true;
            }
            i++;
        }

        return false;
    }

    void remove(int key) {
        int index = hashFunction(key);
        int i = 0;
        int newIndex;

        while (i < TABLE_SIZE) {
            newIndex = (index + i * i) % TABLE_SIZE;
            if (!occupied[newIndex]) {
                break;
            }
            if (table[newIndex] == key) {
                table[newIndex] = -1;
                occupied[newIndex] = false;
                cout << "Removed " << key << " from index " << newIndex << endl;
                return;
            }
            i++;
        }

        cout << "Key " << key << " not found." << endl;
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << ": ";
            if (occupied[i])
                cout << table[i];
            else
                cout << "Empty";
            cout << endl;
        }
    }

    ~HashTable() {
        delete[] table;
        delete[] occupied;
    }
};

int main() {
    HashTable ht;

    ht.insert(10);
    ht.insert(20);
    ht.insert(30);
    ht.insert(25);
    ht.display();

    cout << "\nSearching for 25: " << (ht.search(25) ? "Found" : "Not Found") << endl;
    cout << "Searching for 99: " << (ht.search(99) ? "Found" : "Not Found") << endl;

    ht.remove(20);
    ht.display();

    return 0;
}
