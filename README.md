# Huffman
Huffman coding gain calculator for text files.

References:
- https://en.wikipedia.org/wiki/Huffman_coding
- https://cmps-people.ok.ubc.ca/ylucet/DS/Huffman.html

This program outputs what would be a provided file size in bytes if it was encoded using the Huffman coding, and how much bytes we would gain compared to the original file size.

To try it, build the project using `make`.\
You can test that everything is working properly by typing `make test`.\
You can then use this program on your own text-files using `./bin/huffman <filename>`.

*NOTES:*
 - *When printing the dictionary, '_' represents then space character.*
 - *I assume that the input file is always ASCII encoded, otherwise the file we would be more compressed.*
 - *If we would really encode the provided file, we would have to also write the associated Huffman tree to be able to decode it later, which would take additional space.*
 - *I use my own minimalist binary heap implementation in this project that you can find [here](https://github.com/mrochk/binary-heap).*
