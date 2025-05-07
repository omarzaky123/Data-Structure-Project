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
            table[i] = -1;         // Use -1 to indicate empty slot
            occupied[i] = false;   // Slot is not occupied
        }
    }

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

    void insert(int key) {
        int index = hashFunction(key);
        int originalIndex = index;

        while (occupied[index]) {
            index = (index + 1) % TABLE_SIZE;
            if (index == originalIndex) {
                cout << "Hash Table is full!" << endl;
                return;
            }
        }

        table[index] = key;
        occupied[index] = true;
        cout << "Inserted " << key << " at index " << index << endl;
    }

    bool search(int key) {
        int index = hashFunction(key);
        int originalIndex = index;

        while (occupied[index]) {
            if (table[index] == key)
                return true;
            index = (index + 1) % TABLE_SIZE;
            if (index == originalIndex)
                break;
        }
        return false;
    }

    void remove(int key) {
        int index = hashFunction(key);
        int originalIndex = index;

        while (occupied[index]) {
            if (table[index] == key) {
                table[index] = -1;
                occupied[index] = false;
                cout << "Removed " << key << " from index " << index << endl;
                return;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == originalIndex)
                break;
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

    ht.insert(5);
    ht.insert(15);
    ht.insert(25);
    ht.display();

    cout << "\nSearching for 15: " << (ht.search(15) ? "Found" : "Not Found") << endl;
    cout << "Searching for 100: " << (ht.search(100) ? "Found" : "Not Found") << endl;

    ht.remove(15);
    ht.display();

    return 0;
}
