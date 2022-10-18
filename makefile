COMPILER=g++

SRC_DIR=src
BUILD_DIR=build

SDLFILE=main_sdl.cpp
ASCIIFILE=main_ascii.cpp
OUT=out
OUT_BUF=$(FILE)

FLAGS=-lSDL2 -lSDL2main 

all:
	@echo "sdl / ascii"
sdl:
	$(COMPILER) $(SRC_DIR)/$(SDLFILE) $(FLAGS)-o $(BUILD_DIR)/$(OUT)
ascii:
	$(COMPILER) $(SRC_DIR)/$(ASCIIFILE) -o $(BUILD_DIR)/$(OUT)
