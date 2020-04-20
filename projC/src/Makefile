IDIR=../include
ODIR=obj

CC = gcc
CFLAGS = -O2 -Wall -g -ansi -D_GNU_SOURCE -I$(IDIR)

_DEPS = clients.h products.h billing.h sales.h interface.h filial.h output.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o clients.o products.o billing.o sales.o interface.o filial.o output.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

program: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f obj/*.o
	rm -f program