# Huffman
Huffman coding gain calculator for text files.

References:
- https://en.wikipedia.org/wiki/Huffman_coding
- https://cmps-people.ok.ubc.ca/ylucet/DS/Huffman.html

This program outputs what would be a provided file size in bytes if it was encoded using the Huffman coding, and how much we would gain.

To try it, first build the project using `make`.

You can then test that everything is working properly by typing `make test`.

You can also provide your own text-file:
```
./bin/huffman <filename>
```

**Overall, after some testing with my program, I came to the conclusion that the files compressed using the Huffman coding lose more or less ~40% of their original size.**

*NOTES:*
 - *I assume that the characters are ASCII encoded, otherwise we would gain even more space.*
 - *If we would really encode the provided file, we would have to also write the associated Huffman tree to be able to decode it later, which would take additional space.*
 - *I use my own binary heap implementation in this project that you can find [here](https://github.com/mrochk/binary-heap).*