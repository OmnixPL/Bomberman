CC=g++
CFLAGS= -g3

# for every foo.o rule perform g++ 
%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $< 
make: main.o server.o client.o packets.o
	$(CC) $(CFLAGS) -o main main.o server.o client.o packets.o