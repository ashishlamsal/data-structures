#include <iostream>
#include <string>
#include <vector>

const int ALPHABET_SIZE = 26;

class Trie {
private:
    class Node {
    public:
        char value;
        Node* children[ALPHABET_SIZE];
        bool isEndOfWord;

        Node(const char& value) :value(value), isEndOfWord(false) {
            for (int i = 0; i < ALPHABET_SIZE; i++)
                children[i] = nullptr;
        }

        // true if 'this' has a child i.e. Node{k=ch,v=!nullptr}
        bool hasChild(const char& ch) {
            return children[ch - 'a'] != nullptr;
        }

        // adds a child i.e Node{k=ch,v=Node(ch)} to 'this'
        void addChild(const char& ch) {
            children[ch - 'a'] = new Node(ch);
        }

        // returns v=Node(ch) of 'this'
        Node* getChild(const char& ch) {
            return children[ch - 'a'];
        }

        // returns vector of all child nodes of 'this' 
        std::vector<Node*> getChildren() {
            std::vector<Node*> childNodes;
            for (auto&& ch : children)
                if (ch != nullptr)
                    childNodes.push_back(ch);
            return childNodes;
        }

        // returns true if 'this' has any children
        bool hasChildren() {
            for (auto&& ch : children)
                if (ch != nullptr)
                    return true;
            return false;
        }

        // removes child of 'this' with k=ch
        void removeChild(const char& ch) {
            children[ch - 'a'] = nullptr;
            delete this->children[ch - 'a'];
        }
    };

    Node* root;

private:
    void remove(Node*, const std::string&, int);
    
    void findWords(Node*, std::string, std::vector<std::string>&);
    Node* findLastNodeOf(const std::string&);

public:
    Trie();
    ~Trie();
    
    void insert(const std::string&);
    bool contains(const std::string&);
    void remove(const std::string&);
    
    std::vector<std::string> findWords(const std::string&);
    void display();

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

    if (!child->hasChildren() && !child->isEndOfWord)
        root->removeChild(ch);
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

void Trie::display() {
    std::cout << "All words in Tire: \n";
    for (auto&& word : findWords(""))
        std::cout << word << std::endl;
}

int main() {
    Trie t1;
    t1.insert("carrot");
    t1.insert("can");
    t1.insert("careful");
    t1.insert("caret");
    t1.insert("carpenter");

    t1.remove("caret");

    t1.display();

    std::cout << "\nDoes Trie Contains ? " << std::boolalpha << t1.contains("can") << std::endl;
    std::cout << "Does Trie Contains ? " << std::boolalpha << t1.contains("cane") << std::endl;

    std::cout << "\nWords staring with [prefix] : " << std::endl;
    for (auto&& word : t1.findWords("car"))
        std::cout << word << std::endl;

    return 0;
}