#Makefile template

INCLDR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I$(INCLDR)

OBJDIR = obj

_DEPS = oppgave4.h
DEPS = $(patsubst %,$(INCLDR)/%,$(_DEPS))

_OBJS = oppgave4.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))


$(OBJDIR)/%.o: %.c $(DEPS)
		 $(CC) -c -o $@ $< $(CFLAGS)

oppgave_4: $(OBJS)
		 gcc -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
		 rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~ 