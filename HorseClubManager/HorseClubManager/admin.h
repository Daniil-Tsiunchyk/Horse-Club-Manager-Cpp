#pragma once
// Включает заголовочные файлы, используемые в программе
#include "user.h"      // подключает заголовочный файл с определениями пользователя
#include <fstream>     // для работы с файлами
#include "tools.h"     // подключает заголовочный файл с инструментами

using namespace std;

// Константа для имени файла пользователей
const string USER_FILE = "users.txt";

// Структура для представления информации о пользователях
struct User {
    string username;
    string password;
    int status;
};

// Объявления функций для работы с пользователями
bool readUsersFromFile(User users[], int& userCount);
bool writeUsersToFile(User users[], int userCount);

void addUser(User users[], int& userCount);
void removeUser(User users[], int& userCount, const User& currentAdmin);
void viewUsers(User users[], int userCount);
User loginUser(User users[], int userCount);
void registerUser(User users[], int& userCount);