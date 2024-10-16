#ifndef BST_H
#define BST_H

#include "User.h"
#include <iostream>
#include <stack>
#include <vector>
#include <tuple>

class BSTNode {
public:
    User* user;
    BSTNode* left;
    BSTNode* right;

    BSTNode(User* user) : user(user), left(nullptr), right(nullptr) {}
};

class BST {
public:
    BST(User** users, int size);
    ~BST();

    void printBT() const;

    void searchAndPrintBySurname(const std::string& surname) const;
    void searchAndPrintBySurnameAndName(const std::string& surname, const std::string& name) const;

    void addUser(const std::string& surname, const std::string& name, const std::string& number);
    void remove(const std::string& surname, const std::string& name);

    void rename(const std::string& oldSurname, const std::string& oldName, const std::string& newSurname, const std::string& newName, const std::string& newNumber);
private:
    BSTNode* root;
    BSTNode* createMinimalBST(User** users, int size);
    void freeTree(BSTNode* node);
};

#endif // BST_H
