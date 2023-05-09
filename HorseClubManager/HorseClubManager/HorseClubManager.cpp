#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <iomanip>
#include "user.h"
#include "admin.h"
#include "tools.h"


void showUserMenu(User& currentUser, User users[], int& userCount, Horse horses[], int& horseCount, Result results[], int& resultCount);
void showAdminMenu(User& currentUser, User users[], int& userCount, Horse horses[], int& horseCount, Result results[], int& resultCount);
void loadData_1(Horse horses[], int& horseCount, Result results[], int& resultCount, User users[], int& userCount);


int main() {

    // Установка кодировки консоли на 1251 для корректного отображения кириллицы
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Объявление основных переменных и структур данных
    User currentUser;
    const int max = 100;
    int userCount = 0, horseCount = 0, resultCount = 0, choice;
    User users[max];
    Horse horses[max];
    Result results[max];

    // Загрузка данных из файлов в массивы
    loadData_1(horses, horseCount, results, resultCount, users, userCount);

    // Главный цикл программы, обрабатывающий выбор пользователя (вход, регистрация, выход)
    while (true) {
        system("cls");
        cout << "\n\n 1. Войти\n";
        cout << " 2. Зарегистрироваться\n";
        cout << " 3. Выйти\n\t---> ";
        choice = inputInt(1, 3);

        // Обработка выбора пользователя
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
            // Сохранение данных в файлах перед выходом из программы
            writeHorsesToFile(horses, horseCount);
            writeResultsToFile(results, resultCount);
            writeUsersToFile(users, userCount);
            exit(0);
        default:
            cout << "Неверный выбор. Повторите попытку.\n";
        }
    }
}

// Функция выводит меню пользователя и обрабатывает его выбор
void showUserMenu(User& currentUser, User users[], int& userCount, Horse horses[], int& horseCount, Result results[], int& resultCount) {
    int choice;
    bool exitMenu = false;

    // Цикл для повторного отображения меню, пока пользователь не выберет выход
    while (!exitMenu) {
        cout << "\n\n 1. Просмотреть лошадей\n";
        cout << " 2. Поиск лошади\n";
        cout << " 3. Просмотреть результаты\n";
        cout << " 4. Выйти\n\t---> ";
        choice = inputInt(1, 4);

        // Обработка выбора пользователя
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

// Функция выводит меню администратора и обрабатывает его выбор
void showAdminMenu(User& currentUser, User users[], int& userCount, Horse horses[], int& horseCount, Result results[], int& resultCount) {
    int choice;
    bool exitMenu = false;

    // Цикл для повторного отображения меню, пока администратор не выберет выход
    while (!exitMenu) {
        cout << "\n\n----- Меню администратора-----\n";
        cout << " 1. Работа с аккаунтами\n";
        cout << " 2. Работа с лошадями и рекордами\n";
        cout << " 3. Выйти из меню\n\t---> ";
        choice = inputInt(1, 3);

        // Обработка выбора администратора
        switch (choice) {
        case 1:
            while (!exitMenu) {
                cout << "\n\n----- Работа с аккаунтами -----\n";
                cout << " 1. Просмотреть пользователей\n";
                cout << " 2. Добавить пользователя\n";
                cout << " 3. Удалить пользователя\n";
                cout << " 4. Вернуться в меню\n\t---> ";
                choice = inputInt(1, 4);

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
                cout << "\n\n----- Работа с лошадями и рекордами -----\n";
                cout << " 1. Просмотреть лошадей\n";
                cout << " 2. Добавить лошадь\n";
                cout << " 3. Редактировать лошадь\n";
                cout << " 4. Удалить лошадь\n";
                cout << " 5. Просмотреть результаты\n";
                cout << " 6. Добавить результат\n";
                cout << " 7. Удалить результат\n";
                cout << " 8. Отсортировать результаты\n";
                cout << " 9. Вернуться в меню\n\t---> ";
                choice = inputInt(1, 9);

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

// Функция loadData_1 загружает данные из файлов в массивы
void loadData_1(Horse horses[], int& horseCount, Result results[], int& resultCount, User users[], int& userCount) {
    const int max = 100;
    horseCount = readHorsesFromFile(horses);
    resultCount = readResultsFromFile(results);
    readUsersFromFile(users, userCount);
}
