//
// Created by szymon on 05.12.2021.
//

#ifndef HASHTABLE_FILEREADER_H
#define HASHTABLE_FILEREADER_H
#include <fstream>
#include <vector>
using namespace std;

struct record;

class FileReader {
public:
    explicit FileReader(const string &file);
    void setOffset(int n);
    void read(int n, vector<record> &records);
    virtual ~FileReader();

private:
    ifstream file;
};


#endif //HASHTABLE_FILEREADER_H
