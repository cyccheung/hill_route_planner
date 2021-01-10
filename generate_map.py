# Redirect the output of this python script to hilldata file
# Prints out the map in the following format:
# MAPHEIGHT
# MAPWIDTH
# STARTX
# STARTY
# DESTINATIONX
# DESTINATIONY
# ALTITUDESTEP Lower bound
# ALTITUDESTEP Upper bound
# row 0, col 0
# row 0, col 1
# ...
# row MAPHEIGHT - 1, col MAPWIDTH - 1

import random 

# Dimensions of map to generate
MAPWIDTH = 10
MAPHEIGHT = 10
ALTITUDESTEP = (-4, 8)
STARTPOINT = (5, 6)
DESTINATION = (8, 1)
STARTALTITUDE = 300
map = []

# Generates a random altitude for input row and column given altitude from source
# Then recursively works on adjacent cells
def generateRandomAltitude(sourceAltitude, row, col):
    if row >= 0 and row < MAPHEIGHT and col >= 0 and col < MAPWIDTH:
        if map[row][col] is None:
            map[row][col] = sourceAltitude + random.randint(ALTITUDESTEP[0], ALTITUDESTEP[1])
            generateRandomAltitude(map[row][col], row - 1, col) # Up
            generateRandomAltitude(map[row][col], row + 1, col) # Down
            generateRandomAltitude(map[row][col], row, col - 1) # Left
            generateRandomAltitude(map[row][col], row, col + 1) # Right

def printMap(map):
    for i in range(MAPHEIGHT):
        for j in range(MAPWIDTH):
            print(map[i][j])

if __name__ == "__main__":
    if 0 <= STARTPOINT[0] < MAPWIDTH and 0 <= STARTPOINT[1] < MAPHEIGHT and 0 <= DESTINATION[0] < MAPWIDTH and 0 <= DESTINATION[1] < MAPHEIGHT:
        for latitude in range(MAPHEIGHT):
            tempRow = []
            for longitude in range(MAPWIDTH):
                tempRow.append(None)
            map.append(tempRow)
        # print(map)
        generateRandomAltitude(STARTALTITUDE, STARTPOINT[0], STARTPOINT[1])
        print(MAPHEIGHT)
        print(MAPWIDTH)
        print(STARTPOINT[0])
        print(STARTPOINT[1])
        print(DESTINATION[0])
        print(DESTINATION[1])
        print(ALTITUDESTEP[0])
        print(ALTITUDESTEP[1])
        printMap(map)
    else:
        print("Start point out of range")
