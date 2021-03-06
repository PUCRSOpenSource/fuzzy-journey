IDIR = ./include
SDIR = ./src
ODIR = ./obj

CC = gcc
CXX = g++
CFLAGS = -I$(IDIR) -g -Wall -Wpedantic
CXXFLAGS = -std=c++11 -I$(IDIR) -g -Wall -Wpedantic

_DEPS = datafile.h table_entry.h table.h datablock.h rowid.h buffer.h btree.h node.h bdata.h ldata.h branch.h leaf.h table_c.h

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = datafile.o table_entry.o table.o datablock.o rowid.o buffer.o btree.o bdata.o ldata.o branch.o leaf.o sif.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: main

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

main: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

obj/sif.o: src/sif.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean run doc

run: main
	./main

doc: Doxyfile
	doxygen $^
clean:
	rm -rf gt.png
	rm -rf graphTree
	rm -f datafile.part
	rm -f $(ODIR)/*.o 
	rm -f doc/xml/*
	rm -f main
