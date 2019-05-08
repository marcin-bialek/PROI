CC := g++
ARGS := -std=c++11 -Wall -Wextra -pedantic -I include
SRC := $(wildcard src/*.cpp)
TARGET := bin/Multiset


all: $(SRC)
	mkdir -p bin
	$(CC) $(ARGS) -o $(TARGET) $^ 
