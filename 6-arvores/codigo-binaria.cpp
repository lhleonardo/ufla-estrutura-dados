#include <iostream>

using namespace std;

typedef int Data;

enum Position { LEFT, RIGHT };

class Node {
    // clang-format off
  friend class BinaryTree;
    // clang-format on

  private:
    const Data value;
    unsigned occurrence;
    Node* ancestor;
    Node* left;
    Node* right;

  public:
    Node(const Data value) : value(value) {
        this->ancestor = NULL;
        this->left = NULL;
        this->right = NULL;
        this->occurrence = 1;
    }
    ~Node() {
        // claro que não vou apagar o ancestor(pai), pois poderia apagar toda a BinaryTree
        delete left;
        delete right;
    }
};

class BinaryTree {
  private:
    Node* root;
    int size;

    Node* findPositionToAdd(const Data elemento, Position* posicao);
    Node* getNode(Data value);

    void move(Node* older, Node* newer);

    Node* minValue(Node* reference);
    Node* maxValue(Node* reference);

    void inOrder(Node* reference, unsigned int level);
    void preOrder(Node* reference, unsigned int level);
    void posOrder(Node* reference, unsigned int level);

  public:
    BinaryTree();
    ~BinaryTree();
    void add(Data value);
    void remove(Data value);
    bool search(Data value);

    void preOrder();
    void posOrder();
    void inOrder();
};

BinaryTree::BinaryTree() {
    this->root = NULL;
    this->size = 0;
}

BinaryTree::~BinaryTree() {
    delete this->root;
}

Node* BinaryTree::minValue(Node* reference) {
    Node* current = reference;
    Node* previous;

    while (current != NULL) {
        previous = current;
        current = current->left;
    }

    return previous;
}

Node* BinaryTree::maxValue(Node* reference) {
    Node* current = reference;
    Node* previous = current;

    while (current != NULL) {
        previous = current;
        current = current->right;
    }

    return previous;
}

Node* BinaryTree::findPositionToAdd(Data value, Position* position) {
    Node* current = this->root;
    Node* previous = current;

    while (current != NULL) {
        previous = current;
        if (value > current->value) {
            *position = RIGHT;
            current = current->right;
        } else {
            *position = LEFT;
            current = current->left;
        }
    }

    return previous;
}

void BinaryTree::add(Data value) {
    if (this->root == NULL) {
        this->root = new Node(value);
        this->size++;
        return;
    }

    Node* element = new Node(value);
    Position position;

    Node* existentNode = this->getNode(value);

    // busca o local onde o elemento deverá ser adicionado, trazendo junto consigo seu
    // respectivo pai
    if (existentNode != NULL) {
        existentNode->occurrence = existentNode->occurrence + 1;
    } else {
        // nó não existe na arvore, então deverá ser criado
        Node* rootElement = this->findPositionToAdd(value, &position);

        element->ancestor = rootElement;
        if (position == RIGHT) {
            rootElement->right = element;
        } else {
            rootElement->left = element;
        }
    }

    this->size++;
}

bool BinaryTree::search(Data value) {
    if (this->size == 0)
        return false;

    if (this->getNode(value) != NULL) {
        return true;
    }

    return false;
}

Node* BinaryTree::getNode(Data value) {
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

void BinaryTree::move(Node* oldNode, Node* newNode) {
    if (this->root == oldNode) {
        this->root = newNode;
    } else {
        Node* father = oldNode->ancestor;

        // verifica se o antigo valor é filho a direita ou esquerda
        if (father->left == oldNode) {
            father->left = newNode;
        } else {
            father->right = newNode;
        }

        if (newNode != NULL)
            newNode->ancestor = father;
    }
}

void BinaryTree::remove(Data value) {
    Node* element = this->getNode(value);

    // se nao for encontrado esse elemento, nao faz nada pq ele não existe
    if (element == NULL)
        return;

    if (element->occurrence > 1) {
        element->occurrence--;
    } else {
        if (element->left == NULL and element->right == NULL) {
            delete element;
        } else {
            // tem um só filho?
            // ou exclusivo = ^, ou seja, só funcionará quando apenas tiver
            // um lado verdadeiro
            if (element->left == NULL ^ element->right == NULL) {
                // sobe o filho que nao eh nulo
                this->move(element,
                           element->right == NULL ? element->left : element->right);
            } else {
                // tem os dois filhos... substituirei pelo sucessor
                Node* sucessor = this->minValue(element->right);

                // cuidando do caso em que o sucessor pode ter um filho a direita
                // não tem porque dizer que o filho a direita do sucessor seja filho do nó
                // que será removido
                if (sucessor->ancestor != element) {
                    // filho a direita do sucessor agora deverá estar em seu lugar
                    this->move(sucessor, sucessor->right);
                    // sucessor assume a guarda do filho do nó que será removido
                    sucessor->right = element->right;
                    // filho do nó que será removido aceita sucessor como seu legitimo pai
                    sucessor->right->ancestor = sucessor;
                }
                // tirando o antigo nó de cena e colocando o sucessor como o novo pai
                this->move(element, sucessor);
                // o filho a esquerda não pode ser órfão
                sucessor->left = element->left;
                // definindo o pai para que tudo fique certo
                sucessor->left->ancestor = sucessor;
            }
            // fazendo isso para que, na hora de destruir,
            // não apague coisas indevidas
            element->left = NULL;
            element->right = NULL;
            delete element;
        }
    }

    this->size--;
}

void BinaryTree::preOrder(Node* reference, unsigned int level) {
    if (reference != NULL) {
        this->preOrder(reference->left, level + 1);
        cout << "[" << reference->value << ":" << level << "]..";
        this->preOrder(reference->right, level + 1);
    }
}

void BinaryTree::preOrder() {
    this->preOrder(this->root, 0);
    cout << endl;
}

void BinaryTree::inOrder(Node* reference, unsigned int level) {
    if (reference != NULL) {
        cout << "[" << reference->value << ":" << level << "]..";
        this->inOrder(reference->left, level + 1);
        this->inOrder(reference->right, level + 1);
    }
}

void BinaryTree::inOrder() {
    this->inOrder(this->root, 0);
    cout << endl;
}

void BinaryTree::posOrder(Node* reference, unsigned int level) {
    if (reference != NULL) {
        this->posOrder(reference->left, level + 1);
        this->posOrder(reference->right, level + 1);
        cout << "[" << reference->value << ":" << level << "]..";
    }
}

void BinaryTree::posOrder() {
    this->posOrder(this->root, 0);
    cout << endl;
}
