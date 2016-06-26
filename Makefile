IDIR = ./include
SDIR = ./src
ODIR = ./obj

CC = gcc
CXX = g++
CFLAGS = -I$(IDIR) -g -Wall -Wpedantic
CXXFLAGS = -std=c++11 -I$(IDIR) -g -Wall -Wpedantic

_DEPS = datafile.h table_entry.h table.h datablock.h rowid.h buffer.h btree.h node.h bdata.h ldata.h branch.h leaf.h table_c.h

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = datafile.o table_entry.o table.o datablock.o rowid.o buffer.o btree.o bdata.o ldata.o branch.o leaf.o msh.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: main

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

main: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

obj/msh.o: src/msh.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean run

run: main
	./main

clean:
	rm -f datafile.part
	rm -f $(ODIR)/*.o 
	rm -f main
