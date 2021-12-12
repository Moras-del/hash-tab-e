//
// Created by szymon on 02.12.2021.
//

#include "HashTable.h"

#include <iostream>

HashTable::HashTable(size_t m) : tableSize{m} {
    table = new record*[m];
    for (int i = 0; i < m; ++i) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    for (int i = 0; i < tableSize; ++i) {
        delete table[i];
    }
    delete[] table;
}

unsigned int HashTable::insert(const record &data) {
    const std::string surname = data.surname;
    for (int i = 0; i < tableSize; i++){
        unsigned int index = hash(surname.c_str(), surname.length(), i);
        if(table[index] == nullptr || table[index]->surname.empty()) {
            delete table[index];
            table[index] = new record{data.popularity, data.surname};
            return index;
        }
    }
    return -1;
}

record* HashTable::find(const std::string &surname) {
    for (int i = 0; i < tableSize; i++){
        unsigned int index = hash(surname.c_str(), surname.length(), i);
        if(table[index]->surname == surname)
            return table[index];
        if(table[index] == nullptr)
            return nullptr;
    }
    return nullptr;
}

void HashTable::del(const std::string &surname) {
    unsigned int index = 0;
    int i = 0;
    do {
        if(i == tableSize)
            break;
        index = hash(surname.c_str(), surname.length(), i++);
    } while (table[index] != nullptr && table[index]->surname.compare(surname) != 0);
    delete table[index];
    table[index] = new record{-1, ""};
}

uint32_t HashTable::hash(const char *key, int size, int i) {
    unsigned int val = 0;
    for (int j = 0; j < size; ++j, ++val) {
        val += key[j];
        val += (val << 10);
        val ^= (val >> 6);
    }

    val += (val << 3);
    val ^= (val >> 11);
    val += (val << 15);
    return (val+i*i) % tableSize;

}

int HashTable::countDels() {
    int counter = 0;
    for (int i = 0; i < tableSize; ++i) {
        if (table[i] != nullptr && table[i]->surname.empty())
            counter++;
    }
    return counter;
}

void HashTable::printContent() {
    for (int i = 0; i < tableSize; ++i) {
        std::cout << i << "]: ";
        if(table[i])
            std::cout << *table[i];
        else
            std::cout << "BRAK";
        std::cout << '\n';
    }
}
