# Takes hilldata and optimalpath files
# Plots 3D surface of map in green
# Plots start and end points in red
# Plots route taken in blue

import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import numpy as np

startPoint = []
destination = []
map = []
path = []

# Read in map data
print("Reading hilldata...")
mapFile = open("hilldata", "r")
mapContent = mapFile.read()
map = mapContent.split("\n")
mapFile.close()
map.remove('')
map = [int(i) for i in map]
# print(map)

# Get details from map data
MAPHEIGHT = map[0]
MAPWIDTH = map[1]
STARTX = map[2]
STARTY = map[3]
DESTINATIONX = map[4]
DESTINATIONY = map[5]

# Read in path data
print("Reading optimalpath...")
pathFile = open("optimalpath", "r")
pathContent = pathFile.read()
path = pathContent.split("\n")
pathFile.close()

# Plot 3D surface of map
X, Y = np.meshgrid(np.arange(MAPWIDTH), np.arange(MAPHEIGHT))
fig = plt.figure()
ax = fig.add_subplot(1,1,1, projection='3d')
Z = np.reshape(np.array(map[6:]), (MAPWIDTH, MAPHEIGHT))
ax.plot_surface(X, Y, Z, color='g')

# TODO: Plot start and destination
pointsX = np.array([STARTX, DESTINATIONX])
pointsY = np.array([STARTY, DESTINATIONY])
pointsZ = np.array([map[STARTY * MAPWIDTH + STARTX] + 10, map[DESTINATIONY * MAPWIDTH + DESTINATIONX] + 10])
print(pointsX)
print(pointsY)
print(pointsZ)
ax.scatter(pointsX, pointsY, pointsZ, color='r', s=50)
# TODO: Plot optimal route
plt.show()