#include <cstdlib>
#include <iostream>

#include "huffman.hpp"

int main(int argc, char **argv) {
    Huffman h;

    if (argc < 2) {
        std::cerr << "Usage: huffman <file_to_encode>\n";
        return 1;
    }

    char *filename = argv[1];

    pair<uint, uint> result = h.encoded_file_size(filename);
    h.print_resume(result.first, result.second);

    return 0;
}
