#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>

using namespace std;

const string HORSE_FILE = "horses.txt";
const string RESULT_FILE = "results.txt";
const string USER_FILE = "users.txt";

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

struct User {
    string username;
    string password;
    int status;
};
bool readUsersFromFile(User users[], int& userCount);
bool writeUsersToFile(User users[], int userCount);
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
void showUserMenu(User& currentUser, User users[], int& userCount, Horse horses[], int& horseCount, Result results[], int& resultCount);
void addUser(User users[], int& userCount);
void removeUser(User users[], int& userCount, const User& currentAdmin);
void viewUsers(User users[], int userCount);
void showAdminMenu(User& currentUser, User users[], int& userCount, Horse horses[], int& horseCount, Result results[], int& resultCount);
void loadData_1(Horse horses[], int& horseCount, Result results[], int& resultCount, User users[], int& userCount);
User loginUser(User users[], int userCount);
void registerUser(User users[], int& userCount);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    User currentUser;
    const int max = 100;
    int userCount = 0, horseCount = 0, resultCount = 0, choice;
    User users[max];
    Horse horses[max];
    Result results[max];


    loadData_1(horses, horseCount, results, resultCount, users, userCount);

    while (true) {
        cout << "\n 1. Войти\n";
        cout << " 2. Зарегистрироваться\n";
        cout << " 3. Выйти\n";
        cin >> choice;

        switch (choice) {
        case 1:
            currentUser = loginUser(users, userCount);
            if (currentUser.status == 1) {
                showAdminMenu(currentUser, users, userCount, horses, horseCount, results, resultCount);
            }
            else if (currentUser.status == 0) {
                showUserMenu(currentUser, users, userCount, horses, horseCount, results, resultCount);
            }
            break;
        case 2:
            registerUser(users, userCount);
            break;
        case 3:
            writeHorsesToFile(horses, horseCount);
            writeResultsToFile(results, resultCount);
            writeUsersToFile(users, userCount);
            exit(0);
        default:
            cout << "Неверный выбор. Повторите попытку.\n";
        }
    }
}


void addUser(User users[], int& userCount) {
    string username, password;
    int status;

    cout << " Введите имя пользователя: ";
    cin >> username;
    cout << " Введите пароль: ";
    cin >> password;
    cout << " Введите статус (0 - пользователь, 1 - администратор): ";
    cin >> status;

    users[userCount].username = username;
    users[userCount].password = password;
    users[userCount].status = status;
    userCount++;

    cout << "Пользователь успешно добавлен." << endl;
}

void removeUser(User users[], int& userCount, const User& currentAdmin) {
    string username;
    cout << " Введите имя пользователя, которого хотите удалить: ";
    cin >> username;

    int userIndex = -1;
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username) {
            userIndex = i;
            break;
        }
    }

    if (userIndex == -1) {
        cout << " Пользователь не найден." << endl;
        return;
    }

    if (users[userIndex].username == currentAdmin.username) {
        cout << " Вы не можете удалить свой аккаунт." << endl;
        return;
    }

    for (int i = userIndex; i < userCount - 1; i++) {
        users[i] = users[i + 1];
    }
    userCount--;

    cout << " Пользователь успешно удален." << endl;
}

void viewUsers(User users[], int userCount) {
    cout << " Список пользователей: " << endl;
    for (int i = 0; i < userCount; i++) {
        cout << " \tИмя пользователя: " << users[i].username << ", статус: " << (users[i].status == 1 ? "администратор" : "пользователь") << endl;
    }
}


void showAdminMenu(User& currentUser, User users[], int& userCount, Horse horses[], int& horseCount, Result results[], int& resultCount) {
    int choice;
    bool exitMenu = false;

    while (!exitMenu) {
        cout << "\n----- Меню администратора-----\n";
        cout << " 1. Работа с аккаунтами\n";
        cout << " 2. Работа с лошадями и рекордами\n";
        cout << " 3. Выйти из меню\n";
        cout << "\tВыберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            while (!exitMenu) {
                cout << "\n----- Работа с аккаунтами -----\n";
                cout << " 1. Просмотреть пользователей\n";
                cout << " 2. Добавить пользователя\n";
                cout << " 3. Удалить пользователя\n";
                cout << " 4. Вернуться в меню\n";
                cout << "\tВыберите действие: ";
                cin >> choice;

                switch (choice) {
                case 1:
                    viewUsers(users, userCount);
                    break;
                case 2:
                    addUser(users, userCount);
                    break;
                case 3:
                    removeUser(users, userCount, currentUser);
                    break;
                case 4:
                    exitMenu = true;
                    break;
                default:
                    cout << "Неверный выбор. Повторите попытку.\n";
                }
            }
            exitMenu = false;
            break;
        case 2:
            while (!exitMenu) {
                cout << "\n----- Работа с лошадями и рекордами -----\n";
                cout << " 1. Просмотреть лошадей\n";
                cout << " 2. Добавить лошадь\n";
                cout << " 3. Редактировать лошадь\n";
                cout << " 4. Удалить лошадь\n";
                cout << " 5. Просмотреть результаты\n";
                cout << " 6. Добавить результат\n";
                cout << " 7. Удалить результат\n";
                cout << " 8. Отсортировать результаты\n";
                cout << " 9. Вернуться в меню\n";
                cout << "\tВыберите действие: ";
                cin >> choice;

                switch (choice) {
                case 1:
                    viewHorses(horses, horseCount);
                    break;
                case 2:
                    addHorse(horses, horseCount);
                    break;
                case 3:
                    editHorse(horses, horseCount);
                    break;
                case 4:
                    removeHorse(horses, horseCount);
                    break;
                case 5:
                    viewResults(results, resultCount);
                    break;
                case 6:
                    addResult(results, resultCount);
                    break;
                case 7:
                    removeResult(results, resultCount);
                    break;
                case 8:
                    sortResults(results, resultCount);
                    break;
                case 9:
                    exitMenu = true;
                    break;
                default:
                    cout << " Неверный выбор. Повторите попытку.\n";
                }
            }
            exitMenu = false;
            break;
        case 3:
            exitMenu = true;
            break;
        default:
            cout << " Неверный выбор. Повторите попытку.\n";
        }
    }
}

void loadData_1(Horse horses[], int& horseCount, Result results[], int& resultCount, User users[], int& userCount) {
    const int max = 100;
    horseCount = readHorsesFromFile(horses);
    resultCount = readResultsFromFile(results);
    readUsersFromFile(users, userCount);
}

User loginUser(User users[], int userCount) {
    string username, password;
    cout << " Введите логин: ";
    cin >> username;
    cout << " Введите пароль: ";
    cin >> password;

    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username && users[i].password == password) {
            cout << " Добро пожаловать, " << username << "!" << endl;
            return users[i];
        }
    }

    cout << " Неверное имя пользователя или пароль." << endl;
    return User{ "", "", -1 };
}

void registerUser(User users[], int& userCount) {
    string username, password;
    cout << " Введите логин: ";
    cin >> username;
    cout << " Введите пароль: ";
    cin >> password;

    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username) {
            cout << " Имя пользователя уже занято. Пожалуйста, выберите другое имя." << endl;
            return;
        }
    }

    users[userCount].username = username;
    users[userCount].password = password;
    users[userCount].status = 0;
    userCount++;

    cout << " Регистрация успешна. Теперь вы можете войти." << endl;
}

void viewHorses(Horse horses[], int horseCount) {
    cout << " Список лошадей:" << endl;
    for (int i = 0; i < horseCount; i++) {
        cout << "\tИмя: " << horses[i].name << ", порода: " << horses[i].breed << ", возраст: " << horses[i].age << endl;
    }
}

void addHorse(Horse horses[], int& horseCount) {
    string name, breed;
    int age;

    cout << " Введите имя лошади: ";
    cin >> name;
    cout << " Введите породу лошади: ";
    cin >> breed;
    cout << " Введите возраст лошади: ";
    cin >> age;

    horses[horseCount].name = name;
    horses[horseCount].breed = breed;
    horses[horseCount].age = age;
    horseCount++;

    cout << " Лошадь успешно добавлена." << endl;
}

void editHorse(Horse horses[], int horseCount) {
    string name;
    cout << " Введите имя лошади для редактирования: ";
    cin >> name;

    int horseIndex = -1;
    for (int i = 0; i < horseCount; i++) {
        if (horses[i].name == name) {
            horseIndex = i;
            break;
        }
    }

    if (horseIndex == -1) {
        cout << " Лошадь не найдена." << endl;
        return;
    }

    string newName, newBreed;
    int newAge;
    cout << " Введите новое имя: ";
    cin >> newName;
    cout << " Введите новую породу: ";
    cin >> newBreed;
    cout << " Введите новый возраст: ";
    cin >> newAge;

    horses[horseIndex].name = newName;
    horses[horseIndex].breed = newBreed;
    horses[horseIndex].age = newAge;

    cout << " Данные лошади успешно обновлены." << endl;
}

void findHorse(Horse horses[], int horseCount) {
    string name;
    cout << " Введите имя лошади для поиска: ";
    cin >> name;

    for (int i = 0; i < horseCount; i++) {
        if (horses[i].name == name) {
            cout << "\tИмя: " << horses[i].name << ", порода: " << horses[i].breed << ", возраст: " << horses[i].age << endl;
            return;
        }
    }

    cout << " Лошадь не найдена." << endl;
}

void removeHorse(Horse horses[], int& horseCount) {
    string name;
    cout << " Введите имя лошади для удаления: ";
    cin >> name;

    int horseIndex = -1;
    for (int i = 0; i < horseCount; i++) {
        if (horses[i].name == name) {
            horseIndex = i;
            break;
        }
    }

    if (horseIndex == -1) {
        cout << " Лошадь не найдена." << endl;
        return;
    }

    for (int i = horseIndex; i < horseCount - 1; i++) {
        horses[i] = horses[i + 1];
    }
    horseCount--;
    cout << " Лошадь успешно удалена." << endl;
}
void viewResults(Result results[], int resultCount) {
    cout << " Список результатов:" << endl;
    for (int i = 0; i < resultCount; i++) {
        cout << "\tИмя лошади: " << results[i].horseName << ", дата: " << results[i].date << ", результат: " << results[i].result << endl;
    }
}

void addResult(Result results[], int& resultCount) {
    string horseName, date;
    int result;
    cout << " Введите имя лошади: ";
    cin >> horseName;
    cout << " Введите дату (дд.мм.гггг): ";
    cin >> date;
    cout << " Введите результат: ";
    cin >> result;

    results[resultCount].horseName = horseName;
    results[resultCount].date = date;
    results[resultCount].result = result;
    resultCount++;

    cout << " Результат успешно добавлен." << endl;
}

void removeResult(Result results[], int& resultCount) {
    string date;
    cout << " Введите дату результатов для удаления (дд.мм.гггг): ";
    cin >> date;
    int resultIndex = -1;
    for (int i = 0; i < resultCount; i++) {
        if (results[i].date == date) {
            resultIndex = i;
            break;
        }
    }

    if (resultIndex == -1) {
        cout << " Результат не найден." << endl;
        return;
    }

    for (int i = resultIndex; i < resultCount - 1; i++) {
        results[i] = results[i + 1];
    }
    resultCount--;

    cout << " Результат успешно удален." << endl;
}
void sortResults(Result results[], int resultCount) {
    for (int i = 0; i < resultCount - 1; i++) {
        for (int j = 0; j < resultCount - i - 1; j++) {
            if (results[j].result < results[j + 1].result) {
                swap(results[j], results[j + 1]);
            }
        }
    }
    cout << " Результаты отсортированы по убыванию." << endl;
}

void showUserMenu(User& currentUser, User users[], int& userCount, Horse horses[], int& horseCount, Result results[], int& resultCount) {
    int choice;
    bool exitMenu = false;
    while (!exitMenu) {
        cout << "\n 1. Просмотреть лошадей\n";
        cout << " 2. Поиск лошади\n";
        cout << " 3. Просмотреть результаты\n";
        cout << " 4. Выйти\n";
        cin >> choice;

        switch (choice) {
        case 1:
            viewHorses(horses, horseCount);
            break;
        case 2:
            findHorse(horses, horseCount);
            break;
        case 3:
            viewResults(results, resultCount);
            break;
        case 4:
            exitMenu = true;
            break;
        default:
            cout << " Неверный выбор. Повторите попытку.\n";
        }
    }
}
bool writeUsersToFile(User users[], int userCount) {
    ofstream file(USER_FILE);
    if (!file) {
        return false;
    }
    for (int i = 0; i < userCount; i++) {
        file << users[i].username << "\n";
        file << users[i].password << "\n";
        file << users[i].status;
        if (i < userCount - 1) {
            file << "\n";
        }
    }
    file.close();
    return true;
}

void writeHorsesToFile(Horse horses[], int horseCount) {
    ofstream file(HORSE_FILE);
    for (int i = 0; i < horseCount; i++) {
        file << horses[i].name << "\n";
        file << horses[i].breed << "\n";
        file << horses[i].age;
        if (i < horseCount - 1) {
            file << endl;
        }
    }
    file.close();
}

void writeResultsToFile(Result results[], int resultCount) {
    ofstream file(RESULT_FILE);
    for (int i = 0; i < resultCount; i++) {
        file << results[i].horseName << "\n";
        file << results[i].date << "\n";
        file << results[i].result;
        if (i < resultCount - 1) {
            file << endl;
        }
    }
    file.close();
}

bool readUsersFromFile(User users[], int& userCount) {
    ifstream file(USER_FILE);
    if (!file) {
        return false;
    }
    userCount = 0;
    while (getline(file, users[userCount].username) &&
        getline(file, users[userCount].password) &&
        (file >> users[userCount].status)) {
        file.ignore();
        userCount++;
    }
    file.close();
    return true;
}

int readHorsesFromFile(Horse horses[]) {
    ifstream file(HORSE_FILE);
    int horseCount = 0;
    while (getline(file, horses[horseCount].name) &&
        getline(file, horses[horseCount].breed) &&
        (file >> horses[horseCount].age)) {
        file.ignore();
        horseCount++;
    }
    file.close();
    return horseCount;
}

int readResultsFromFile(Result results[]) {
    ifstream file(RESULT_FILE);
    int resultCount = 0;
    while (getline(file, results[resultCount].horseName) &&
        getline(file, results[resultCount].date) &&
        (file >> results[resultCount].result)) {
        file.ignore();
        resultCount++;
    }
    file.close();
    return resultCount;
}
