#include <iostream>
#include <string>
#include <exception>
#include <climits>
#include <vector>
#include <queue>

template <class T>
class BinaryTree {
private:
    class Node {
    public:
        T value;
        Node* leftChild;
        Node* rightChild;
        Node(const T& value) :value(value), leftChild(nullptr), rightChild(nullptr) {}
    };
    Node* root;

private:
    bool isLeaf(Node*);
    void print2DUtil(const std::string&, Node*, bool);

    void TraversePreOrder(Node*);
    void TraverseInOrder(Node*);
    void TraversePostOrder(Node*);

    int height(Node*);
    int minValue(Node*);
    int minBST(Node*);
    int maxBST(Node*);
    int totalNodes(Node*);
    
    bool equals(Node*, Node*);
    bool isBinarySearchTree(Node*, int, int);
    void getNodesAtDistance(Node*, int, std::vector<T>&);

public:
    BinaryTree();
    ~BinaryTree();

    void insert(const T&);
    bool find(const T&);
    void display();

    // Depth-First Traversals
    void TraversePreOrder();
    void TraverseInOrder();
    void TraversePostOrder();

    // Breadth-First Traversal
    void TraverseLevelOrder();
    void BFS();

    int height();
    int minValue();
    int minBST();
    int maxBST();
    int totalNodes();

    bool equals(const BinaryTree<T>&);
    bool isBinarySearchTree();
    std::vector<T> getNodesAtDistance(int);
};

template <class T>
BinaryTree<T>::BinaryTree() :root(nullptr) {}

template <class T>
BinaryTree<T>::~BinaryTree() {}

template <class T>
bool BinaryTree<T>::isLeaf(Node* node) {
    return (node->leftChild == nullptr && node->rightChild == nullptr);
}

template <class T>
void BinaryTree<T>::insert(const T& value) {
    Node* node = new Node(value);
    if (root == nullptr)
        root = node;
    else
    {
        Node* current = root;
        while (true)
        {
            if (value < current->value) {
                if (current->leftChild == nullptr) {
                    current->leftChild = node;
                    break;
                }
                current = current->leftChild;
            }
            else {
                if (current->rightChild == nullptr) {
                    current->rightChild = node;
                    break;
                }
                current = current->rightChild;
            }
        }
    }
}

template <class T>
bool BinaryTree<T>::find(const T& value) {
    Node* current = root;
    while (current != nullptr) {
        if (value < current->value)
            current = current->leftChild;
        else if (value > current->value)
            current = current->rightChild;
        else
            return true;
    }
    return false;
}

template <class T>
void BinaryTree<T>::print2DUtil(const std::string& prefix, Node* root, bool isLeft)
{
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
void BinaryTree<T>::display() {
    print2DUtil("", root, false);

}

template <class T>
void BinaryTree<T>::TraversePreOrder() {
    std::cout << "Preorder Traversal : [  ";
    TraversePreOrder(root);
    std::cout << "\b\b  ]\n";
}

template <class T>
void BinaryTree<T>::TraverseInOrder() {
    std::cout << "Inorder Traversal  : [  ";
    TraverseInOrder(root);
    std::cout << "\b\b  ]\n";
}

template <class T>
void BinaryTree<T>::TraversePostOrder() {
    std::cout << "Postorder Traversal: [  ";
    TraversePostOrder(root);
    std::cout << "\b\b  ]\n";
}


template <class T>
void BinaryTree<T>::TraversePreOrder(Node* root) {
    if (root == nullptr) return;
    std::cout << root->value << ", ";
    TraversePreOrder(root->leftChild);
    TraversePreOrder(root->rightChild);
}

template <class T>
void BinaryTree<T>::TraverseInOrder(Node* root) {
    if (root == nullptr) return;
    TraverseInOrder(root->leftChild);
    std::cout << root->value << ", ";
    TraverseInOrder(root->rightChild);
}

template <class T>
void BinaryTree<T>::TraversePostOrder(Node* root) {
    if (root == nullptr) return;
    TraversePostOrder(root->leftChild);
    TraversePostOrder(root->rightChild);
    std::cout << root->value << ", ";
}

template <class T>
int BinaryTree<T>::height() {
    return height(root);
}

// postorder traversal algorithm
template <class T>
int BinaryTree<T>::height(Node* root) {
    if (root == nullptr) return -1;

    if (isLeaf(root))
        return 0;

    return 1 + (height(root->leftChild) > height(root->rightChild) ?
        height(root->leftChild) : height(root->rightChild));

    // return 1 + std::max(height(root->leftChild), height(root->rightChild));
}

template <class T>
int BinaryTree<T>::minValue() {
    return minValue(root);
}

// postorder traversal algorithm | O(n)
template <class T>
int BinaryTree<T>::minValue(Node* root) {
    if (root == nullptr)
        throw std::runtime_error("Empty Tree");

    int min = root->value;
    if (root->leftChild != nullptr) {
        int left = minValue(root->leftChild);
        min = (min > left) ? left : min;    // min(min,left)
    }
    if (root->rightChild != nullptr) {
        int right = minValue(root->rightChild);
        min = (min > right) ? right : min;  // // min(min,right)
    }
    return min;
}

template <class T>
int BinaryTree<T>::minBST() {
    return minBST(root);
}

// O(logn)
template <class T>
int BinaryTree<T>::minBST(Node* root) {
    if (root == nullptr)
        throw std::runtime_error("Empty Tree");

    Node* current = root;
    while (current->leftChild != nullptr)
        current = current->leftChild;
    return current->value;
}

template <class T>
int BinaryTree<T>::maxBST() {
    return maxBST(root);
}

template <class T>
int BinaryTree<T>::maxBST(Node* root) {
    if (root == nullptr)
        throw std::runtime_error("Empty Tree");

    Node* current = root;
    while (current->rightChild != nullptr)
        current = current->rightChild;
    return current->value;
}

template <class T>
int BinaryTree<T>::totalNodes() {
    return totalNodes(root);
}

template <class T>
int BinaryTree<T>::totalNodes(Node* root) {
    if (root == nullptr)
        return 0;
    return totalNodes(root->leftChild) + totalNodes(root->rightChild) + 1;
}

template <class T>
bool BinaryTree<T>::equals(const BinaryTree<T>& tree) {
    return equals(root, tree.root);
}

// preorder traversal algorithm
template <class T>
bool BinaryTree<T>::equals(Node* first, Node* second) {
    if (first == nullptr && second == nullptr)
        return true;
    if (first != nullptr && second != nullptr)
        return (first->value == second->value) &&
        equals(first->leftChild, second->leftChild) &&
        equals(first->rightChild, second->rightChild);

    return false;
};

template <class T>
bool BinaryTree<T>::isBinarySearchTree() {
    return isBinarySearchTree(root, INT_MIN, INT_MAX);
}

// preorder traversal algorithm
template <class T>
bool BinaryTree<T>::isBinarySearchTree(Node* root, int min, int max) {
    if (root == nullptr)
        return true;
    if (root->value < min || root->value > max)
        return false;

    return isBinarySearchTree(root->leftChild, min, root->value - 1) &&
        isBinarySearchTree(root->rightChild, root->value, max); // right biased | (else, root->value+1) 
};

template <class T>
std::vector<T> BinaryTree<T>::getNodesAtDistance(int distance) {
    std::vector<T> list;
    getNodesAtDistance(root, distance, list);
    return list;
}

template <class T>
void BinaryTree<T>::getNodesAtDistance(Node* root, int distance, std::vector<T>& list) {
    if (root == nullptr)
        return;

    if (distance == 0) {
        list.push_back(root->value);
        return;
    }
    getNodesAtDistance(root->leftChild, distance - 1, list);
    getNodesAtDistance(root->rightChild, distance - 1, list);
};

template <class T>
void BinaryTree<T>::TraverseLevelOrder() {
    std::cout << "Level Order Traversal : [  ";
    for (int i = 0; i <= height(); i++) {
        for (auto&& value : getNodesAtDistance(i))
            std::cout << value << ", ";
    }
    std::cout << "\b\b  ]\n";
};


template <class T>
void BinaryTree<T>::BFS() {
    if (root == nullptr)
        return;

    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* node = q.front();
        q.pop();

        std::cout << node->value << std::endl;

        if (node->leftChild != nullptr)
            q.push(node->leftChild);
        if (node->rightChild != nullptr)
            q.push(node->rightChild);
    }
};

int main() {
    try {
        BinaryTree<int> tree;
        tree.insert(7);
        tree.insert(4);
        tree.insert(9);
        tree.insert(6);
        tree.insert(8);
        tree.insert(10);
        tree.insert(1);

        BinaryTree<int> tree1;
        tree1.insert(7);
        tree1.insert(4);
        tree1.insert(90);
        tree1.insert(6);
        tree1.insert(8);
        tree1.insert(10);
        tree1.insert(1);

        std::cout << "Are two trees equal ? " << std::boolalpha << tree.equals(tree1) << std::endl;
        std::cout << "Is this BST ? " << std::boolalpha << tree.isBinarySearchTree() << std::endl;
        std::cout << "Does tree contains given value ? " << std::boolalpha << tree.find(6) << std::endl;

        tree.display();

        tree.TraversePreOrder();
        tree.TraverseInOrder();
        tree.TraversePostOrder();
        tree.TraverseLevelOrder();
        tree.BFS();
        
        std::cout << "Height of Tree : " << tree.height() << std::endl;
        std::cout << "Minimum value of Tree : " << tree.minValue() << std::endl;
        std::cout << "Minimum value of BST : " << tree.minBST() << std::endl;
        std::cout << "Maximum value of BST : " << tree.maxBST() << std::endl;
        std::cout << "Total number of nodes in BST : " << tree.totalNodes() << std::endl;

        int distance = 2;
        std::vector<int> list = tree.getNodesAtDistance(distance);
        std::cout << "Nodes at distance " << distance << " : [  ";
        for (auto&& value : list)
            std::cout << value << ", ";
        std::cout << "\b\b  ]\n";

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
};