#include <cstdlib>
#include <iostream>

#include "huffman.h"

int main(int argc, char **argv) {
    Huffman encoder;

    if (argc < 2) {
        std::cerr << "Usage: huffman <file_to_encode>\n";
        return 1;
    }

    encoder.encode_file(argv[1]);

    return 0;
}