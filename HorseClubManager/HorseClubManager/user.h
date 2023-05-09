#pragma once
#include <string>
#include <iostream>
#include "admin.h"

using namespace std;

const string HORSE_FILE = "horses.txt";
const string RESULT_FILE = "results.txt";

struct Horse {
    string name;
    string breed;
    int age;
};

struct Result {
    string horseName;
    string date;
    double result;
};

int readHorsesFromFile(Horse horses[]);
void writeHorsesToFile(Horse horses[], int horseCount);
int readResultsFromFile(Result results[]);
void writeResultsToFile(Result results[], int resultCount);
void viewHorses(Horse horses[], int horseCount);
void addHorse(Horse horses[], int& horseCount);
void editHorse(Horse horses[], int horseCount);
void findHorse(Horse horses[], int horseCount);
void removeHorse(Horse horses[], int& horseCount);
void viewResults(Result results[], int resultCount);
void addResult(Result results[], int& resultCount);
void removeResult(Result results[], int& resultCount);
void sortResults(Result results[], int resultCount);
