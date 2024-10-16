#include "BST.h"

BST::BST(User** users, int size) {
    root = createMinimalBST(users, size);
}

BST::~BST() {
    freeTree(root);
}

BSTNode* BST::createMinimalBST(User** users, int size) {
    if (size <= 0) {
        return nullptr;
    }

    std::stack<std::tuple<BSTNode**, int, int>> stack;
    BSTNode* root = new BSTNode(users[size / 2]);
    stack.push(std::make_tuple(&root, 0, size - 1));

    while (!stack.empty()) {
        BSTNode** node = std::get<0>(stack.top());
        int start = std::get<1>(stack.top());
        int end = std::get<2>(stack.top());
        stack.pop();

        int mid = (start + end) / 2;
        *node = new BSTNode(users[mid]);

        if (mid - 1 >= start) {
            stack.push(std::make_tuple(&(*node)->left, start, mid - 1));
        }

        if (mid + 1 <= end) {
            stack.push(std::make_tuple(&(*node)->right, mid + 1, end));
        }
    }

    return root;
}

void BST::printBT() const {
    if (root == nullptr) return;

    std::stack<std::tuple<const BSTNode*, std::string, bool>> nodeStack;
    nodeStack.push({root, "", false});

    while (!nodeStack.empty()) {
        auto [node, prefix, isLeft] = nodeStack.top();
        nodeStack.pop();

        std::cout << prefix;
        std::cout << (isLeft ? "+--- " : "I--- ");
        std::cout << node->user->surname << ", " << node->user->name << ", " << node->user->number << std::endl;

        std::string newPrefix = prefix + (isLeft ? "|   " : "    ");

        if (node->right != nullptr) {
            nodeStack.push({node->right, newPrefix, false});
        }

        if (node->left != nullptr) {
            nodeStack.push({node->left, newPrefix, true});
        }
    }
}

void BST::searchAndPrintBySurname(const std::string& surname) const {
    std::stack<BSTNode*> stack;
    BSTNode* current = root;
    bool found = false;

    while (current != nullptr || !stack.empty()) {
        while (current != nullptr) {
            stack.push(current);
            current = current->left;
        }

        current = stack.top();
        stack.pop();

        if (current->user->surname == surname) {
            std::cout << "Korisnik: " << current->user->name << " " << current->user->surname << ", Broj: " << current->user->number << std::endl;
            found = true;
        }

        current = current->right;
    }

    if (!found) {
        std::cout << "Nema korisnika sa prezimenom: " << surname << std::endl;
    }
}

void BST::searchAndPrintBySurnameAndName(const std::string& surname, const std::string& name) const {
    std::stack<BSTNode*> stack;
    BSTNode* current = root;
    bool found = false;

    while (current != nullptr || !stack.empty()) {
        while (current != nullptr) {
            stack.push(current);
            current = current->left;
        }

        current = stack.top();
        stack.pop();

        if (current->user->surname == surname && current->user->name == name) {
            std::cout << "Korisnik: " << current->user->name << " " << current->user->surname << ", Broj: " << current->user->number << std::endl;
            found = true;
        }

        current = current->right;
    }

    if (!found) {
        std::cout << "Nema korisnika sa imenom: " << name << " i prezimenom: " << surname << std::endl;
    }
}

void BST::addUser(const std::string& surname, const std::string& name, const std::string& number) {
    User* newUser = new User(surname + "," + name + "," + number); // Kreiraj novog korisnika
    BSTNode* newNode = new BSTNode(newUser); // Kreiraj novi čvor za stablo

    if (root == nullptr) {
        root = newNode; // Ako je stablo prazno, novi čvor postaje koren
        return;
    }

    BSTNode* current = root;
    BSTNode* parent = nullptr;

    while (true) {
        parent = current;

        // Odredi gde treba dodati novi čvor
        if (surname < current->user->surname) {
            current = current->left; // Idi levo
            if (current == nullptr) {
                parent->left = newNode; // Dodaj levo
                return;
            }
        } else {
            current = current->right; // Idi desno
            if (current == nullptr) {
                parent->right = newNode; // Dodaj desno
                return;
            }
        }
    }
}

// Preuzeto iz literature "Algoritmi i strukture podataka" - Milo Tomasevic
void BST::remove(const std::string& surname, const std::string& name) {
    BSTNode* p = root;
    BSTNode* q = nullptr;
    bool found = false;

    while (p != nullptr && (p->user->surname != surname || p->user->name != name)) {
        q = p;
        if (surname < p->user->surname || (surname == p->user->surname && name < p->user->name)) {
            p = p->left;
        } else {
            p = p->right;
        }
    }

    if (p == nullptr) {
        std::cout << "Korisnik sa imenom '" << name << "' i prezimenom '" << surname << "' nije pronadjen." << std::endl;
        return;
    }

    found = true;
    BSTNode* rp;

    if (p->left == nullptr) {
        rp = p->right;
    }

    else if (p->right == nullptr) {
        rp = p->left;
    }

    else {
        BSTNode* f = p;
        rp = p->right;
        BSTNode* s = rp->left;

        while (s != nullptr) {
            f = rp;
            rp = s;
            s = s->left;
        }

        if (f != p) {
            f->left = rp->right;
            rp->right = p->right;
        }

        rp->left = p->left;
    }

    if (q == nullptr) {
        root = rp;
    } else if (p == q->left) {
        q->left = rp;
    } else {
        q->right = rp;
    }

    delete p;

    if (found) {
        std::cout << "Korisnik sa imenom '" << name << "' i prezimenom '" << surname << "' je uklonjen." << std::endl;
    }
}

void BST::rename(const std::string& oldSurname, const std::string& oldName, const std::string& newSurname, const std::string& newName, const std::string& newNumber) {
    BSTNode* current = root;
    BSTNode* parent = nullptr;

    while (current != nullptr && (current->user->surname != oldSurname || current->user->name != oldName)) {
        parent = current;
        if (oldSurname < current->user->surname || (oldSurname == current->user->surname && oldName < current->user->name)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == nullptr) {
        std::cout << "Korisnik sa imenom '" << oldName << "' i prezimenom '" << oldSurname << "' nije pronadjen." << std::endl;
        return;
    }

    if (oldSurname == newSurname && oldName == newName) {
        current->user->number = newNumber;
        std::cout << "Broj telefona korisnika je ažuriran na: " << newNumber << std::endl;
        return;
    }

    User* updatedUser = new User(newSurname + "," + newName + "," + newNumber);
    remove(oldSurname, oldName);
    addUser(newSurname, newName, newNumber);

    std::cout << "Korisnik je ažuriran sa novim imenom i/ili prezimenom: " << newName << " " << newSurname << " i brojem: " << newNumber << std::endl;
}

void BST::freeTree(BSTNode* node) {
    if (node == nullptr) {
        return;
    }

    std::stack<BSTNode*> stack;
    stack.push(node);

    while (!stack.empty()) {
        BSTNode* current = stack.top();
        stack.pop();

        if (current->right != nullptr) {
            stack.push(current->right);
        }
        if (current->left != nullptr) {
            stack.push(current->left);
        }

        delete current;
    }
}