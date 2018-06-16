#include <iostream>
#include <iomanip>

using namespace std;

typedef int Data;

enum Position { LEFT, RIGHT };

class Node {
    // clang-format off
  friend class AVLTree;
    // clang-format on

  private:
    const Data value;

    int level;

    Node* ancestor;
    Node* left;
    Node* right;

  public:
    Node(const Data value) : value(value) {
        this->ancestor = NULL;
        this->left = NULL;
        this->right = NULL;
        this->level = 1;
    }
    ~Node() {
        // obviosly i don't delete the ancestor, because this break the tree;
        delete left;
        delete right;
    }
};

class AVLTree {
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

    Node* leftRotation(Node* reference);
    Node* rightRotation(Node* reference);

  public:
    AVLTree();
    ~AVLTree();
    void add(Data value);
    void remove(Data value);
    bool search(Data value);

    void preOrder();
    void posOrder();
    void inOrder();
};

AVLTree::AVLTree() {
    this->root = NULL;
    this->size = 0;
}

AVLTree::~AVLTree() {
    delete this->root;
}

Node* AVLTree::minValue(Node* reference) {
    Node* current = reference;
    Node* previous;

    while (current != NULL) {
        previous = current;
        current = current->left;
    }

    return previous;
}

Node* AVLTree::maxValue(Node* reference) {
    Node* current = reference;
    Node* previous = current;

    while (current != NULL) {
        previous = current;
        current = current->right;
    }

    return previous;
}

int AVLTree::getLevel(Node* reference) {
    if (reference == NULL) {
        return 0;
    }
    return reference->level;
}

int AVLTree::balanceCoefficent(Node* reference) {
    if (reference == NULL) {
        return 0;
    }
    return this->getLevel(reference->left) - this->getLevel(reference->right);
}

void AVLTree::add(Data value) {
    this->root = addAndBalance(this->root, value);
}

Node* AVLTree::balance(Node* reference) {
    reference->level =
        1 + max(this->getLevel(reference->left), this->getLevel(reference->right));

    int factor = this->balanceCoefficent(reference);

    // everything is fine
    if (factor >= -1 and factor <= 1) {
        return reference;
    }
    // right rotation
    if ((factor > 1) and (this->balanceCoefficent(reference->left) >= 0)) {
        return rightRotation(reference);
    }

    // left and right rotation
    if ((factor > 1) and (this->balanceCoefficent(reference->left) < 0)) {
        // correct the left son before rotation
        reference->left = leftRotation(reference->left);

        return rightRotation(reference);
    }

    // right and left rotation
    if ((factor < -1) and (this->balanceCoefficent(reference->right) > 0)) {
        // correct the right son before rotation
        reference->right = rightRotation(reference->right);

        return leftRotation(reference);

    }

    // only left rotation
    if ((factor < -1) and (this->balanceCoefficent(reference->left) <= 0)) {
        return leftRotation(reference);
    }

    // it should happen?
    return reference;
}

Node* AVLTree::rightRotation(Node* reference) {
    // getting left son from node
    Node* aux = reference->left;

    // defines that left son of reference is now left son of aux
    // because aux should be the "root" of this subtree
    reference->left = aux->right;

    // setting correct ancestor of hierarchical
    if (reference->left != NULL) {
        reference->left->ancestor = reference;
    }

    // ancestor of aux is ancestor of reference
    aux->ancestor = reference->ancestor;

    // if reference have ancestor (reference is root?)
    if (reference->ancestor != NULL) {
        // setting correct ancestor of hierarchical
        if (reference->ancestor->left == reference) {
            reference->ancestor->left = aux;
        } else {
            reference->ancestor->right = aux;
        }
    }

    // reference will be the right child of aux
    aux->right = reference;
    aux->right->ancestor = aux;

    // update levels...
    reference->level = 1 + max(this->balanceCoefficent(reference->left),
                               this->balanceCoefficent(reference->right));
    aux->level =
        1 + max(this->balanceCoefficent(aux->left), this->balanceCoefficent(aux->right));

    // return the new root of this subtree
    return aux;
}

Node* AVLTree::leftRotation(Node* reference) {
    // getting right son from node
    Node* aux = reference->right;

    // defines that right son of reference is now left son of aux
    // because aux should be the "root" of this subtree
    reference->right = aux->left;

    // setting correct ancestor of hierarchical
    if (reference->right != NULL) {
        reference->right->ancestor = reference;
    }

    // ancestor of aux is ancestor of reference
    aux->ancestor = reference->ancestor;

    // if reference have ancestor (reference is root?)
    if (reference->ancestor != NULL) {
        // setting correct ancestor of hierarchical
        if (reference->ancestor->left == reference) {
            reference->ancestor->left = aux;
        } else {
            reference->ancestor->right = aux;
        }
    }

    // reference will be the left child of aux
    aux->left = reference;
    aux->left->ancestor = aux;

    // update levels...
    reference->level = 1 + max(this->balanceCoefficent(reference->left),
                               this->balanceCoefficent(reference->right));
    aux->level =
        1 + max(this->balanceCoefficent(aux->left), this->balanceCoefficent(aux->right));

    // return the new root of this subtree
    return aux;
}

Node* AVLTree::addAndBalance(Node* reference, Data value) {
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

bool AVLTree::search(Data value) {
    if (this->size == 0)
        return false;

    if (this->getNode(value) != NULL) {
        return true;
    }

    return false;
}

Node* AVLTree::getNode(Data value) {
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

void AVLTree::move(Node* oldNode, Node* newNode) {
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

void AVLTree::preOrder(Node* reference, unsigned int level) {
    if (reference != NULL) {
        this->preOrder(reference->left, level + 1);
        cout  << "[" << setw(2) << reference->value << ":" << setw(2) << level << "]..";
        this->preOrder(reference->right, level + 1);
    }
}

void AVLTree::preOrder() {
    this->preOrder(this->root, 0);
    cout << endl;
}

void AVLTree::inOrder(Node* reference, unsigned int level) {
    if (reference != NULL) {
        cout  << "[" << setw(2) << reference->value << ":" << setw(2) << level << "]..";
        this->inOrder(reference->left, level + 1);
        this->inOrder(reference->right, level + 1);
    }
}

void AVLTree::inOrder() {
    this->inOrder(this->root, 0);
    cout << endl;
}

void AVLTree::posOrder(Node* reference, unsigned int level) {
    if (reference != NULL) {
        this->posOrder(reference->left, level + 1);
        this->posOrder(reference->right, level + 1);
        cout  << "[" << setw(2) << reference->value << ":" << setw(2) << level << "]..";
    }
}

void AVLTree::posOrder() {
    this->posOrder(this->root, 0);
    cout << endl;
}

int main() {
    AVLTree avl;

    avl.add(9);
    avl.add(1);
    avl.add(4);
    avl.add(5);
    avl.add(7);
    avl.add(13);
    avl.add(12);
    avl.add(17);
    avl.add(35);
    avl.add(21);
    avl.add(14);
    avl.add(2);
    avl.add(8);

    avl.preOrder();
    avl.inOrder();
    avl.posOrder();
    return 0;
}
