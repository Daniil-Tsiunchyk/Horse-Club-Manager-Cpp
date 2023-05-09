#include "admin.h"

// Функция для добавления пользователя
void addUser(User users[], int& userCount) {
    string username, password;
    int status;

    cout << " Введите имя пользователя: ";
    cin >> username;
    cout << " Введите пароль: ";
    cin >> password;
    cout << " Введите статус (0 - пользователь, 1 - администратор): ";
    status = inputInt(0, 1);

    users[userCount].username = username;
    users[userCount].password = password;
    users[userCount].status = status;
    userCount++;

    cout << "Пользователь успешно добавлен." << endl;
}

// Функция для удаления пользователя
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

// Функция для вывода списка пользователей
void viewUsers(User users[], int userCount) {
    cout << "\n Список пользователей: " << endl;
    for (int i = 0; i < userCount; i++) {
        cout << " \tИмя пользователя: " << users[i].username << ", статус: " << (users[i].status == 1 ? "администратор" : "пользователь") << endl;
    }
}

// Функция авторизации
User loginUser(User users[], int userCount) {
    string username;
    const int maxAttempts = 3;
    int attempts = 0;

    while (attempts < maxAttempts) {
        cout << " Введите логин: ";
        cin >> username;
        string password = inputPassword();
        password = doHash(password);

        for (int i = 0; i < userCount; i++) {
            if (users[i].username == username && users[i].password == password) {
                cout << " Добро пожаловать, " << username << "!" << endl;
                return users[i];
            }
        }

        cout << " Неверное имя пользователя или пароль." << endl;
        attempts++;
        if (attempts < maxAttempts) {
            cout << " Осталось попыток: " << (maxAttempts - attempts) << endl;
        }
    }

    cout << " Превышено количество попыток входа. " << endl;
    return User{ "", "", -1 };
}

// Функция для регистрации нового пользователя
void registerUser(User users[], int& userCount) {
    string username;
    cout << " Введите логин: ";
    cin >> username;

    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username) {
            cout << " Имя пользователя уже занято. Пожалуйста, выберите другое имя." << endl;
            return;
        }
    }

    string password = inputPassword();
    cout << " Подтвердите пароль: ";
    string confirmPassword = inputPassword();

    if (password != confirmPassword) {
        cout << " Пароли не совпадают. Попробуйте зарегистрироваться снова." << endl;
        return;
    }

    users[userCount].username = username;
    users[userCount].password = doHash(password);
    users[userCount].status = 0;
    userCount++;

    cout << " Регистрация прошла успешно. Теперь вы можете войти." << endl;
}


// Функция для записи пользователей в файл
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


// Функция для чтения пользователей из файла
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
