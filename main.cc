#include <bits/stdc++.h>

#include "huffman.h"

using namespace std;

int main(int argc, char **argv) {
  Huffman encoder;

  if (argc < 2)
    cout << "Usage: huffman <file_to_encode>\n";
  else if (encoder.encode_file(argv[1]) > 0)
    return EXIT_SUCCESS;
  else {
    cerr << "An error occcured.\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}