IDIR = ./include
SDIR = ./src
ODIR = ./obj

CC = g++
CFLAGS = -std=c++11 -I$(IDIR) -g -Wall -Wpedantic

_DEPS = datafile.h table_entry.h table.h datablock.h rowid.h buffer.h btree.h node.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o datafile.o table_entry.o table.o datablock.o rowid.o buffer.o btree.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean run

run: main
	./main

clean:
	rm -f datafile.part
	rm -f tabledata.bin
	rm -f $(ODIR)/*.o 
	rm -f main
