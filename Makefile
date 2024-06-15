FLAGS = -O -Wall -Werror -Wshadow

all:
	c++ main.cpp -lSDL2 $(FLAGS)
