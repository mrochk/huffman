#include "huffman.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "heap.h"

using namespace std;

HuffmanNode::HuffmanNode() {
  this->symbol = ' ';
  this->occurs = 0;
  left = EMPTY;
  right = EMPTY;
};

HuffmanNode::HuffmanNode(char symbol, uint occurs) {
  this->symbol = symbol;
  this->occurs = occurs;
  left = EMPTY;
  right = EMPTY;
}

HuffmanNode::HuffmanNode(char symbol, uint occurs, HuffmanNode *left,
                         HuffmanNode *right) {
  this->symbol = symbol;
  this->occurs = occurs;
  this->left = left;
  this->right = right;
}

HuffmanNode::~HuffmanNode() {
  if (this->left != EMPTY)
    delete (left);
  if (this->left != EMPTY)
    delete (right);
}

uint Huffman::encode_file(string filename) {
  ifstream file;

  file.open(filename);
  assert(!file.fail() && "ERROR: when opening the file");

  auto occurs_map = create_map_of_occurrences(file);
  auto huffman_tree = create_huffman_tree(occurs_map);
  auto codes = create_map_of_codes(huffman_tree);

  print_dict(codes);

  delete (huffman_tree);
  return compute_diff(file, codes);
}

map<char, uint> Huffman::create_map_of_occurrences(ifstream &file) {
  assert(file);

  map<char, uint> map_occurs;
  string line;

  while (!file.eof()) {
    getline(file, line);
    for (auto &c : line)
      map_occurs[c]++;
  }

  return map_occurs;
}

HuffmanTree *Huffman::create_huffman_tree(map<char, uint> &occurrences_map) {
  Heap<HuffmanNode *> heap(
      [](HuffmanNode *a, HuffmanNode *b) { return a->occurs > b->occurs; });

  for (auto &p : occurrences_map)
    heap.insert(new HuffmanNode(p.first, p.second));

  while (heap.get_size() > 1) {
    auto a = heap.pop_top(), b = heap.pop_top();
    auto inode = new HuffmanNode(INODE_SYMBOL, (a->occurs + b->occurs), a, b);
    heap.insert(inode);
  }

  return heap.pop_top();
}

void Huffman::_create_map_of_codes(HuffmanNode *node, string code,
                                   map<char, string> &codes) {
  if (node == nullptr)
    return;

  if (node->symbol != INODE_SYMBOL) {
    codes[node->symbol] = code;
    return;
  }

  _create_map_of_codes(node->left, code + "0", codes);
  _create_map_of_codes(node->right, code + "1", codes);
}

map<char, string> Huffman::create_map_of_codes(HuffmanTree *tree) {
  assert(tree && "ERROR: empty tree");

  map<char, string> codes;
  _create_map_of_codes(tree, "", codes);

  return codes;
}

uint Huffman::compute_diff(ifstream &file, map<char, string> &codes) {
  string line;
  float len_encoded, len_base;
  len_base = len_encoded = 0;

  file.clear();
  file.seekg(0);

  while (!file.eof()) {
    getline(file, line);
    for (auto &c : line) {
      auto code = codes[c];
      len_encoded += code.size();
      len_base++;
    }
    line.clear();
  }

  len_encoded /= 8;
  int percentage = int(((len_encoded / len_base) - 1) * 100);

  cout << "\nAssuming the characters are ASCII encoded:\n";
  cout << " - Provided file size: " << len_base << " bytes.\n";
  cout << " - The Huffman encoded file size would be: " << ceil(len_encoded)
       << " bytes.\n";
  cout << " - Difference: -" << len_base - ceil(len_encoded) << " bytes ("
       << percentage << "%).\n";

  return len_encoded;
}

void Huffman::print_dict(map<char, string> &codes) {
  vector<pair<char, string>> sorted;

  for (auto &c : codes)
    sorted.push_back(c);

  auto compare = [](pair<char, string> a, pair<char, string> b) {
    return a.second.size() < b.second.size();
  };

  sort(sorted.begin(), sorted.end(), compare);

  cout << "---------------------\nGenerated "
          "Dictionary:\n---------------------\n";
  for (auto &p : sorted)
    cout << ((p.first == 32) ? '_' : p.first) << " :: " << p.second << '\n';
  cout << "---------------------";
}
