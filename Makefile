.RECIPEPREFIX = >

all: build

build: 
> @mkdir -p bin
> @g++ -Wall main.cc huffman.cc heap.h utils.h -pedantic -o bin/huffman

test_small:
> @echo "Testing on a ~100 characters file:"
> @./bin/huffman test_files/small.txt

test_medium:
> @echo "Testing on a ~5000 characters file:"
> @./bin/huffman test_files/medium.txt

test_large:
> @echo "Testing on a ~100000 characters file:"
> @./bin/huffman test_files/large.txt

clean:
> @rm -r bin
