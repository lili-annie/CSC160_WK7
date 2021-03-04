CC=g++
CFLAGS=-I.
DEPS = csc160.h
OBJ = csc160.o wk7.o hw7.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

wk7: $(OBJ)
	$(CC) -o $@ csc160.o wk7.o $(CFLAGS)

hw7: $(OBJ)
	$(CC) -o $@ csc160.o hw7.o $(CFLAGS)

all: wk7 hw7

clean:
	rm -f *.o wk7 hw7
