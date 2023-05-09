#pragma once
// Включает строковую библиотеку, используемую в программе
#include <string>
#include <iostream>
#include "admin.h"    // подключает заголовочный файл с определениями администратора
#include "tools.h"    // подключает заголовочный файл с инструментами

using namespace std;

// Константы для имен файлов
const string HORSE_FILE = "horses.txt";
const string RESULT_FILE = "results.txt";

// Структура для представления информации о лошадях
struct Horse {
    string name;
    string breed;
    int age;
};

// Структура для представления информации о результатах
struct Result {
    string horseName;
    string date;
    double result;
};

// Объявления функций для работы с лошадьми и результатами
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