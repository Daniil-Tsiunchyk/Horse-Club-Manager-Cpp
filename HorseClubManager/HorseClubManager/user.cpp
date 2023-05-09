#include "user.h"

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
    age = inputInt(0, 45);

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
    newAge = inputInt(0, 45);

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
    result = inputInt(0, 500);

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