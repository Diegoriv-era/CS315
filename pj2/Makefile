OBJS	= main.o Worm.o Screen.o
SOURCE	= main.cpp Worm.cpp Screen.cpp
HEADER	= Worm.hpp Screen.hpp Cell.hpp
OUT	= worm
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -lncurses -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

Worm.o: Worm.cpp
	$(CC) $(FLAGS) Worm.cpp 

Screen.o: Screen.cpp
	$(CC) $(FLAGS) Screen.cpp 


clean:
	rm -f $(OBJS) $(OUT)