#include <iostream>

template <class T>
class AVLTree {
private:
    class AVLNode {
    public:
        T value;
        int height;
        AVLNode* leftChild;
        AVLNode* rightChild;
        AVLNode(const T& value) :value(value), height(0), leftChild(nullptr), rightChild(nullptr) {}
    };
    AVLNode* root;

private:
    void print2DUtil(const std::string&, AVLNode*, bool);

    AVLNode* insert(AVLNode*, const T&);

    int height(AVLNode*);
    void setHeight(AVLNode*);

    bool isLeftHeavy(AVLNode*);
    bool isRightHeavy(AVLNode*);
    int BalanceFactor(AVLNode*);

    AVLNode* balance(AVLNode*);
    AVLNode* leftRotate(AVLNode*);
    AVLNode* rightRotate(AVLNode*);

public:
    AVLTree();
    ~AVLTree();
    void insert(const T&);
    void display();
};

template <class T>
AVLTree<T>::AVLTree() :root(nullptr) {}

template <class T>
AVLTree<T>::~AVLTree() {}

template <class T>
void AVLTree<T>::insert(const T& value) {
    std::cout << "\n->Insert: " << value << std::endl;
    root = insert(root, value);
    display();
}

template <class T>
typename AVLTree<T>::AVLNode* AVLTree<T>::insert(AVLNode* root, const T& value) {
    if (root == nullptr)
        return new AVLNode(value);

    if (value < root->value)
        root->leftChild = insert(root->leftChild, value);
    else
        root->rightChild = insert(root->rightChild, value);

    setHeight(root);    // calcualte height of each node

    return balance(root);
}

template <class T>
typename AVLTree<T>::AVLNode* AVLTree<T>::balance(AVLNode* root) {
    if (isLeftHeavy(root))
    {
        display();
        std::cout << root->value << " is left heavy" << std::endl;

        if (BalanceFactor(root->leftChild) < 0) {
            std::cout << "Perform left rotation on " << root->leftChild->value << std::endl;
            root->leftChild = leftRotate(root->leftChild);
        }
        std::cout << "Perform right rotation on " << root->value << std::endl;
        return rightRotate(root);
    }
    else if (isRightHeavy(root))
    {
        display();
        std::cout << root->value << " is right heavy" << std::endl;

        if (BalanceFactor(root->rightChild) > 0) {
            std::cout << "Perform right rotation on " << root->rightChild->value << std::endl;
            root->rightChild = rightRotate(root->rightChild);
        }
        std::cout << "Perform left rotation on " << root->value << std::endl;
        return leftRotate(root);
    }

    return root;
}

template <class T>
typename AVLTree<T>::AVLNode* AVLTree<T>::leftRotate(AVLNode* root) {
    AVLNode* newRoot = root->rightChild;

    root->rightChild = newRoot->leftChild;
    newRoot->leftChild = root;

    setHeight(root);
    setHeight(newRoot);

    return newRoot;
}

template <class T>
typename AVLTree<T>::AVLNode* AVLTree<T>::rightRotate(AVLNode* root) {
    AVLNode* newRoot = root->leftChild;

    root->leftChild = newRoot->rightChild;
    newRoot->rightChild = root;

    setHeight(root);
    setHeight(newRoot);

    return newRoot;
};

template <class T>
int AVLTree<T>::height(AVLNode* node) {
    return (node == nullptr) ? -1 : node->height;
}

template <class T>
void AVLTree<T>::setHeight(AVLNode* node) {
    node->height = 1 + (height(node->leftChild) > height(node->rightChild) ?
        height(node->leftChild) : height(node->rightChild));
}

template <class T>
bool AVLTree<T>::isLeftHeavy(AVLNode* node) {
    return BalanceFactor(node) > 1;
}

template <class T>
bool AVLTree<T>::isRightHeavy(AVLNode* node) {
    return BalanceFactor(node) < -1;
}

template <class T>
int AVLTree<T>::BalanceFactor(AVLNode* node) {
    return (node == nullptr) ? 0 : height(node->leftChild) - height(node->rightChild);
}

template <class T>
void AVLTree<T>::print2DUtil(const std::string& prefix, AVLNode* root, bool isLeft) {
    // Base case  
    if (root == nullptr)
        return;

    std::cout << prefix;
    std::cout << (isLeft ? "├──" : "└──");
    std::cout << root->value << std::endl;

    // Process left child and right child  
    print2DUtil(prefix + (isLeft ? "│   " : "    "), root->leftChild, true);
    print2DUtil(prefix + (isLeft ? "│   " : "    "), root->rightChild, false);
}

template <class T>
void AVLTree<T>::display() {
    print2DUtil("", root, false);
}

int main() {
    AVLTree<int> tree;
    tree.insert(30);
    tree.insert(15);
    tree.insert(18);
    tree.insert(10);
    tree.insert(16);
    tree.insert(7);
    tree.insert(8);
    std::cout << "AVL Tree: " << std::endl;
    tree.display();
    return 0;
}


/*
Note : [use of typename keyword]

In a template that we write, there are two kinds of names (identifiers) that could be used
- dependant names and non- dependant names.
A dependant name is a name that depends on a template parameter;
a non- dependant name has the same meaning irrespective of what the template parameters are.

template< typename T > void foo( T& x, int value )
{
    ++ T::static_member_variable ; // 'static_member_variable' is a dependant name
    ++value ; // 'value' is a non- dependant name
}

What a dependant name refers to could be something different for each different instantiation
of the template. As a consequence, C++ templates are subject to "two-phase name lookup". When
a template is initially parsed (before any instantiation takes place) the compiler looks up
the non-dependent names. When a particular instantiation of the template takes place, the
template parameters are known by then, and the compiler looks up dependent names.

During the first phase, the parser needs to know if a dependant name is the name of a type or
the name of a non-type. By default, a dependant name is assumed to be the name of a non-type.
The typename keyword before a dependant name disambiguates it to be the name of a type.

In template <typename T> typename T::value_type print(const T& c) ;, we clarify that the
dependant name value_type is the name of a type.

*/