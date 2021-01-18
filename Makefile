CXX	= g++
SOURCES	= $(wildcard *.cpp)
HEADERS = $(wildcard *.hpp)
HILLGENERATE = generate_map.py
PATHPLOT = pathplot.py
HILLDATA = hilldata
OPTIMALPATH = optimalpath

#------------- Changes below ---------------
CXXFLAGS = -Wall
EXEC = hill.out
#------------- Changes above ---------------
all: $(EXEC) generate run plot

$(EXEC): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(HEADERS) $(SOURCES) -o $(EXEC)

plot: $(PATHPLOT)
	python $(PATHPLOT)

run: $(EXEC)
	./$(EXEC)

generate: $(HILLGENERATE)
	python $(HILLGENERATE) > $(HILLDATA)

clean:
	rm $(EXEC) $(HILLDATA) $(OPTIMALPATH)

.PHONY: clean