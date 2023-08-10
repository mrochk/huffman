#include <cstdlib>
#include <iostream>

#include "huffman.hpp"

int main(int argc, char **argv) {
    Huffman huff;

    if (argc < 2) {
        std::cerr << "Usage: huffman <file_to_encode>\n";
        return 1;
    }

    char *filename = argv[1];
    huff.encoded_file_size(filename);

    return EXIT_SUCCESS;
}
