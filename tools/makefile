TOOLS=$(dir $(wildcard ./*/makefile))
TOOLS_TO_MAKE=$(addsuffix /make, $(EXAMPLES))
TOOLS_TO_CLEAN=$(addsuffix /clean, $(EXAMPLES))

all: $(TOOLS_TO_MAKE)
clean: $(TOOLS_TO_CLEAN)

%/make: %
	- cd $< && mkdir -p objects bin && make && cd ../

%/clean: %
	- cd $< && make clean && cd ../

