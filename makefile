CC=g++
CFLAGS=-I ./boost_1_49_0

# for every foo.o rule perform g++ 
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< 
make: main.o server.o client.o packets/Packet.o packets/PacketAck.o
	$(CC) $(CFLAGS) -o main main.o server.o client.o packets/Packet.o packets/PacketAck.o