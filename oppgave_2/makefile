#Makefile template

INCLDR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I$(INCLDR)

OBJDIR = obj

_DEPS = FileManager.h wordProcessor.h
DEPS = $(patsubst %,$(INCLDR)/%,$(_DEPS))

_OBJS = oppgave2.o FileManager.o wordProcessor.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))


$(OBJDIR)/%.o: %.c $(DEPS)
		 $(CC) -c -o $@ $< $(CFLAGS)

oppgave_2: $(OBJS)
		 gcc -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
		 rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~ 