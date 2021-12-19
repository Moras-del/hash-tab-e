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
    unsigned int index = hash(surname.c_str(), surname.length());
    for (int i = 0; i <= tableSize; ++i) {
        unsigned int newIndex = (index + i*i) % tableSize;
        if(table[newIndex] == nullptr || table[newIndex]->surname.empty()) {
            delete table[newIndex];
            table[newIndex] = new record{data.popularity, data.surname};
            return newIndex;
        }
    }
    return -1;
}

record* HashTable::find(const std::string &surname) {
    unsigned int index = hash(surname.c_str(), surname.length());
    for (int i = 0; i <= tableSize; i++){
        unsigned int newIndex = (index + i*i) % tableSize;
        if(table[newIndex] == nullptr)
            return nullptr;
        if(table[newIndex]->surname == surname)
            return table[newIndex];
    }
    return nullptr;
}

void HashTable::del(const std::string &surname) {
    auto rec = find(surname);
    rec->popularity = -1;
    rec->surname = "";
}

uint32_t HashTable::hash(const char *key, int size) {
    unsigned int val = 0;
    for (int j = 0; j < size; ++j, ++val) {
        val += key[j];
        val += (val << 10);
        val ^= (val >> 6);
    }
    val += (val << 3);
    val ^= (val >> 11);
    val += (val << 15);
    return val % tableSize;

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
            std::cout << "NULL";
        std::cout << '\n';
    }
}
