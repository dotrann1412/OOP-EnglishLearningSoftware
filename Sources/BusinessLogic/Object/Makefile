MAKEFLAGS += --silent

cc = g++
cflags = -std=c++17 -g -c

User.o : User.cpp User.h 
	$(cc) $(cflags) -o User.o User.cpp

UserHandle.o : UserHandle.cpp UserHandle.h 
	$(cc) $(cflags) -o UserHandle.o UserHandle.cpp

main.o : main.cpp 
	$(cc) $(cflags) -o main.o main.cpp

all: main.o User.o UserHandle.o 
	$(cc) -std=c++17 -g -o main main.o User.o UserHandle.o 

clean:
	rm -f -- main -f -- *.o -f -- *.exe -f -- *.h.gch
