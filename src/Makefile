# 

CCC	= g++ -std=c++11 -Wall -Wextra -pedantic
LFLAGS	= -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

all: main.cc Game.o Renderer.o
	$(CCC) -o main main.cc Game.o Renderer.o $(LFLAGS)

Game.o: Game.cc Game.h
	$(CCC) -c Game.cc

Renderer.o: Renderer.cc Renderer.h
	$(CCC) -c Renderer.cc

clean:
	@ \rm -rf *.o *.gch core
zap:
	@ \rm -f main *~
