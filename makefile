CC = g++
LD = g++

LDFLAGS = -std=c++14 -Wall -Wextra -Werror -pedantic
CCFLAGS = $(LDFLAGS) -c

SRCDIR = src
OBJDIR = obj

EXE = Genetic


all: $(EXE)


$(EXE):	$(OBJDIR)/Genetic.o $(OBJDIR)/main.o
	$(LD) $(LDFLAGS) $(OBJDIR)/Genetic.o $(OBJDIR)/main.o -o $(EXE)


$(OBJDIR)/Genetic.o:	$(SRCDIR)/Genetic.hpp $(SRCDIR)/Genetic.cpp
	$(CC) $(CCFLAGS) $(SRCDIR)/Genetic.cpp -o $(OBJDIR)/Genetic.o

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	$(CC) $(CCFLAGS) $(SRCDIR)/main.cpp -o $(OBJDIR)/main.o
