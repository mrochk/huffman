#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <istream>
#include <map>
#include <string>

#include "utils.h"

using namespace std;

class HuffmanNode {
public:
  char symbol;
  uint occurs;
  HuffmanNode *left, *right;

  /**************************************************************************/

  HuffmanNode() {
    this->symbol = ' ';
    this->occurs = 0;
    left = EMPTY;
    right = EMPTY;
  };

  HuffmanNode(char symbol, uint occurs) {
    this->symbol = symbol;
    this->occurs = occurs;
    left = EMPTY;
    right = EMPTY;
  }

  HuffmanNode(char symbol, uint occurs, HuffmanNode *left, HuffmanNode *right) {
    this->symbol = symbol;
    this->occurs = occurs;
    this->left = left;
    this->right = right;
  }
};

typedef class HuffmanNode HuffmanTree;

class Huffman {
public:
  /* Computes the Huffman tree associated to the given file and returns what
   * would be the new file size in bytes or 0 if an error occured.
   * @param filename The path to the file to which calculate the encoded
   * size.*/
  uint encode_file(string filename);

  /* Returns a map of <symbol, n_occurences> of each symbol in a text file.
   * @param file The file that we want to create the map from.*/
  map<char, uint> create_map_of_occurrences(ifstream &file);

  /* Creates an Huffman-tree based on a map of <symbol, n_occurences> using a
   * heap.
   * @param stream The map that we want to create the tree from.*/
  HuffmanTree *create_huffman_tree(map<char, uint>);

  /* Creates a map of <symbol, prefix_code> from an huffman-tree.
   * @param tree The tree that we want to get the prefix_codes from.*/
  map<char, string> create_map_of_codes(HuffmanNode *tree);

  /* The create_map_of_codes auxiliary function.*/
  void _create_map_of_codes(HuffmanNode *node, string code,
                            map<char, string> &codes);

  /* Replaces every text file characted by his associated prefix-code and
   * returns his new size in bytes. */
  uint compute_diff(ifstream &file, map<char, string> &codes);
};

#endif