#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
    // Read width, height, and altitude data from hilldata file 
    int MAPHEIGHT = 0;
    int MAPWIDTH = 0;
    std::vector<int> map;
    std::ifstream hilldata("hilldata");
    if(hilldata.is_open()) {
        hilldata >> MAPHEIGHT >> MAPWIDTH;
        int tempAltitude;
        while(hilldata >> tempAltitude) {
            map.push_back(tempAltitude);
        }
        hilldata.close();
    }
    else {
        std::cout << "Unable to open file";
    }


    return 0;
}