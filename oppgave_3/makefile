#Makefile template

INCLDR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I$(INCLDR)

OBJDIR = obj

_DEPS = ListManager.h ConsoleManager.h Node.h Data.h FileManager.h
DEPS = $(patsubst %,$(INCLDR)/%,$(_DEPS))

_OBJS = oppgave3.o ListManager.o ConsoleManager.o FileManager.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))


$(OBJDIR)/%.o: %.c $(DEPS)
		 $(CC) -c -o $@ $< $(CFLAGS)

oppgave_3: $(OBJS)
		 gcc -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
		 rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~ 