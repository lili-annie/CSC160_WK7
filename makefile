CC=g++
CFLAGS=-I.
DEPS = 
OBJ = wk7.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

wk7: $(OBJ)
	$(CC) -o $@ csc160.o wk7.o $(CFLAGS)

all: wk7

clean:
	rm -f *.o wk7
