#include <iostream>
#include <string>
#include <fstream>

#include "User.h"
using namespace std;

int countRows(string filename) {
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
User** kreirajUsers(string filename) {
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
void deleteUsers(User** niz, int rows) {
    for (int i = 0; i < rows; i++) {
        delete niz[i];
    }
    delete niz;
}

int main() {
    string filename;
    getline(cin, filename);
    User** niz = kreirajUsers(filename);
    int rows = countRows(filename);

    for (int i = 0; i < rows; i++) {
        niz[i]->printUser();
        cout << "-------" << endl;
    }

    deleteUsers(niz, rows);
    return 0;
}