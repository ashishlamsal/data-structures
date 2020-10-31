#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Trie {
private:
    class Node {
    public:
        char value;
        std::unordered_map<char, Node*> children;
        bool isEndOfWord;

        Node(const char& value) :value(value), isEndOfWord(false) {}

        // true if 'this' has a child i.e. Node{k=ch,v=!nullptr}
        bool hasChild(const char& ch) {
            return children[ch] != nullptr;
        }

        // adds a child i.e Node{k=ch,v=Node(ch)} to 'this'
        void addChild(const char& ch) {
            children[ch] = new Node(ch);
        }

        // returns v=Node(ch) of 'this'
        Node* getChild(const char& ch) {
            return children[ch];
        }

        // returns vector of all child nodes of 'this' 
        std::vector<Node*> getChildren() {
            std::vector<Node*> childNodes;
            childNodes.reserve(children.size());

            for (auto&& ch : children)
                childNodes.push_back(ch.second);

            return childNodes;
        }

        // returns true if 'this' has any children
        bool hasChildren() {
            return !children.empty();
        }

        // removes child of 'this' with k=ch
        void removeChild(const char& ch) {
            delete this->children[ch];
            children.erase(ch);
        }
    };

    Node* root;

private:
    void remove(Node*, const std::string&, int);

    void traversePreOrder(Node*);
    void traversePostOrder(Node*);

    void printAllWords(Node*, std::string&, int);
    void findWords(Node*, std::string, std::vector<std::string>&);
    Node* findLastNodeOf(const std::string&);

public:
    Trie();
    ~Trie();

    void insert(const std::string&);
    bool contains(const std::string&);
    void remove(const std::string&);
    void display();

    void traversePreOrder();
    void traversePostOrder();

    std::vector<std::string> findWords(const std::string&);
};

Trie::Trie() {
    root = new Node(' ');
}

Trie::~Trie() {
    delete root;
}

void Trie::insert(const std::string& word) {
    Node* current = root;

    for (auto&& ch : word) {
        if (!current->hasChild(ch))
            current->addChild(ch);
        current = current->getChild(ch);
    }
    current->isEndOfWord = true;
}

bool Trie::contains(const std::string& word) {
    Node* current = root;

    for (auto&& ch : word) {
        if (!current->hasChild(ch))
            return false;
        current = current->getChild(ch);
    }
    return current->isEndOfWord;
}

void Trie::remove(const std::string& word) {
    remove(root, word, 0);
}

void Trie::remove(Node* root, const std::string& word, int depth) {
    if (depth == word.length()) {
        root->isEndOfWord = false;
        return;
    }

    char ch = word[depth];
    Node* child = root->getChild(ch);

    if (child == nullptr)
        return;

    remove(child, word, depth + 1);         // post-order traversal

    // If 'child' does not have any children and it is not end of another word, 
    // then tell 'root' object to remove the 'child'
    if (!child->hasChildren() && !child->isEndOfWord)
        root->removeChild(ch);
}

void Trie::traversePreOrder() {
    traversePreOrder(root);
}

void Trie::traversePreOrder(Node* root) {
    if (root == nullptr)
        return;

    std::cout << root->value << std::endl;
    for (auto&& child : root->getChildren()) {
        traversePreOrder(child);
    }
}

void Trie::traversePostOrder() {
    traversePostOrder(root);
}

void Trie::traversePostOrder(Node* root) {
    if (root == nullptr)
        return;

    for (auto&& child : root->getChildren())
        traversePostOrder(child);
    std::cout << root->value << std::endl;
}

std::vector<std::string> Trie::findWords(const std::string& prefix) {
    std::vector<std::string> words;
    Node* lastNode = findLastNodeOf(prefix);
    findWords(lastNode, prefix, words);
    return words;
}

void Trie::findWords(Node* root, std::string prefix, std::vector<std::string>& words) {
    if (root == nullptr)
        return;

    if (root->isEndOfWord)
        words.push_back(prefix);

    for (auto&& child : root->getChildren()) {
        if (child == nullptr)
            return;
        findWords(child, prefix + child->value, words);
    }
}

typename Trie::Node* Trie::findLastNodeOf(const std::string& prefix) {
    Node* current = root;
    for (auto&& ch : prefix) {
        Node* child = current->getChild(ch);
        if (child == nullptr)
            return nullptr;
        current = child;
    }
    return current;
}

void Trie::printAllWords(Node* root, std::string& word, int depth) {
    if (root->isEndOfWord) {
        for (int i = 0; i < depth; i++)
            std::cout << word[i];
        std::cout << "\n";
    }

    for (auto&& child : root->getChildren()) {
        if (child == nullptr)
            return;
        word[depth] = child->value;
        printAllWords(child, word, depth + 1);
    }
}

void Trie::display() {
    std::cout << "All words in Tire: \n";
    std::string word;
    printAllWords(root, word, 0);
    findWords(word);

}

int main() {
    Trie t1;
    t1.insert("cantilever");
    t1.insert("caret");
    t1.insert("car");
    t1.insert("can");
    t1.insert("canada");
    t1.insert("egg");
    t1.insert("care");
    t1.insert("careful");
    t1.insert("card");
    t1.insert("carpenter");

    t1.remove("caret");

    std::cout << "Does Trie Contains ? " << std::boolalpha << t1.contains("caret") << std::endl;
    std::cout << "Does Trie Contains ? " << std::boolalpha << t1.contains("car") << std::endl;
    std::cout << "Does Trie Contains ? " << std::boolalpha << t1.contains("care") << std::endl;

    t1.display();
    //t1.traversePreOrder();
    //t1.traversePostOrder();

    std::cout << "\nWords staring with [prefix] : " << std::endl;
    for (auto&& word : t1.findWords("car"))
        std::cout << word << std::endl;

    return 0;
}