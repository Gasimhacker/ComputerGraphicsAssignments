SRC ?= ./src/Assignment_2/Assign2-p3.cpp
OUT ?= main

all:
	g++ $(SRC) -o $(OUT) -I".\include" -L".\lib\x64" -lfreeglut -lopengl32 -lglu32