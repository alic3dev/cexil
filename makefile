PROJECT_NAME=cexil

INCLUDE_DIRECTORY=include
OBJECTS_DIRECTORY=objects
SOURCES_DIRECTORY=sources
EXAMPLES_DIRECTORY=examples

OUT_FILE=$(OBJECTS_DIRECTORY)/$(PROJECT_NAME).o

SOURCE_FILES=$(wildcard $(SOURCES_DIRECTORY)/*.c)
OBJECT_FILES=$(patsubst $(SOURCES_DIRECTORY)/%.c, $(OBJECTS_DIRECTORY)/%.o, $(SOURCE_FILES))

CC=gcc
C_FLAGS=-O3 -I$(INCLUDE_DIRECTORY)
LD=ld
LD_FLAGS=

$(OUT_FILE): $(OBJECT_FILES)
	$(LD) $(LD_FLAGS) -r $^ -o $@

$(OBJECTS_DIRECTORY)/%.o: $(SOURCES_DIRECTORY)/%.c
	$(CC) $(C_FLAGS) -c $< -o $@

examples: .FORCE
	cd $(EXAMPLES_DIRECTORY) && make

all: $(OUT_FILE) examples

clean:
	-rm $(OUT_FILE) $(OBJECTS_DIRECTORY)/*.o 2> /dev/null

clean_examples:
	cd $(EXAMPLES_DIRECTORY) && make clean

clean_all: clean clean_examples

.FORCE:

