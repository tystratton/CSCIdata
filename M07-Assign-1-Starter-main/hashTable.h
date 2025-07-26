/* Program name: hashTable.h
Author: Ty Stratton
Date last updated: 7/17/2025
Purpose: Time Program Module 7 Assignment 1, learning Hash Tables*/

#ifndef H_HASHTABLE
#define H_HASHTABLE

#include <iostream>
#include <vector>
#include <list>

// ===== Version 1: Quadratic Probing =====

enum class EntryType { EMPTY, ACTIVE };

class HashTableQuadratic {
public:
    explicit HashTableQuadratic(int size = 100003) : tableSize(size) {
        table.resize(tableSize);
        collisionCount = 0;
    }

    void insert(int item) {
        int hashVal = hash(item);
        int i = 0;
        int currentPos = hashVal;

        bool collision = false;
        while (i < tableSize) {
            if (table[currentPos].info != EntryType::ACTIVE) {
                table[currentPos].element = item;
                table[currentPos].info = EntryType::ACTIVE;
                if (collision) {
                    collisionCount++;
                }
                return;
            }
            if (!collision) {
                collision = true;
            }
            i++;
            currentPos = (hashVal + i * i) % tableSize;
        }
    }

    bool search(int item) {
        int hashVal = hash(item);
        int i = 0;

        while (i < tableSize) {
            int currentPos = (hashVal + i * i) % tableSize;
            const auto& entry = table[currentPos];

            if (entry.info == EntryType::EMPTY) {
                return false;
            }
            if (entry.info == EntryType::ACTIVE && entry.element == item) {
                return true;
            }
            i++;
        }
        return false;
    }
    
    int getCollisions() const {
        return collisionCount;
    }

private:
    struct HashEntry {
        int element;
        EntryType info;
        
        // Constructor to initialize all fields
        HashEntry() : element(0), info(EntryType::EMPTY) {}
    };

    std::vector<HashEntry> table;
    int tableSize;
    int collisionCount;

    int hash(int key) const {
        int result = key % tableSize;
        return result < 0 ? result + tableSize : result;
    }
};

// ===== Version 2: Chaining =====

class HashTableChaining {
public:
    explicit HashTableChaining(int size = 50003) : tableSize(size) {
        table.resize(tableSize);
        collisionCount = 0;
    }

    void insert(int item) {
        int hashVal = hash(item);
        if (!table[hashVal].empty()) {
            collisionCount++;
        }
        table[hashVal].push_back(item);
    }

    bool search(int item) {
        int hashVal = hash(item);
        for (int val : table[hashVal]) {
            if (val == item) {
                return true;
            }
        }
        return false;
    }

    int getCollisions() const {
        return collisionCount;
    }

private:
    std::vector<std::list<int>> table;
    int tableSize;
    int collisionCount;

    int hash(int key) const {
        int result = key % tableSize;
        return result < 0 ? result + tableSize : result;
    }
};

#endif // H_HASHTABLE
