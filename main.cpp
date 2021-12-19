#include <iostream>
#include <cstring>
#include <vector>
#include <random>
#include "HashTable.h"
#include "FileReader.h"
using namespace std;

#define TABLE_SIZE 5003
#define FULFILL 0.8
#define RECORDS_SIZE (TABLE_SIZE * FULFILL)
void testFunctionality();
int getRandom(int min, int max);
void readFromFile(FileReader &fileReader, vector<record> &records, int offset, int size);

int main(int argc, char** argv) {
    if(argc >= 2 && strcmp(argv[1], "test") == 0){
        testFunctionality();
        return 0;
    }
    HashTable table{TABLE_SIZE};
    vector<record> records;
    FileReader fileReader{"../nazwiska.txt"};

    readFromFile(fileReader, records, getRandom(1, 10000-RECORDS_SIZE), RECORDS_SIZE);
    for (auto record : records)
        table.insert(record);
    cout << "Dodano " << RECORDS_SIZE << " nazwisk do tablicy" << endl;

    for (int i = 0; i < RECORDS_SIZE-1; i+=2){
        table.del(records[i].surname);
    }
    cout << "Usunieto " << RECORDS_SIZE/2 << " nazwisk z tablicy" << endl;

    records.clear();

    readFromFile(fileReader, records, getRandom(10000, 10000+RECORDS_SIZE), RECORDS_SIZE/2);
    for (auto record : records)
        table.insert(record);
    cout << "Dodano " << RECORDS_SIZE/2 << " nazwisk do tablicy" << endl;

    cout << "Znaleziono " << table.countDels() << " rekordów z znacznikiem DEL" << endl;
    cout << (int)(table.countDels()*100/RECORDS_SIZE) << "% z " << RECORDS_SIZE << " to DEL" << endl;
    return 0;
}

void testFunctionality() {
    //wczytaj 15 wierszy
    vector<record> records;
    HashTable table{23};
    FileReader fileReader{"../nazwiska.txt"};
    fileReader.read(17, records);

    //wypisz wiersze i dodaj do tablicy
    for (int i = 0; i < 17; i++) {
        cout << i << "]: " << records[i] << '\n';
        table.insert(records[i]);
    }
    cout << '\n';
    //wypisz zawartość tablicy
    table.printContent();

    //znajdź nazwisko
    auto found = table.find("Nowak");
    cout << found << " -> " << *found << endl;

    //usuń i znajdź jeszcze raz
    table.del("Nowak");
    table.printContent();
    found = table.find("Nowak");
    if(!found){
        cout << "Nie znaleziono Nowaka.\n";
    }

    cout << "Znaleziono " << table.countDels() << " znacznik DEL.\n";
}

int getRandom(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(min, max);
    return distr(gen);
}

void readFromFile(FileReader &fileReader, vector<record> &records, int offset, int size) {
    fileReader.setOffset(offset);
    fileReader.read(size, records);
}
