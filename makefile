INCLUDE = -Isrc/game
LIBS = -lmingw32 -lsdl2main -lsdl2
DEPS = src/game/*.cpp

all:
	cls
	g++ $(INCLUDE) $(LINKERS) $(DEPS) src/main.cpp -o main $(LIBS)
	./main
