CC=g++
CFLAGS= -g3

G++ = g++

INCLUDE_PATH = ./include
LIB_PATH = ./lib
GOOGLE_TEST_LIB = gtest

G++FLAGS = -std=c++11 -g3 -Wall -I $(INCLUDE_PATH)
LD_FLAGS = -std=c++11 -L ./lib -l $(GOOGLE_TEST_LIB) -lgmock -l pthread

TARGETS= main test
OBJECTS= server.o client.o packets.o session.o lobby.o ServerRecv.o receiver.o clientReceiver.o
MAIN_OBJECTS= main.o $(OBJECTS)
TEST_OBJECTS= test.o $(OBJECTS)

# for every foo.o rule perform g++ 
%.o: %.cpp
	$(G++) $(G++FLAGS) -c -o $@ $< 
make: main

main: $(MAIN_OBJECTS)
	$(G++) $(G++FLAGS) -o $@ $(MAIN_OBJECTS)

test: $(TEST_OBJECTS)
	$(G++) -o $@ $(TEST_OBJECTS) $(LD_FLAGS)

all: $(TARGETS)

clean:
	rm main.o test.o $(OBJECTS) $(TARGETS)