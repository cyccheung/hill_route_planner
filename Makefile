CXX	= g++
SOURCES	= $(wildcard *.cpp)
HEADERS = $(wildcard *.hpp)
HILLGENERATE = generate_map.py
HILLDATA = hilldata

#------------- Changes below ---------------
CXXFLAGS = -Wall
EXEC = hill.out
#------------- Changes above ---------------
all: $(EXEC) run

$(EXEC): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(HEADERS) $(SOURCES) -o $(EXEC)

run: $(EXEC)
	./$(EXEC)

generate: $(HILLGENERATE)
	python3 $(HILLGENERATE) > hilldata

clean:
	rm $(EXEC)

.PHONY: clean