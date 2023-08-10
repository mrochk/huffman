.RECIPEPREFIX = >

all: build

build: 
> @mkdir -p bin
> @g++ -Wall main.cc huffman.cpp binary_heap.hpp -pedantic -o bin/huffman

test: build
> @echo "Testing on a 5000+ characters file:"
> @./bin/huffman test_files/medium.txt

clean:
> @rm -r bin
