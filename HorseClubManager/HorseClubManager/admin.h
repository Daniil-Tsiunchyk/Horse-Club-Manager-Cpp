#pragma once
#include "user.h"
#include <fstream>
#include "tools.h"

using namespace std;

const string USER_FILE = "users.txt";

struct User {
    string username;
    string password;
    int status;
};
bool readUsersFromFile(User users[], int& userCount);
bool writeUsersToFile(User users[], int userCount);

void addUser(User users[], int& userCount);
void removeUser(User users[], int& userCount, const User& currentAdmin);
void viewUsers(User users[], int userCount);
User loginUser(User users[], int userCount);
void registerUser(User users[], int& userCount);