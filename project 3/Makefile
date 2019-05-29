CC := g++
ARGS := -std=c++11 -Wall -Wextra -pedantic -I include -I "include/Event Emmiter" -I include/Json -I include/Pharmacy
SRC := $(wildcard src/*.cpp)
TARGET := bin/PharmacySimulator


all: $(SRC)
	mkdir -p bin
	$(CC) $(ARGS) -o $(TARGET) $^ 
