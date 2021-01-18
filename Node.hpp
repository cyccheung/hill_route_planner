/*
    A node object represents one location on the map
    Will be travelling between adjacent nodes in the map
*/

#ifndef NODE_HPP
#define NODE_HPP

#include <limits>
#include <utility>
#include <iostream>

class Node {
public:
    // Constructor - Called when Node object is created
    Node(int altitudeIn, int idIn) {
        altitude = altitudeIn;
        id = idIn;
        gCost = std::numeric_limits<int>::max();    // Initialize gCost to get to node as very large number
        cost = std::numeric_limits<int>::max();     // Initialize cost to get to node as very large number
        parent = nullptr;                           // Don't know which node leads here
        visited = false;
        addedToUnvisited = false;
    }

    // Calculates x and y position of node
    std::pair<int,int> getPosition(int MAPWIDTH) {
        return std::make_pair(id % MAPWIDTH, id / MAPWIDTH);
    }

    // Returns altitude
    int getAltitude() {
        return altitude;
    }

    // Returns gCost
    int getGCost() {
        return gCost;
    }

    // Sets gCost
    void setGCost(int gCostIn) {
        gCost = gCostIn;
    }

    // Returns cost
    int getCost() {
        return cost;
    }

    // Sets cost to get to this node
    void setCost(int costIn) {
        cost = costIn;
    }

    // Get node ID
    int getID() {
        return id;
    }

    // Set node ID
    void setID(int idIn) {
        id = idIn;
    }

    // Get parent
    Node* getParent() {
        return parent;
    }

    // Set parent
    void setParent(Node* parentIn) {
        parent = parentIn;
    }

    // Get visited status
    bool getVisited() {
        return visited;
    }

    // Set visited status
    void setVisited(bool visitedIn) {
        visited = visitedIn;
    }

    // Get addedToUnvisited status
    bool getAddedToUnvisited() {
        return addedToUnvisited;
    }

    // Set addedToUnvisited status
    void setAddedToUnvisited(bool addedToUnvisitedIn) {
        addedToUnvisited = addedToUnvisitedIn;
    }

    // Print out node details
    void print() {
        if(parent == nullptr) {
            std::cout << "Node " << id << " from Node null at " << altitude << "\n";
        }
        else {
            std::cout << "Node " << id << " from Node " << parent->getID() << " at " << altitude << "\n";
        }
    }

private:
    int altitude;
    int gCost;
    int cost;
    int id;
    Node* parent;
    bool visited;
    bool addedToUnvisited;
};

#endif