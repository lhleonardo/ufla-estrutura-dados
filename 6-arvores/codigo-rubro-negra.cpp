#include <iostream>

using namespace std;

typedef int Data;

enum Position { LEFT, RIGHT };
enum Color {RED, BLACK};

class Node {
    // clang-format off
  friend class RedBlackTree;
    // clang-format on

  private:
    const Data value;

    int level;
    Color color;

    Node* ancestor;
    Node* left;
    Node* right;

  public:
    Node(const Data value) : value(value) {
        this->ancestor = NULL;
        this->left = NULL;
        this->right = NULL;
        this->color = RED;
        this->level = 1;
    }
    ~Node() {
        // obviosly i don't delete the ancestor, because this break the tree;
        delete left;
        delete right;
    }
};

class RedBlackTree {
  private:
    Node* root;
    int size;

    Node* getNode(Data value);

    // balance the nodes from the reference
    Node* balance(Node* reference);

    // return the actual root, if its changed
    Node* addAndBalance(Node* reference, Data value);

    void move(Node* older, Node* newer);

    // to process NULL nodes
    int getLevel(Node* reference);
    int balanceCoefficent(Node* reference);

    Node* minValue(Node* reference);
    Node* maxValue(Node* reference);

    void inOrder(Node* reference, unsigned int level);
    void preOrder(Node* reference, unsigned int level);
    void posOrder(Node* reference, unsigned int level);

  public:
    RedBlackTree();
    ~RedBlackTree();
    void add(Data value);
    void remove(Data value);
    bool search(Data value);

    void preOrder();
    void posOrder();
    void inOrder();
};

RedBlackTree::RedBlackTree() {
    this->root = NULL;
    this->size = 0;
}

RedBlackTree::~RedBlackTree() {
    delete this->root;
}

Node* RedBlackTree::minValue(Node* reference) {
    Node* current = reference;
    Node* previous;

    while (current != NULL) {
        previous = current;
        current = current->left;
    }

    return previous;
}

Node* RedBlackTree::maxValue(Node* reference) {
    Node* current = reference;
    Node* previous = current;

    while (current != NULL) {
        previous = current;
        current = current->right;
    }

    return previous;
}

int RedBlackTree::getLevel(Node* reference) {
    if (reference == NULL) {
        return 0;
    }
    return reference->level;
}

int RedBlackTree::balanceCoefficent(Node* reference) {
    if (reference == NULL) {
        return 0;
    }
    return this->getLevel(reference->left) - this->getLevel(reference->right);
}

void RedBlackTree::add(Data value) {
    this->root = addAndBalance(this->root, value);
}

Node* RedBlackTree::balance(Node* reference) {
    reference->level =
        1 + max(this->getLevel(reference->left), this->getLevel(reference->right));

    int factor = this->balanceCoefficent(reference);

    if (factor >= -1 and factor <= 1) {
        // everything is fine
        return reference;
    }

    if (factor > 1 and this->balanceCoefficent(reference->left) >= 0) {
        // right rotation
    }

    if (factor > 1 and this->balanceCoefficent(reference->right) < 0) {
        // left and right rotation
    }

    if (factor < -1 and this->balanceCoefficent(reference->right) >= 0) {
        // right and left rotation
    }

    if (factor < -1 and this->balanceCoefficent(reference->left) < 0) {
        // only left rotation
    }

    // it should happen?
    return reference;
}

Node* RedBlackTree::addAndBalance(Node* reference, Data value) {
    // it's here in two cases: empty tree or correct position was found
    if (reference == NULL) {
        return new Node(value);
    }

    if (value < reference->value) {
        // recursive adding and found where it should be added
        reference->left = addAndBalance(reference->left, value);
        // indicates who is the father of the value
        reference->left->ancestor = reference;
    } else if (value > reference->value) {
        // recursive adding and found where it should be added
        reference->right = addAndBalance(reference->right, value);
        // indicates who is the father of the value
        reference->right->ancestor = reference;
    } else {
        // duplicate elements is not allowed
        cerr << "Duplicate elements: " << value << endl;
        return reference;
    }

    // balance after insertion
    return balance(reference);
}
bool RedBlackTree::search(Data value) {
    if (this->size == 0)
        return false;

    if (this->getNode(value) != NULL) {
        return true;
    }

    return false;
}

Node* RedBlackTree::getNode(Data value) {
    Node* current = root;
    bool found = false;

    while (current != NULL and not found) {
        if (value < current->value) {
            current = current->left;
        } else if (value > current->value) {
            current = current->right;
        } else {
            found = true;
        }
    }

    return current;
}

void RedBlackTree::move(Node* oldNode, Node* newNode) {
    if (this->root == oldNode) {
        this->root = newNode;
    } else {
        Node* father = oldNode->ancestor;

        // check if old value is right or left son
        if (father->left == oldNode) {
            father->left = newNode;
        } else {
            father->right = newNode;
        }

        if (newNode != NULL)
            newNode->ancestor = father;
    }
}

void RedBlackTree::preOrder(Node* reference, unsigned int level) {
    if (reference != NULL) {
        this->preOrder(reference->left, level + 1);
        cout << "[" << reference->value << ":" << level << "]..";
        this->preOrder(reference->right, level + 1);
    }
}

void RedBlackTree::preOrder() {
    this->preOrder(this->root, 0);
    cout << endl;
}

void RedBlackTree::inOrder(Node* reference, unsigned int level) {
    if (reference != NULL) {
        cout << "[" << reference->value << ":" << level << "]..";
        this->inOrder(reference->left, level + 1);
        this->inOrder(reference->right, level + 1);
    }
}

void RedBlackTree::inOrder() {
    this->inOrder(this->root, 0);
    cout << endl;
}

void RedBlackTree::posOrder(Node* reference, unsigned int level) {
    if (reference != NULL) {
        this->posOrder(reference->left, level + 1);
        this->posOrder(reference->right, level + 1);
        cout << "[" << reference->value << ":" << level << "]..";
    }
}

void RedBlackTree::posOrder() {
    this->posOrder(this->root, 0);
    cout << endl;
}
