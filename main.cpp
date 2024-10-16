#include <string>
#include "UserArray.h"
#include "BST.h"

using namespace std;

int main() {
    string filename = "Contacts20.txt";
    User** niz = UserArray::kreirajUsers(filename);
    int rows = UserArray::countRows(filename);

    BST bst(niz, rows);

    bst.printBT();

    cout << "" << endl;
    cout << "" << endl;
    cout << "" << endl;

    string oldSurname = "Shergill";
    string oldName = "Alla";
    string newSurname = "Stankovic";
    string newName = "Lazar";
    string newNumber = "123456789";

    bst.rename(oldSurname, oldName, newSurname, newName, newNumber);

    bst.printBT();

    UserArray::freeUsers(niz, rows);
    return 0;
}
