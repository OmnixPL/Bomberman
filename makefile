CC=g++
CFLAGS=-I ./boost_1_49_0

# for every foo.o rule perform g++ 
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< 
make: main.o
	$(CC) $(CFLAGS) -o main main.o
