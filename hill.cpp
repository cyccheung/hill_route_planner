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
        while(hilldata >> tempAltitude) {
            Node tempNode(tempAltitude);
            map.push_back(tempNode);
        }
        hilldata.close();
    }
    else {
        std::cout << "Unable to open file" << std::endl;
        return 1;
    }

    // Find optimal path and set the parent nodes appropriately
    Planner planner(&map[STARTY * MAPWIDTH + STARTX], &map[DESTINATIONY * MAPWIDTH + DESTINATIONX], MAPHEIGHT, MAPWIDTH);
    planner.aStar(map);
    // Bactrack from goal node and output optimal path to optimalpath file
    std::vector<int> path;
    planner.backtrack(path);
    // Output path into optimalpath file
    std::ofstream optimalPath;
    optimalPath.open("optimalpath");
    for(int i = 0; i < path.size(); ++i) {
        optimalPath << path[i] << ",";
    }
    optimalPath.close();
    return 0;
}