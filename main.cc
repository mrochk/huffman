#include <bits/stdc++.h>

#include "huffman.h"

using namespace std;

int main(int argc, char **argv) {
    Huffman encoder;

    if (argc < 2) {
        cout << "Usage: huffman <file_to_encode>\n";
        return 1;
    }

    encoder.encode_file(argv[1]);

    return 0;
}