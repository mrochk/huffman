#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <istream>
#include <map>
#include <string>

using namespace std;

#define INODE_SYMBOL '$'

typedef struct HuffmanNode {
    char         symbol;
    uint         occurs;
    HuffmanNode *left, *right;

    HuffmanNode();

    HuffmanNode(char, uint);

    HuffmanNode(char, uint, HuffmanNode *, HuffmanNode *);

    ~HuffmanNode();

} HuffmanNode, HuffmanTree;

class Huffman {
   public:
    /* Returns what would be the new file size in bytes if it was encoded
       using Huffman coding. */
    pair<uint, uint> encoded_file_size(string filename);

    void print_resume(int, int);

   private:
    map<char, uint> create_map_of_occurrences(ifstream &file);

    HuffmanTree *create_huffman_tree(map<char, uint> &occurences_map);

    map<char, string> create_map_of_codes(HuffmanNode *tree);

    void _create_map_of_codes(HuffmanNode *, string, map<char, string> &);

    pair<uint, uint> compute_diff(ifstream &file, map<char, string> &codes);

    void print_dict(map<char, string> &codes);
};

#endif
