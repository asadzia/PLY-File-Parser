####################################################################
# Author: Asad Zia
#####################################################################

#[Coloring]
NO_COLOR=\033[0m
OK_COLOR=\033[36;01m
COMPILE_COLOR=\033[45;33;01m
STATEMENT_COLOR=\033[46;33;01m

CC=g++
CFLAGS=-Wall -W -std=c++0x -c -g
SOURCES=$(wildcard *.cpp)
OBJECTS_AUX=$(SOURCES:.cpp=.o)
OBJECTS=$(subst $(SRC), $(BIN), $(OBJECTS_AUX))
EXECUTABLE=make

all: $(EXECUTABLE)

scanner:@echo "$(COMPILE_COLOR)|----- Finished Compiling -----|$(NO_COLOR)"
	@echo "$(NO_COLOR)                            $(NO_COLOR)" 
	Main.o Triangle.o Colour.o Point.o ParsePLY.o Matrix.o
	g++ Main.o Triangle.o Colour.o Point.o Matrix.o ParsePLY.o  -o hello

Main.o: Main.cpp
	g++ -c Main.cpp

Triangle.o: Triangle.cpp
	g++ -c Triangle.cpp

Point.o: Point.cpp
	g++ -c Point.cpp

Matrix.o: Matrix.cpp
	g++ -c Matrix.cpp

ParsePLY.o: ParsePLY.cpp
	g++ -c ParsePLY.cpp

Colour.o: Colour.cpp
	g++ -c Colour.cpp

clean:
	rm -rf *.o make

$(EXECUTABLE): $(OBJECTS)
	@echo "$(COMPILE_COLOR)|----- Finished Compiling -----|$(NO_COLOR)"
	@echo "$(NO_COLOR)                            $(NO_COLOR)"
	@echo "$(COMPILE_COLOR)|-- Building. --|$(NO_COLOR)"
	$(CC) *.o -o $@
	@echo "$(COMPILE_COLOR)|--------------------------|$(NO_COLOR)"
run:
	./scanner
