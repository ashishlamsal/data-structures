#include <iostream>
#include <exception>
#include <string>
#include <unordered_map>
#include <stack>
#include <queue>
#include <set>
#include <list>

class Graph {
private:
    class Node {
    public:
        std::string label;
        Node(const std::string& label) :label(label) {}
    };

    // use map for fast lookup insted of a list of nodes
    std::unordered_map<std::string, Node*> nodes;

    // list of lists of adjacent node
    // eg. Node A = [B,C,D] where, B,C,D are adjacent to A
    std::unordered_map<Node*, std::list<Node*>> adjacencyList;

    void depthFirstTraversalRec(Node*, std::set<Node*>&);


public:
    void addNode(const std::string&);
    void addEdge(const std::string&, const std::string&);

    void removeNode(const std::string&);
    void removeEdge(const std::string&, const std::string&);

    void depthFirstTraversalRec(const std::string&);
    void depthFirstTraversalItr(const std::string&);

    void breadthFirstTraversal(const std::string&);

    void print();
};

void Graph::addNode(const  std::string& label) {
    Node* new_node = new Node(label);

    // add new node to list of nodes (map)
    nodes.emplace(label, new_node);
}

void Graph::addEdge(const std::string& from, const std::string& to) {
    if (nodes.find(from) == nodes.end())
        throw std::runtime_error("Error: " + from + " node not found");
    if (nodes.find(to) == nodes.end())
        throw std::runtime_error("Error: " + to + " node not found");

    // add "to node" to "from node" list as its adjacent node
    adjacencyList[nodes[from]].push_back(nodes[to]);

}

void Graph::removeNode(const std::string& node) {
    if (nodes.find(node) == nodes.end())
        return;

    for (auto&& n : adjacencyList) {
        n.second.remove(nodes[node]);
    }
    adjacencyList.erase(nodes[node]);
    nodes.erase(node);
}

void Graph::removeEdge(const std::string& from, const std::string& to) {
    if (nodes.find(from) == nodes.end() || nodes.find(to) == nodes.end())
        return;

    adjacencyList[nodes[from]].remove(nodes[to]);
}

void Graph::print() {
    for (auto&& n : adjacencyList) {
        if (!n.second.empty()) {
            std::cout << n.first->label + " is connected to [ ";
            for (auto&& i : n.second) {
                std::cout << i->label << ", ";
            }
            std::cout << "\b\b ]" << std::endl;
        }
    }
}

void Graph::depthFirstTraversalRec(const std::string& root) {
    std::set<Node*> visited;
    if (nodes.find(root) == nodes.end())
        throw std::runtime_error("Error: " + root + " node not found");

    depthFirstTraversalRec(nodes[root], visited);
}

void Graph::depthFirstTraversalRec(Node* root, std::set<Node*>& visited) {
    std::cout << root->label << std::endl;
    visited.insert(root);

    for (auto&& node : adjacencyList[root]) {
        if (visited.find(node) == visited.end())
            depthFirstTraversalRec(node, visited);
    }
}

void Graph::depthFirstTraversalItr(const std::string& root) {
    // validate the root node
    if (nodes.find(root) == nodes.end())
        throw std::runtime_error("Error: " + root + " node not found");

    // set of visited nodes
    std::set<Node*> visited;

    // create a stack frontier and push root node
    std::stack<Node*> frontier;
    frontier.push(nodes[root]);

    while (!frontier.empty()) {
        // pop one node from the top of the stack
        Node* current = frontier.top();
        frontier.pop();

        // continue if the current node is already visited
        if (visited.find(current) != visited.end())
            continue;

        // visit the current node and add it to the set of visited node
        std::cout << current->label << std::endl;
        visited.insert(current);

        // push all of current's unvisited neighbour into the stack
        for (auto&& neighbour : adjacencyList[current]) {
            if (visited.find(neighbour) == visited.end())
                frontier.push(neighbour);
        }
    }
}

void Graph::breadthFirstTraversal(const std::string& root) {
    // validate the root node
    if (nodes.find(root) == nodes.end())
        throw std::runtime_error("Error: " + root + " node not found");

    // set of visited nodes
    std::set<Node*> visited;

    // create a queue frontier and push root node
    std::queue<Node*> frontier;
    frontier.push(nodes[root]);


    while (!frontier.empty()) {
        // pop one node from the front of the queue
        Node* current = frontier.front();
        frontier.pop();

        // continue if the current node is already visited
        if (visited.find(current) != visited.end())
            continue;

        // visit the current node and add it to the set of visited node
        std::cout << current->label << std::endl;
        visited.insert(current);

        // push all of current's unvisited neighbour into the queue
        for (auto&& neighbour : adjacencyList[current]) {
            if (visited.find(neighbour) == visited.end())
                frontier.push(neighbour);
        }
    }
}

int main() {
    try {
        Graph graph;
        graph.addNode("A");
        graph.addNode("B");
        graph.addNode("C");
        graph.addNode("D");
        graph.addEdge("A", "B");
        graph.addEdge("B", "D");
        graph.addEdge("D", "C");
        graph.addEdge("A", "C");
        // graph.removeEdge("A", "D");
        // graph.removeNode("C");
        graph.print();

        std::cout << "Depth First Traversal (Recursive) : " << std::endl;
        graph.depthFirstTraversalRec("A");

        std::cout << "Depth First Traversal (Iterative) : " << std::endl;
        graph.depthFirstTraversalRec("A");

        std::cout << "Breadth First Traversal : " << std::endl;
        graph.breadthFirstTraversal("A");

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}