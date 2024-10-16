#include "UserArray.h"

int UserArray::countRows(string filename) {
    ifstream file(filename);
    string line;

    if(!file.is_open()) {
        cerr << "Unable to open file" << endl;
        return 0;
    }

    int i = 0;
    getline(file, line);
    while (getline(file, line)) {
        i++;
    }

    return i;
}

User ** UserArray::kreirajUsers(string filename) {
    ifstream file(filename);
    string line;

    if(!file.is_open()) {
        cerr << "Unable to open file" << endl;
    }

    int i = 0;
    User** x = new User*[countRows(filename)];
    getline(file, line);
    while (getline(file, line)) {
        User* user = new User(line);
        x[i] = user;
        i++;
    }

    file.close();

    return x;
}

void UserArray::freeUsers(User** niz, int rows) {
    for (int i = 0; i < rows; i++) {
        delete niz[i];
    }
    delete[] niz;
}

void UserArray::printUsers(User **niz, int rows) {
    for (int i = 0; i < rows; i++) {
        niz[i]->printUser();
        cout << "-------" << endl;
    }
}
