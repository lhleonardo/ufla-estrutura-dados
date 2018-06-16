#include <iomanip>
#include <iostream>

using namespace std;

typedef int Data;

enum Position { LEFT, RIGHT };
enum Color { RED, BLACK };

class Node {
    // clang-format off
  friend class RedBlackTree;
    // clang-format on

  private:
    const Data value;

    int level;

    Node* ancestor;
    Node* left;
    Node* right;

    Color color;

  public:
    Node(const Data value) : value(value) {
        this->ancestor = NULL;
        this->left = NULL;
        this->right = NULL;
        this->level = 1;
        this->color = RED;
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

    void updateLevelOfNode(Node* reference);
    void checkColors(Node* reference);

    Node* getNodeToAdd(Data value, Position& positionToAdd);

    // balance the nodes from the reference
    Node* balance(Node* reference);

    void move(Node* older, Node* newer);

    // to process NULL nodes
    Color getColor(Node* reference);
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

void RedBlackTree::updateLevelOfNode(Node* reference) {
    Node* temp = reference;
    while (temp != NULL) {
        temp->level = 1 + max(this->getLevel(temp->left), this->getLevel(temp->right));
        temp = temp->ancestor;
    }
}

Color RedBlackTree::getColor(Node* reference) {
    if (reference == NULL) {
        return BLACK;
    }

    return reference->color;
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

Node* RedBlackTree::getNodeToAdd(Data value, Position& positionToAdd) {
    Node* current = this->root;
    Node* previous;
    while (current != NULL) {
        previous = current;
        if (value < current->value) {
            positionToAdd = LEFT;
            current = current->left;
        } else {
            positionToAdd = RIGHT;
            current = current->right;
        }
    }

    return previous;
}

void RedBlackTree::checkColors(Node* reference) {
    Node* father;
    Node* uncle;
    Node* granfa;
    // father and element can not be ROOT
    while (reference != this->root and reference->ancestor != this->root) {
        father = reference->ancestor;
        granfa = father->ancestor;
        uncle = father == granfa->left ? granfa->right : granfa->left;

        // vermelho nao pode ter filho vermelho
        if (this->getColor(father) == RED and this->getColor(reference) == RED) {
            if (this->getColor(granfa) == BLACK and this->getColor(uncle) == RED) {
                father->color = BLACK;
                if (uncle != NULL)
                    uncle->color = BLACK;

                granfa->color = RED;

                if (granfa == this->root) {
                    granfa->color = BLACK;
                }
            } else if (this->getColor(granfa) == BLACK and
                       this->getColor(uncle) == BLACK) {
                // rotation
                granfa = this->balance(granfa);
            }
        }

        reference = reference->ancestor;
    }
}

void RedBlackTree::add(Data value) {
    if (this->root == NULL) {
        this->root = new Node(value);
        this->root->color = BLACK;

        this->size++;
        return;
    }

    Node* aux = this->root;
    Position positionToAdd;
    Node* father = this->getNodeToAdd(value, positionToAdd);

    Node* current = new Node(value);
    if (positionToAdd == LEFT) {
        father->left = current;
    } else {
        father->right = current;
    }
    current->ancestor = father;

    this->updateLevelOfNode(current);
    this->checkColors(current);

    this->size++;
}

Node* RedBlackTree::balance(Node* reference) {
    // rotation....
    int factor = this->balanceCoefficent(reference);

    // right rotation
    if ((factor > 1) and (this->balanceCoefficent(reference->left) >= 0)) {
        // change the colors of father and his son
        reference->left->color = reference->left->color == RED ? BLACK : RED;
        reference->color = reference->color == RED ? BLACK : RED;
        return rightRotation(reference);
    }

    // left and right rotation
    if ((factor > 1) and (this->balanceCoefficent(reference->left) < 0)) {
        // correct the left son before rotation
        reference->left = leftRotation(reference->left);

        reference->left->color = reference->left->color == RED ? BLACK : RED;
        reference->color = reference->color == RED ? BLACK : RED;

        return rightRotation(reference);
    }

    // right and left rotation
    if ((factor < -1) and (this->balanceCoefficent(reference->right) > 0)) {
        // correct the right son before rotation
        reference->right = rightRotation(reference->right);

        reference->right->color = reference->right->color == RED ? BLACK : RED;
        reference->color = reference->color == RED ? BLACK : RED;

        return leftRotation(reference);
    }

    // only left rotation
    if ((factor < -1) and (this->balanceCoefficent(reference->left) <= 0)) {
        reference->right->color = reference->right->color == RED ? BLACK : RED;
        reference->color = reference->color == RED ? BLACK : RED;
        return leftRotation(reference);
    }

    // it should happen?
    return reference;
}

Node* RedBlackTree::rightRotation(Node* reference) {
    // getting left son from node
    Node* aux = reference->left;
    if (reference == this->root) {
        this->root = aux;
    }

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

Node* RedBlackTree::leftRotation(Node* reference) {
    // getting right son from node
    Node* aux = reference->right;

    if (reference == this->root) {
        this->root = aux;
    }

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
        cout << "[" << setw(2) << reference->value << ":" << setw(2) << level << "]..";
        this->preOrder(reference->right, level + 1);
    }
}

void RedBlackTree::preOrder() {
    this->preOrder(this->root, 0);
    cout << endl;
}

void RedBlackTree::inOrder(Node* reference, unsigned int level) {
    if (reference != NULL) {
        cout << "[" << setw(2) << reference->value << ":" << setw(2) << level;
        cout << (reference->color == RED ? ":R" : ":B") << "]..";
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
        cout << "[" << setw(2) << reference->value << ":" << setw(2) << level << "]..";
    }
}

void RedBlackTree::posOrder() {
    this->posOrder(this->root, 0);
    cout << endl;
}

int main() {
    RedBlackTree rb;

    rb.add(10);
    // rb.add(9);
    rb.add(7);
    rb.add(6);
    rb.add(5);
    rb.add(8);
    rb.add(9);

    rb.inOrder();

    return 0;
}
