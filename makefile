INCLUDE = -Ilib/SDL2/include -IGame/
LINKERS = -Llib/SDL2/lib
LIBS = -lmingw32 -lsdl2main -lsdl2
DEPS = Game/*.cpp

all:
	cls
	g++ $(INCLUDE) $(LINKERS) $(DEPS) main.cpp -o main $(LIBS)
	./main