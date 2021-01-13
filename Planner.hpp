/*
    Object to plan the route
*/

#include <queue>
#include <vector>
#include "Node.hpp"

// Custom comparator class to compare nodes
class Compare {
public:
    bool operator() (Node* a, Node* b) {
        return a->getCost() < b->getCost();
    }
};

class Planner {
public:
    // Sets start and destination nodes
    // Adds the start node to unvisited
    Planner(Node* startNodePtr, Node* destinationNodePtr, int MAPHEIGHTIN, int MAPWIDTHIN);

    // Plans route using A*
    // Returns if path is found
    bool aStar(std::vector<Node> &map);

    // Backtracks from input node to start node
    void backtrack(std::vector<int> &path);

private:
    // Calculate cost to get from start node to node
    // Trace back to start to figure out cost to get here
    double calculateGCost(Node* node, Node* parentNode);

    // Calculate cost to get from node to destination node
    // Returns Euclidean distance between node and destination
    // NOTE: Heuristic is not admissable
    double calculateHCost(Node* node);

    // Adds nodes adjacent to currentNode to unvisited
    // Updates adjacent nodes' cost if a lower cost to it can be made through currentNode
    void addAdjacent(std::vector<Node> &map, Node* currentNode, int MAPHEIGHT, int MAPWIDTH);

    std::priority_queue<Node*, std::vector<Node*>, Compare> unvisited;
    Node* startNode;
    Node* destinationNode;
    int MAPHEIGHT;
    int MAPWIDTH;
    int STARTX;
    int STARTY;
    int DESTINATIONX;
    int DESTINATIONY;
    int ALTITUDESTEPLOWER;
    int ALTITUDESTEPUPPER;
};