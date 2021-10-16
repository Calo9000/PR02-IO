TARGET=bst
 
# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall
 
PTHREAD=-pthread
 
CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe

 
# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic -lm
 
OBJS=    bst.o
 
all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)
    
bst.o: bst.c
	$(CC) -c $(CCFLAGS) bst.c $(GTKLIB) -o bst.o -lm
    
clean:
	rm -f *.o $(TARGET)
