OBJS	= main.o project3.o
SOURCE	= main.cpp project3.cpp
HEADER	= project3.hpp
OUT	= project3
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

project3.o: project3.cpp
	$(CC) $(FLAGS) g++ project3.cpp 


clean:
	rm -f $(OBJS) $(OUT)