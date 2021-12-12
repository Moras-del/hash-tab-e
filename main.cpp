#include <iostream>
#include <cstring>
#include <vector>
#include <random>
#include "HashTable.h"
#include "FileReader.h"
using namespace std;

#define TABLE_SIZE 8000
#define FULFILL 0.8
#define RECORDS_SIZE (TABLE_SIZE * FULFILL)
void testFunctionality();
int getRandom(int min, int max);

int main(int argc, char** argv) {
    if(argc >= 2 && strcmp(argv[1], "test") == 0){
        testFunctionality();
        return 0;
    }
    vector<record> records;
    FileReader fileReader{"../nazwiska.txt"};
    fileReader.setOffset(getRandom(1, 10000-RECORDS_SIZE));
    fileReader.read(RECORDS_SIZE, records);
    HashTable table{TABLE_SIZE};
    for (auto record : records)
        table.insert(record);
    cout << "Dodano " << RECORDS_SIZE << " nazwisk do tablicy" << endl;
    for (int i = 0; i < RECORDS_SIZE; i+=2)
        table.del(records[i].surname);
    cout << "Usunieto " << RECORDS_SIZE/2 << " nazwisk z tablicy" << endl;
    records.clear();
    fileReader.setOffset(getRandom(10000, 10000+RECORDS_SIZE));
    fileReader.read(RECORDS_SIZE/2, records);
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
    HashTable table{15};
    FileReader fileReader{"../nazwiska.txt"};
    fileReader.read(15, records);

    //wypisz wiersze i dodaj do tablicy
    for (int i = 0; i < 15; i++) {
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
    cout << table.countDels() << endl;
    found = table.find("Nowak");
    cout << found << endl;
}

int getRandom(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(min, max);
    return distr(gen);
}
