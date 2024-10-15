#ifndef USER_H
#define USER_H
#include <string>
#include <iostream>

using namespace std;

class User {
public:
    User(std::string fileline);
    ~User();

    void printUser();

private:
    void setName(string fileline);
    void setSurname(string fileline);
    void setNumber(string fileline);

    string name;
    string surname;
    string number;
};

#endif
