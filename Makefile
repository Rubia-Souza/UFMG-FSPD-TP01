CC = g++
CPPFLAGS = -std=c++11 -g -Wall
LIBS = -pthread

INCLUDE_FOLDER = ./include/
SRC_FOLDER = ./src/
BIN_FOLDER = ./bin/
OBJ_FOLDER = ./obj/

TARGET = app
SRC = $(wildcard $(SRC_FOLDER)*.cpp)
OBJ = $(patsubst $(SRC_FOLDER)%.cpp, $(OBJ_FOLDER)%.o, $(SRC))

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@ -I $(INCLUDE_FOLDER) $(LIBS)

all: build

.PHONY: run
run: $(TARGET)
	$(BIN_FOLDER)$(TARGET)

$(TARGET): build

build: $(OBJ)
	$(CC) $(CPPFLAGS) -o $(BIN_FOLDER)$(TARGET) $(OBJ) $(LIBS)

clean:
	rm -rf $(OBJ_FOLDER)* $(BIN_FOLDER)*

windows_clean:
	del /S .\bin\*.exe
	del /S .\obj\*.o