#include <iostream>
#include <string>

#include "User.h"

int main() {
    User* user = new User("Bonin,Leonard,5231253452");
    user->printUser();
    return 0;
}
