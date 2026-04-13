CC = g++
CXXFLAGS = -std=c++11 -g -Wall -lpthread

INCLUDE_FOLDER = ./include/
BIN_FOLDER = ./bin/
OBJ_FOLDER = ./obj/
SRC_FOLDER = ./src/

TARGET = run
SRC = $(wildcard $(SRC_FOLDER)*.cpp)
OBJ = $(patsubst $(SRC_FOLDER)%.cpp, $(OBJ_FOLDER)%.o, $(SRC))

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -I $(INCLUDE_FOLDER)

all: build

run: $(TARGET)
	$(BIN_FOLDER)$(TARGET)

build: $(OBJ)
	$(CC) $(CXXFLAGS) -o $(BIN_FOLDER)$(TARGET) $(OBJ)

clean:
	rm -rf $(OBJ_FOLDER)* $(BIN_FOLDER)*

windows_clean:
	del /S .\bin\*.exe
	del /S .\obj\*.o