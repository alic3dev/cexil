PROJECT_NAME=cexil_collision_example

BIN_DIRECTORY=bin

OUT_FILE=$(BIN_DIRECTORY)/$(PROJECT_NAME)

INCLUDE_DIRECTORY=include
OBJECTS_DIRECTORY=objects
SOURCES_DIRECTORY=sources

SOURCE_FILES=$(wildcard $(SOURCES_DIRECTORY)/*.c)
OBJECT_FILES=$(patsubst $(SOURCES_DIRECTORY)/%.c, $(OBJECTS_DIRECTORY)/%.o, $(SOURCE_FILES))

CEXIL_INCLUDE_DIRECTORY=../../include
CEXIL_OBJECT=../../objects/cexil.o

CC=gcc
C_FLAGS=-O3 -I$(INCLUDE_DIRECTORY) -I$(CEXIL_INCLUDE_DIRECTORY) -Wno-gnu-designator

$(OUT_FILE): $(OBJECT_FILES)
	mkdir -p $(BIN_DIRECTORY)
	$(CC) $(C_FLAGS) $^ $(CEXIL_OBJECT) -o $@

$(OBJECTS_DIRECTORY)/%.o: $(SOURCES_DIRECTORY)/%.c
	$(CC) $(C_FLAGS) -c $< -o $@

clean:
	-rm $(OUT_FILE) $(OBJECTS_DIRECTORY)/*.o 2> /dev/null

