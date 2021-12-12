//
// Created by szymon on 05.12.2021.
//

#include "FileReader.h"
#include "HashTable.h"
#include <algorithm>
#include <random>

FileReader::FileReader(const string &fileName) : file(fileName) {}

FileReader::~FileReader() {
    file.close();
}

void FileReader::read(int n, vector<record> &records) {
    for (int i = 0; i < n; i++){
        record data;
        file >> data;
        records.push_back(data);
    }

    random_device rd;
    mt19937 g(rd());

    shuffle(records.begin(), records.end(), g);
}

void FileReader::setOffset(int n) {
    file.seekg(0);
    string s;
    for (int i = 0; i < n; ++i) {
        getline(file, s);
    }
}
