EXAMPLES=$(dir $(wildcard ./*/makefile))
EXAMPLES_TO_MAKE=$(addsuffix /make, $(EXAMPLES))
EXAMPLES_TO_CLEAN=$(addsuffix /clean, $(EXAMPLES))

all: $(EXAMPLES_TO_MAKE)
clean: $(EXAMPLES_TO_CLEAN)

%/make: %
	- cd $< && make && cd ../

%/clean: %
	- cd $< && make clean && cd ../

