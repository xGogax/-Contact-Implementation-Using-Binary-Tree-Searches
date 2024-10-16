#include "User.h"

User::User(std::string fileline) {
    setName(fileline);
    setSurname(fileline);
    setNumber(fileline);
}


void User::setSurname(std::string fileline) {
    this->surname = fileline.substr(0, fileline.find(','));
}

void User::setName(std::string fileline) {
    size_t prva_pozicija = fileline.find(',') + 1;
    size_t druga_pozicija = fileline.find(',', prva_pozicija);
    this->name = fileline.substr(prva_pozicija, druga_pozicija - prva_pozicija);
}

void User::setNumber(std::string fileline) {
    size_t druga_pozicija = fileline.find(',', fileline.find(',') + 1) + 1;
    this->number = fileline.substr(druga_pozicija);
}

void User::printUser() {
    std::cout << "Name: " << this->name << std::endl;
    std::cout << "Surname: " << this->surname << std::endl;
    std::cout << "Number: " << this->number << std::endl;
}

