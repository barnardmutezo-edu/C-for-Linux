#Makefile template

INCLDR = ./include
CC = gcc
CFLAGS = -O2 -lpthread
CFLAGS += -I$(INCLDR)

OBJDIR = obj

_DEPS = Data.h
DEPS = $(patsubst %,$(INCLDR)/%,$(_DEPS))

_OBJS = oppgave5.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))


$(OBJDIR)/%.o: %.c $(DEPS)
		 $(CC) -c -o $@ $< $(CFLAGS)

oppgave_5: $(OBJS)
		 gcc -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
		 rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~ 