// Directed Graph

#include <iostream>
#include <exception>
#include <string>
#include <unordered_map>
#include <stack>
#include <queue>
#include <set>
#include <list>

class DiGraph {
private:
    class Node {
    public:
        std::string label;
        Node(const std::string& label) :label(label) {}
    };

    // use map for fast lookup instead of a list of nodes
    std::unordered_map<std::string, Node*> nodes;

    // list of lists of adjacent node
    // eg. Node A = [B,C,D] where, B,C,D are adjacent to A
    std::unordered_map<Node*, std::list<Node*>> adjacencyList;

private:
    void depthFirstTraversalRec(Node*, std::set<Node*>&);

    void TopologicalSort(Node*, std::set<Node*>&, std::stack<Node*>&);

    bool hasCycle(Node*, std::set<Node*>&, std::set<Node*>&, std::set<Node*>&);

public:
    void addNode(const std::string&);
    void addEdge(const std::string&, const std::string&);

    void removeNode(const std::string&);
    void removeEdge(const std::string&, const std::string&);

    // Depth First Traversals
    void depthFirstTraversalRec(const std::string&);
    void depthFirstTraversalItr(const std::string&);

    // Breadth First Traversal
    void breadthFirstTraversal(const std::string&);

    // Topological Sorting of Directed Acyclic DiGraph (DAG)
    std::list<std::string> TopologicalSort();

    bool hasCycle();

    void print();
};

void DiGraph::addNode(const  std::string& label) {
    Node* new_node = new Node(label);

    // add new node to list of nodes (map)
    nodes.emplace(label, new_node);
}

void DiGraph::addEdge(const std::string& from, const std::string& to) {
    if (nodes.find(from) == nodes.end())
        throw std::runtime_error("Error: " + from + " node not found");
    if (nodes.find(to) == nodes.end())
        throw std::runtime_error("Error: " + to + " node not found");

    // add "to node" to "from node" list as its adjacent node
    adjacencyList[nodes[from]].push_back(nodes[to]);
}

void DiGraph::removeNode(const std::string& node) {
    if (nodes.find(node) == nodes.end())
        return;

    // remove all connections of node
    // eg. A = [B, C, D] B = [A, C, F] C=[A, F]
    // Here, remove node C from all occurrences
    for (auto&& n : adjacencyList) {
        n.second.remove(nodes[node]);
    }

    // remove node (eg. node C) from adjacenctList 
    adjacencyList.erase(nodes[node]);

    // remove node (eg. node C) from list of nodes
    nodes.erase(node);
}

void DiGraph::removeEdge(const std::string& from, const std::string& to) {
    if (nodes.find(from) == nodes.end() || nodes.find(to) == nodes.end())
        return;

    adjacencyList[nodes[from]].remove(nodes[to]);
}

void DiGraph::print() {
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

void DiGraph::depthFirstTraversalRec(const std::string& root) {
    std::set<Node*> visited;
    if (nodes.find(root) == nodes.end())
        throw std::runtime_error("Error: " + root + " node not found");

    depthFirstTraversalRec(nodes[root], visited);
}

void DiGraph::depthFirstTraversalRec(Node* root, std::set<Node*>& visited) {
    std::cout << root->label << std::endl;
    visited.insert(root);

    for (auto&& node : adjacencyList[root]) {
        if (visited.find(node) == visited.end())
            depthFirstTraversalRec(node, visited);
    }
}

void DiGraph::depthFirstTraversalItr(const std::string& root) {
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

void DiGraph::breadthFirstTraversal(const std::string& root) {
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

std::list<std::string> DiGraph::TopologicalSort() {
    std::stack<Node*> stack;
    std::set<Node*> visited;
    std::list<std::string> sorted;

    // depth first traversal on each node of the graph
    for (auto&& node : nodes) {
        TopologicalSort(node.second, visited, stack);
    }

    // pop the stack to get ordered nodes
    while (!stack.empty()) {
        sorted.emplace_back(stack.top()->label);
        stack.pop();
    }

    return sorted;
}

void DiGraph::TopologicalSort(Node* node, std::set<Node*>& visited, std::stack<Node*>& stack) {
    // check if node is already visited
    if (visited.find(node) != visited.end())
        return;

    // If not, visit the node
    visited.insert(node);

    // then, depth first traversal on node
    for (auto&& neighbour : adjacencyList[node]) {
        TopologicalSort(neighbour, visited, stack);
    }

    // push the deepest node without outgoing edges or 
    // node with neighbours already explored to stack
    stack.push(node);
}

bool DiGraph::hasCycle() {
    // insert nodes of graph into all set
    std::set<Node*> all;
    for (auto&& node : nodes) {
        all.insert(node.second);
    }

    std::set<Node*> visiting;
    std::set<Node*> visited;

    while (!all.empty()) {
        // get a node from all set
        Node* current = *all.begin(); // *itr

        // immediately returns true if cycle is found
        if (hasCycle(current, all, visiting, visited))
            return true;
    }

    // no cycle is found in graph
    return false;
}

bool DiGraph::hasCycle(Node* node, std::set<Node*>& all,
    std::set<Node*>& visiting, std::set<Node*>& visited) {
    // remove node form all set and add it to visiting set
    all.erase(node);
    visiting.insert(node);

    for (auto&& neighbour : adjacencyList[node]) {

        // continue if neighbour node is already visited
        if (visited.find(neighbour) != visited.end())
            continue;

        // if neighbour is in visiting set, we have a cycle
        if (visiting.find(neighbour) != visiting.end())
            return true;

        // recursively check for all neighbours
        if (hasCycle(neighbour, all, visiting, visited))
            return true;
    }
    // remove node form visiting set and add it to visited set
    visiting.erase(node);
    visited.insert(node);

    // no cycle found in node and its neighbours
    return false;
}

int main() {
    try {
        DiGraph graph;
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

        /******************** Directed Acyclic Graph ********************/
        DiGraph dag;
        dag.addNode("A");
        dag.addNode("B");
        dag.addNode("C");
        dag.addNode("D");

        dag.addEdge("A", "B");
        dag.addEdge("A", "C");
        dag.addEdge("B", "D");
        dag.addEdge("C", "D");

        /******************** Topological Sorting ********************/
        std::cout << "Topological Sort : " << std::endl;
        std::list<std::string> sorted = dag.TopologicalSort();
        for (auto && node : sorted){
            std::cout << node << std::endl;
        }

        /******************** Cycle Detection (Directed Graph) ********************/
        std::cout << "\nCycle Detection (Directed Graph) " << std::endl;
        if (dag.hasCycle())
            std::cout << "DiGraph is cyclic." << std::endl;
        else
            std::cout << "DiGraph is acyclic." << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}