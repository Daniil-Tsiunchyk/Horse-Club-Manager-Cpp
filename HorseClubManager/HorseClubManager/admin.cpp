#include "admin.h"

void addUser(User users[], int& userCount) {
    string username, password;
    int status;

    cout << " ������� ��� ������������: ";
    cin >> username;
    cout << " ������� ������: ";
    cin >> password;
    cout << " ������� ������ (0 - ������������, 1 - �������������): ";
    cin >> status;

    users[userCount].username = username;
    users[userCount].password = password;
    users[userCount].status = status;
    userCount++;

    cout << "������������ ������� ��������." << endl;
}

void removeUser(User users[], int& userCount, const User& currentAdmin) {
    string username;
    cout << " ������� ��� ������������, �������� ������ �������: ";
    cin >> username;

    int userIndex = -1;
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username) {
            userIndex = i;
            break;
        }
    }

    if (userIndex == -1) {
        cout << " ������������ �� ������." << endl;
        return;
    }

    if (users[userIndex].username == currentAdmin.username) {
        cout << " �� �� ������ ������� ���� �������." << endl;
        return;
    }

    for (int i = userIndex; i < userCount - 1; i++) {
        users[i] = users[i + 1];
    }
    userCount--;

    cout << " ������������ ������� ������." << endl;
}

void viewUsers(User users[], int userCount) {
    cout << " ������ �������������: " << endl;
    for (int i = 0; i < userCount; i++) {
        cout << " \t��� ������������: " << users[i].username << ", ������: " << (users[i].status == 1 ? "�������������" : "������������") << endl;
    }
}


User loginUser(User users[], int userCount) {
    string username, password;
    cout << " ������� �����: ";
    cin >> username;
    cout << " ������� ������: ";
    cin >> password;
    password = doHash(password);
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username && users[i].password == password) {
            cout << " ����� ����������, " << username << "!" << endl;
            return users[i];
        }
    }

    cout << " �������� ��� ������������ ��� ������." << endl;
    return User{ "", "", -1 };
}

void registerUser(User users[], int& userCount) {
    string username, password;
    cout << " ������� �����: ";
    cin >> username;
    cout << " ������� ������: ";
    cin >> password;

    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username) {
            cout << " ��� ������������ ��� ������. ����������, �������� ������ ���." << endl;
            return;
        }
    }

    users[userCount].username = username;
    users[userCount].password = doHash(password);
    users[userCount].status = 0;
    userCount++;

    cout << " ����������� ������ �������. ������ �� ������ �����." << endl;
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