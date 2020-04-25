G++ = g++

INCLUDE_PATH = ./include
LIB_PATH = ./lib
GOOGLE_TEST_LIB = gtest

G++FLAGS = -c -Wall -I $(INCLUDE_PATH)
LD_FLAGS = -L ./lib -l $(GOOGLE_TEST_LIB) -l pthread

TARGETS = main test
OBJECTS = main.o test.o

# for every foo.o rule perform foo.cpp 
%.o: %.cpp
	$(G++) $(G++FLAGS)  -c -o $@ $< 
make: main.o
	$(G++) -o main main.o $(LD_FLAGS)

main: main.o
	$(G++) -o $@ $< $(LD_FLAGS)

all: $(TARGETS)

test: test.o
	$(G++) -o test $< $(LD_FLAGS)

clean:
	rm -f $(TARGETS) $(OBJECTS)