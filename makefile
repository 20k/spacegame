# This needs to be done much better

PWD = $(shell pwd)

CC = g++
OBJS = $(patsubst %.cpp,%.o,$(wildcard **/*.cpp *.cpp))

DEBUG = -g
PNAME = game
INCLUDES = -I$(PWD)/headers

LUA = -llua -ldl
CFLAGS = -Wall $(DEBUG)
LFLAGS = -Wall -lsfml-graphics -lsfml-window -lsfml-system $(DEBUG)

# -Llua/lib -llua -llualib

all: build

debug: build
	insight $(PNAME)

build: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(PNAME) $(LUA)

clean:
	\rm **/*.o *.o *~ $(PNAME)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

