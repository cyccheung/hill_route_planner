#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Node.hpp"
#include "Planner.hpp"

int main() {
    // Read map details from hilldata file 
    int MAPHEIGHT = 0;
    int MAPWIDTH = 0;
    int STARTX = 0;
    int STARTY = 0;
    int DESTINATIONX = 0;
    int DESTINATIONY = 0;
    int ALTITUDESTEPLOWER = 0;
    int ALTITUDESTEPUPPER = 0;

    std::vector<Node> map;
    std::ifstream hilldata("hilldata");
    if(hilldata.is_open()) {
        std::cout << "Reading input file...\n";
        hilldata >> MAPHEIGHT >> MAPWIDTH >> 
                    STARTX >> STARTY >> 
                    DESTINATIONX >> DESTINATIONY >> 
                    ALTITUDESTEPLOWER >> ALTITUDESTEPUPPER;
        int tempAltitude;
        int tempID = 0;
        while(hilldata >> tempAltitude) {
            Node tempNode(tempAltitude, tempID);
            map.push_back(tempNode);
            tempID++;
        }
        hilldata.close();
    }
    else {
        std::cout << "Unable to open file" << std::endl;
        return 1;
    }

    // Find optimal path and set the parent nodes appropriately
    Planner planner(&map[STARTY * MAPWIDTH + STARTX], &map[DESTINATIONY * MAPWIDTH + DESTINATIONX], MAPHEIGHT, MAPWIDTH);
    std::cout << "Running A*...\n";
    planner.aStar(map);
    // Bactrack from goal node and output optimal path to optimalpath file
    std::vector<int> path;
    std::cout << "Backtracking...\n";
    planner.backtrack(path);
    // Output path into optimalpath file
    std::cout << "Generating optimalpath..." << std::endl;
    std::ofstream optimalPath;
    optimalPath.open("optimalpath");
    for(int i = 0; i < (int)path.size(); ++i) {
        optimalPath << path[i] << ",";
    }
    optimalPath.close();
    return 0;
}