INCLUDES ?= -I ./include/ \
-I C:/Programs/SMFL/SFML-2.6.0-gcc/include/
BUILD = ./build/
SOURCES = ./src/
BINARIES = ./bin/
FLAGS = -g -Wall -Wextra -fdiagnostics-color=always #-fsanitize=address -O3
CC = g++

OBJECTS = ${BUILD}chess_board.o \
${BUILD}chessboard_window.o \
${BUILD}chess_pieces.o \
${BUILD}chess_utility.o \
${BUILD}chess_clock.o \
${BUILD}chess_history.o \
${BUILD}chess_mouse.o \
${BUILD}chess_text.o

LIBRARY_DIR ?=	-L C:/Programs/SMFL/SFML-2.6.0-gcc/lib \
				 
LINKED_LIBRARIES = -lsfml-window -lsfml-system -lsfml-graphics

# ${OBJECTS} ${LIBRARY_DIR} ${LINKED_LIBRARIES}
all: ${OBJECTS}
	if not exist "bin" mkdir bin
	if not exist "build" mkdir build
	${CC} ${FLAGS} ${INCLUDES} ${OBJECTS} ${SOURCES}main.cpp ${LIBRARY_DIR} ${LINKED_LIBRARIES} -o ${BINARIES}main
	mingw32-make run

# Build all - wildcards
${BUILD}%.o:${SOURCES}%.cpp
	${CC} ${FLAGS} ${INCLUDES} -c $< -o $@

# Clean build folder if needed
clean:
	del "${BUILD}"

# Run with file
RUN_FILE = main
EXT = exe
run:
	${BINARIES}${RUN_FILE}.${EXT}

# ------test section----------
test:
	${CC} ${INCLUDES} ${TESTING}test.cpp -o ${TESTING}test
	${TESTING}test
