#ifndef USERARRAY_H
#define USERARRAY_H

#include <fstream>
#include "User.h"

class UserArray {
public:

    UserArray();
    ~UserArray();

    static int countRows(string filename);

    static User** kreirajUsers(string filename);

    static void freeUsers(User** niz, int rows);

    static void printUsers(User** niz, int rows);

private:
};

#endif
