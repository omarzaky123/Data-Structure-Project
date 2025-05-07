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

        if (!occupied[index]) {
            // Empty home slot
            table[index] = key;
            occupied[index] = true;
            cout << "Inserted " << key << " at index " << index << endl;
            return;
        }

        // Replacement condition: existing key is not at its home
        int existingKey = table[index];
        int existingKeyHome = hashFunction(existingKey);

        if (existingKeyHome != index) {
            // Replace the existing key with the new key
            cout << "Replacing " << existingKey << " with " << key << " at index " << index << endl;
            table[index] = key;
            key = existingKey; // Reinsert the displaced key
        }

        // Now insert the displaced key (or original if not replaced) using quadratic probing
        for (int i = 1; i < TABLE_SIZE; i++) {
            int newIndex = (index + i * i) % TABLE_SIZE;
            if (!occupied[newIndex]) {
                table[newIndex] = key;
                occupied[newIndex] = true;
                cout << "Inserted " << key << " at index " << newIndex << " using probing" << endl;
                return;
            }
        }

        cout << "Hash table is full! Couldn't insert " << key << endl;
    }

    bool search(int key) {
        int index = hashFunction(key);
        for (int i = 0; i < TABLE_SIZE; i++) {
            int newIndex = (index + i * i) % TABLE_SIZE;
            if (!occupied[newIndex])
                return false;
            if (table[newIndex] == key)
                return true;
        }
        return false;
    }

    void remove(int key) {
        int index = hashFunction(key);
        for (int i = 0; i < TABLE_SIZE; i++) {
            int newIndex = (index + i * i) % TABLE_SIZE;
            if (!occupied[newIndex])
                break;
            if (table[newIndex] == key) {
                table[newIndex] = -1;
                occupied[newIndex] = false;
                cout << "Removed " << key << " from index " << newIndex << endl;
                return;
            }
        }
        cout << "Key " << key << " not found." << endl;
    }

    void display() {
        cout << "Hash Table:\n";
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
    ht.insert(21); // Causes replacement
    ht.insert(31); // More probing

    ht.display();

    cout << "\nSearching for 21: " << (ht.search(21) ? "Found" : "Not Found") << endl;
    cout << "Searching for 99: " << (ht.search(99) ? "Found" : "Not Found") << endl;

    ht.remove(20);
    ht.display();

    return 0;
}
