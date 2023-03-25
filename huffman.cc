#include "huffman.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "heap.h"

using namespace std;

map<char, uint> Huffman::create_map_of_occurrences(ifstream &file) {
    assert(file);

    map<char, uint> map_occurs;
    string line;

    while (!file.eof()) {
        getline(file, line);
        for (auto &c : line) map_occurs[c]++;
        line.clear();
    }

    return map_occurs;
}

HuffmanTree *Huffman::create_huffman_tree(map<char, uint> occurs_map) {
    auto compare =
        ([](HuffmanNode *a, HuffmanNode *b) { return a->occurs > b->occurs; });

    Heap<HuffmanNode *> heap(compare);

    for (auto &p : occurs_map) heap.insert(new HuffmanNode(p.first, p.second));

    while (heap.get_size() > 1) {
        auto first  = heap.pop_top();
        auto second = heap.pop_top();
        auto inode  = new HuffmanNode('$', (first->occurs + second->occurs),
                                     first, second);
        heap.insert(inode);
    }

    return heap.pop_top();
}

void Huffman::_create_map_of_codes(HuffmanNode *node, string code,
                                   map<char, string> &codes) {
    if (node == nullptr) return;
    if (node->symbol != '$') {
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

void print_dict(map<char, string> &codes) {
    vector<pair<char, string>> sorted;
    for (auto &c : codes) {
        sorted.push_back(c);
    }

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

uint Huffman::compute_diff(ifstream &file, map<char, string> &codes) {
    string line;
    uint len_encoded, len_base;
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

    cout << "\nAssuming the characters are ASCII encoded:\n";
    cout << " - Provided file size: " << len_base << " bytes.\n";
    cout << " - Huffman encoded file size: " << len_encoded << " bytes.\n";
    cout << " - Difference: -" << len_base - len_encoded << " bytes.\n";

    return len_encoded;
}

uint Huffman::encode_file(string filename) {
    ifstream file;

    file.open(filename);
    assert(!file.fail() && "ERROR: when opening the file");
    assert(!(file.peek() == std::ifstream::traits_type::eof()) &&
           "ERROR: empty file provided");

    auto occurs_map   = create_map_of_occurrences(file);
    auto huffman_tree = create_huffman_tree(occurs_map);
    auto codes        = create_map_of_codes(huffman_tree);

    print_dict(codes);

    return compute_diff(file, codes);
}
