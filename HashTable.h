//
// Created by szymon on 02.12.2021.
//

#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H
#include <string>
#include <memory>
#include <sstream>

struct record{
    int popularity;
    std::string surname;

    friend void operator>>(std::istream &ifs, record &data){
        std::string line;
        getline(ifs, line);
        std::istringstream iss(line);
        iss >> data.popularity;
        iss >> data.surname;
    }

    friend std::ostream& operator<<(std::ostream &of, record &data){
        if (data.surname.empty())
            of << "DEL";
        else
            of << data.popularity << " " << data.surname;
        return of;
    }

};

class HashTable {
public:
    explicit HashTable(size_t m);
    ~HashTable();
    unsigned int insert(const record& data);
    record *find(const std::string& surname);
    void del(const std::string& surname);
    int countDels();
    void printContent();

private:
    uint32_t hash(const char* key, int size);
    record** table;
    const size_t tableSize;
};


#endif //HASHTABLE_HASHTABLE_H
