#ifndef HISCORE_H
#define HISCORE_H

#define ENTRIES_NUMBER 5
#define NAME_SIZE 10

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

struct Entry {
    char name[NAME_SIZE + 1];
    int score;
};

class HiScore {
private:

    Entry entries[ENTRIES_NUMBER];
    string filePath;

    string tmpName; // Used in << operator overload.

    void loadFile();
    void saveFile();
    void addScore(const string&, int);

public:
	
    HiScore(const string&);
    bool isScoreGoodEnough(int);

    HiScore& operator<<(const string&);
    void operator<<(int);

    friend ostream& operator<< (ostream&, const HiScore&);
};
#endif
