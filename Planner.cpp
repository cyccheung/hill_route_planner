#include <cmath>
#include "Planner.hpp"

Planner::Planner(Node* startNodePtr, Node* destinationNodePtr, int MAPHEIGHTIN, int MAPWIDTHIN) {
    startNode = startNodePtr;
    destinationNode = destinationNodePtr;
    MAPWIDTH = MAPWIDTHIN;
    MAPHEIGHT = MAPHEIGHTIN;
    unvisited.push(startNode);
}

bool Planner::aStar(std::vector<Node> &map) {
    Node* currentNode = startNode;
    currentNode->setVisited(true);
    // Keep searching as long as there are nodes left to visit
    while(!unvisited.empty()) {
        // Add adjacent nodes to unvisited
        addAdjacent(map, currentNode, MAPHEIGHT, MAPWIDTH);
        // Set the next node's parent as the current node
        unvisited.top()->setParent(currentNode);
        // Take the node with the lowest cost as next current
        currentNode = unvisited.top();
        unvisited.pop();
        // If we have reached the goal, return
        if(currentNode == destinationNode) {
            return true;
        }
    }
    // If unvisited PQ is empty before destination is found, then there is no path from start to destination
    return false;
}

void Planner::backtrack(std::vector<int> &path) {
    Node* tempNodePtr;
    int debugIterations = 0;
    // Keep backtracking until we reach the start
    while(tempNodePtr != startNode && debugIterations < 1000) {
        path.push_back(tempNodePtr->getID());
        tempNodePtr = tempNodePtr->getParent();
        debugIterations++;
    }
    path.push_back(tempNodePtr->getID());   // Add start node to path
}

double Planner::calculateGCost(Node* node, Node* parentNode) {
    int altitudeDifference = node->getAltitude() - parentNode->getAltitude();
    int tempEffort = pow(altitudeDifference, 2);
    if(altitudeDifference > 0) {
        tempEffort *= 10;
    }
    return tempEffort + parentNode->getGCost();
}

double Planner::calculateHCost(Node* node) {
    std::pair<int,int> destinationPos = destinationNode->getPosition(MAPWIDTH);
    std::pair<int,int> nodePos = node->getPosition(MAPWIDTH);
    return 10 * ALTITUDESTEPUPPER * sqrt(pow(destinationPos.first - nodePos.first, 2) + pow(destinationPos.second - nodePos.second, 2));
}

void Planner::addAdjacent(std::vector<Node> &map, Node* currentNode, int MAPHEIGHT, int MAPWIDTH) {
    std::vector<int> adjacentIDs;
    // North
    if(currentNode->getID() - MAPWIDTH >= 0) {
        adjacentIDs.push_back(currentNode->getID() - MAPWIDTH);  
    }
    // South
    if(currentNode->getID() + MAPWIDTH < (int)map.size()) {
        adjacentIDs.push_back(currentNode->getID() + MAPWIDTH);  
    }
    // East
    if(currentNode->getID() % MAPWIDTH < MAPWIDTH - 1) {
        adjacentIDs.push_back(currentNode->getID() + 1);  
    }
    // West
    if(currentNode->getID() % MAPWIDTH > 0) {
        adjacentIDs.push_back(currentNode->getID() - 1);
    }

    // Add all adjacent nodes using their IDs
    for(int i = 0; i < (int)adjacentIDs.size(); ++i) {
        int updatedCost = calculateGCost(&map[adjacentIDs[i]], currentNode) + calculateHCost(&map[adjacentIDs[i]]);
        // If cost from going to this node is lower than previously found cost, update the cost
        if(updatedCost < map[adjacentIDs[i]].getCost()) {
            map[adjacentIDs[i]].setGCost(calculateGCost(&map[adjacentIDs[i]], currentNode));
            map[adjacentIDs[i]].setCost(updatedCost);
        }
        // Only add if not a water tile (altitude >= 0) and tile is not visited and not already in unvisited
        if( map[adjacentIDs[i]].getAltitude() >= 0 && 
            !map[adjacentIDs[i]].getVisited() && 
            !map[adjacentIDs[i]].getAddedToUnvisited()) {
            map[adjacentIDs[i]].setVisited(true);
            map[adjacentIDs[i]].setAddedToUnvisited(true);
            unvisited.push(&map[adjacentIDs[i]]);
        }
    }
}
