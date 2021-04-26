// Weighted Undirected Graph

#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <unordered_map>

class WeightedGraph {
private:
    class Edge;
    class Node {
    private:       
        std::string label; // value of the node
        std::vector<Edge*> edges; // edges of the node

    public:
        Node(const std::string& label) :label(label) {}

        // add an edge to the node
        void addEdge(Node* to, float weight) {
            edges.push_back(new Edge(this, to, weight));
        }

        // returns list of edges of the node
        std::vector<Edge*> getEdges() {
            return edges;
        }

        // returns the value of the node
        std::string getlabel() {
            return label;
        }
    };

    class Edge {
    public:
        Node* from;
        Node* to;
        float weight;
        Edge(Node* from, Node* to, float weight) :from(from), to(to), weight(weight) {}
    };

    // a list of all the nodes (use map for fast lookup)
    std::unordered_map<std::string, Node*> nodes;

private:
    class NodeEntry {
    public:
        Node* node;
        float priority; // cost from initial node to given node
        NodeEntry(Node* node, float priority) :node(node), priority(priority) {}

    };

    class CompareDistance {
    public:
        bool operator()(NodeEntry* p1, NodeEntry* p2) {
            // return "true" if "p1" is has higher priority than "p2"
            return p1->priority > p2->priority;
        }
    };

    class CompareWeight {
    public:
        bool operator()(Edge* e1, Edge* e2) {
            // return "true" if "e1" is has lower weight than "e2"
            return e1->weight < e2->weight;
        }
    };

    bool hasCycle(Node*, Node*, std::set<Node*>&);

public:
    void addNode(const std::string&);
    void addEdge(const std::string&, const std::string&, float);
    void print();

    // Dijkstra Algorithm
    int getShortestDistance(const std::string&, const std::string&);
    std::vector<std::string> getShortestPath(const std::string&, const std::string&);

    bool hasCycle();

    // Prim's Algorithm
    WeightedGraph getMinimumSpanningTree();
};

void WeightedGraph::addNode(const  std::string& label) {
    // add new node to list of nodes (map)
    nodes.emplace(label, new Node(label));
}

void WeightedGraph::addEdge(const std::string& from, const std::string& to, float weight) {
    if (nodes.find(from) == nodes.end())
        throw std::runtime_error("Error: " + from + " node not found");
    if (nodes.find(to) == nodes.end())
        throw std::runtime_error("Error: " + to + " node not found");

    // add edges to the node (bidirectional)
    nodes[from]->addEdge(nodes[to], weight);
    nodes[to]->addEdge(nodes[from], weight);
}

void WeightedGraph::print() {
    for (auto&& node : nodes) {
        std::vector<Edge*> edges = node.second->getEdges();

        if (edges.empty())
            std::cout << node.first << " is isolated node." << std::endl;
        else {
            std::cout << node.first << " is connected to [ ";
            for (auto& i : edges) {
                std::cout << i->from->getlabel() << "->" << i->to->getlabel()
                    << " with weight " << i->weight << ", ";
            }
            std::cout << "\b\b ]" << std::endl;
        }
    }
};

int WeightedGraph::getShortestDistance(const std::string& from, const std::string& to) {
    // validate the  node
    if (nodes.find(from) == nodes.end())
        throw std::runtime_error("Error: " + from + " node not found");
    if (nodes.find(to) == nodes.end())
        throw std::runtime_error("Error: " + to + " node not found");

    // initialization with distance=0 for 'from' node
    // initialization of distance=MAXVALUE for other nodes
    std::unordered_map<Node*, float> distances;
    for (auto&& node : nodes) {
        distances[node.second] = std::numeric_limits<float>::max();
    }
    distances[nodes[from]] = 0;

    // set of visited node (BFS)
    std::set<Node*> visited;

    // create a priority queue frontier and push initial node
    std::priority_queue<NodeEntry*, std::vector<NodeEntry*>, CompareDistance> frontier;
    frontier.push(new NodeEntry(nodes[from], 0));

    while (!frontier.empty()) {
        // pop one node from the front of the queue
        Node* current = frontier.top()->node;
        frontier.pop();

        // add it to the set of visited node
        visited.insert(current);

        for (auto&& edge : current->getEdges()) {
            // continue if the neighbour node is already visited
            if (visited.find(edge->to) != visited.end())
                continue;

            // calculate new distance of neighbour node (Relaxation)
            float newDistance = distances[edge->from] + edge->weight;

            // update if newdistance is less than initialized distance
            if (newDistance < distances[edge->to]) {
                distances[edge->to] = newDistance;

                // push updated neighbour into the queue
                frontier.push(new NodeEntry(edge->to, newDistance));
            }
        }
    }

    // return the distance of target node from initial node
    return distances[nodes[to]];
}

std::vector<std::string> WeightedGraph::getShortestPath(
    const std::string& from, const std::string& to) {

    // validate the  node
    if (nodes.find(from) == nodes.end())
        throw std::runtime_error("Error: " + from + " node not found");
    if (nodes.find(to) == nodes.end())
        throw std::runtime_error("Error: " + to + " node not found");

    // initialization with distance=0 for 'from' node
    // initialization of distance=MAXVALUE for other nodes
    std::unordered_map<Node*, float> distances;
    for (auto&& node : nodes) {
        distances[node.second] = std::numeric_limits<float>::max();
    }
    distances[nodes[from]] = 0;

    // key:nextNode, value:currentNode
    std::unordered_map<Node*, Node*> previousNodes;

    // set of visited node (BFS)
    std::set<Node*> visited;

    // create a priority queue frontier and push initial node
    std::priority_queue<NodeEntry*, std::vector<NodeEntry*>, CompareDistance> frontier;
    frontier.push(new NodeEntry(nodes[from], 0));

    while (!frontier.empty()) {
        // pop one node from the front of the queue
        Node* current = frontier.top()->node;
        frontier.pop();

        // add it to the set of visited node
        visited.insert(current);

        for (auto&& edge : current->getEdges()) {
            // continue if the neighbour node is already visited
            if (visited.find(edge->to) != visited.end())
                continue;

            // calculate new distance of neighbour node (Relaxation)
            float newDistance = distances[edge->from] + edge->weight;

            // update if newdistance is less than initialized distance
            if (newDistance < distances[edge->to]) {
                distances[edge->to] = newDistance;

                // path from current node to neighbour node
                previousNodes[edge->to] = current;

                // push updated neighbour into the queue
                frontier.push(new NodeEntry(edge->to, newDistance));
            }
        }
    }

    // push the previous nodes to the stack
    std::stack<Node*> stack;
    stack.push(nodes[to]);
    Node* previous = previousNodes[nodes[to]];
    while (previous != nullptr) {
        stack.push(previous);
        previous = previousNodes[previous];
    }

    // pop the stack to get path in correct order
    std::vector<std::string> path;
    while (!stack.empty()) {
        path.push_back(stack.top()->getlabel());
        stack.pop();
    }

    // return the shortest path of target node from initial node
    return path;
}

bool WeightedGraph::hasCycle() {
    std::set<Node*> visited;

    // depth first traversal on each node of the graph
    for (auto&& node : nodes) {

        // returns true if node is not visited and has cycle 
        if (visited.find(node.second) == visited.end()) {
            if (hasCycle(node.second, nullptr, visited))
                return true;
        }
    }

    // no cycle is found in graph
    return false;
}

bool WeightedGraph::hasCycle(Node* node, Node* parent, std::set<Node*>& visited) {
    // add node to visited set
    visited.insert(node);

    for (auto&& edge : node->getEdges()) {
        // eg. A-B (i.e. A->B, B->A) (not a cycle)  
        // A (initial node) is neighbour and parent of B)
        if (edge->to == parent)
            continue;

        // returns true if neighbour is in visited set (cycle detected)
        if (visited.find(edge->to) != visited.end())
            return true;

        // recursively check for all neighbours
        if (hasCycle(edge->to, node, visited))
            return true;
    }

    // no cycle found in node and its neighbours
    return false;
}


WeightedGraph WeightedGraph::getMinimumSpanningTree() {
    WeightedGraph tree;

    // return if graph is empty
    if (nodes.empty())
        return tree;

    // create a priority queue of edges (connected)
    std::priority_queue<Edge*, std::vector<Edge*>, CompareWeight> edges;

    // push all edges of starting node to queue
    Node* startNode = nodes.begin()->second;
    for (auto&& edge : startNode->getEdges()) {
        edges.push(edge);
    }

    // add the starting node to tree
    tree.addNode(startNode->getlabel());

    // return if startNode is isolated node 
    if (edges.empty())
        return tree;

    // repeat unless all nodes of graph are in the tree 
    while (tree.nodes.size() < nodes.size()) {

        // get edge with minimum weight
        Edge* minEdge = edges.top();
        edges.pop();

        Node* nextNode = minEdge->to;

        // continue if nextNode is already in tree
        if (tree.nodes.find(nextNode->getlabel()) != tree.nodes.end())
            continue;

        // add nextNode and its edge to tree
        tree.addNode(nextNode->getlabel());
        tree.addEdge(minEdge->from->getlabel(),
            nextNode->getlabel(),
            minEdge->weight);

        // push all edges of nextNode connecting unvisited node 
        for (auto&& edge : nextNode->getEdges()) {
            if (tree.nodes.find(edge->to->getlabel()) == tree.nodes.end())
                edges.push(edge);
        }
    }
    return tree;
}


int main() {
    try {
        WeightedGraph graph;
        graph.addNode("A");
        graph.addNode("B");
        graph.addNode("C");
        graph.addNode("D");
        graph.addNode("E");
        graph.addEdge("A", "B", 2);
        graph.addEdge("A", "C", 3);
        graph.addEdge("B", "D", 3);
        graph.addEdge("A", "D", 30);
        graph.print();


        /******************** Shortest Path Algorithm (Dijkstra) ********************/
        std::cout << "\nShortest Path Algorithm (Dijkstra) " << std::endl;
        std::string fromNode = "A";
        std::string toNode = "D";

        std::cout << "Shortest distance from '" + fromNode + "' to '" + toNode + "' : ";
        float shortestDistance = graph.getShortestDistance("A", "D");
        std::cout << shortestDistance << std::endl;

        std::cout << "Shortest path     from '" + fromNode + "' to '" + toNode + "' : ";
        std::vector<std::string> shortestPath = graph.getShortestPath("A", "D");
        for (auto&& path : shortestPath) {
            std::cout << path << " ";
        }
        std::cout << std::endl;


        /******************** Cycle Detection (Undirected Graph) ********************/
        std::cout << "\nCycle Detection (Undirected Graph) " << std::endl;
        if (graph.hasCycle())
            std::cout << "Graph is cyclic." << std::endl;
        else
            std::cout << "Graph is acyclic." << std::endl;


        /******************** Minimum Spanning Tree (Prim's Algorithm) ********************/
        std::cout << "\nMinimum Spanning Tree (Prim's Algorithm)" << std::endl;
        std::cout << "========================================\n";
        WeightedGraph graph1;
        graph1.addNode("A");
        graph1.addNode("B");
        graph1.addNode("C");
        graph1.addNode("D");
        graph1.addEdge("A", "B", 3);
        graph1.addEdge("B", "D", 4);
        graph1.addEdge("C", "D", 5);
        graph1.addEdge("A", "C", 1);
        graph1.addEdge("B", "C", 2);
        std::cout << "\nGraph" << std::endl;
        std::cout << "=====\n";
        graph1.print();
        std::cout << "\nTree" << std::endl;
        std::cout << "====\n";
        WeightedGraph tree = graph1.getMinimumSpanningTree();
        tree.print();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
