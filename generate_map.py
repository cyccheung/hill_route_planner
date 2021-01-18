# Redirect the output of this python script to hilldata file
# Prints out the map in the following format:
# MAPHEIGHT
# MAPWIDTH
# STARTX
# STARTY
# DESTINATIONX
# DESTINATIONY
# row 0, col 0
# row 0, col 1
# ...
# row MAPHEIGHT - 1, col MAPWIDTH - 1

import random 
from perlin_noise import PerlinNoise

# Dimensions of map to generate
MAPWIDTH = 30
MAPHEIGHT = 30
STARTPOINT = (1, 10)
DESTINATION = (25, 15)
RANDOMSEED = 9
ALTITUDEOFFSET = 100
map = []

def printMap(map):
    for i in range(MAPHEIGHT):
        for j in range(MAPWIDTH):
            print(int((map[i][j] * 1000.0)) + ALTITUDEOFFSET)

if __name__ == "__main__":
    print(MAPHEIGHT)
    print(MAPWIDTH)
    print(STARTPOINT[0])
    print(STARTPOINT[1])
    print(DESTINATION[0])
    print(DESTINATION[1])
    if 0 <= DESTINATION[0] < MAPWIDTH and 0 <= DESTINATION[1] < MAPHEIGHT and 0 <= STARTPOINT[0] < MAPWIDTH and 0 <= STARTPOINT[1] < MAPHEIGHT:
        noise = PerlinNoise(octaves=2, seed=RANDOMSEED)
        xpix, ypix = MAPWIDTH, MAPHEIGHT
        map = [[noise([i/xpix, j/ypix]) for j in range(xpix)] for i in range(ypix)]
        printMap(map)
    else:
        print("Start point out of range")