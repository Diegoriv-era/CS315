OBJS	= main.o htmlout.o readjson.o
SOURCE	= main.cpp htmlout.cpp readjson.cpp
HEADER	= htmlout.hpp readjson.hpp
OUT	= main
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

htmlout.o: htmlout.cpp
	$(CC) $(FLAGS) htmlout.cpp 

readjson.o: readjson.cpp
	$(CC) $(FLAGS) readjson.cpp 


clean:
	rm -f $(OBJS) $(OUT)
