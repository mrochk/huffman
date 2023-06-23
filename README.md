# Huffman
Implementation of the Huffman coding algorithm.

References:
- https://en.wikipedia.org/wiki/Huffman_coding
- https://cmps-people.ok.ubc.ca/ylucet/DS/Huffman.html

This program outputs what would be a provided file size in bytes if it was encoded using this algorithm.

To try it, first build the project:
```
make build
```

You can then test it on different sized files by typing one of these 3 commands:
```
make test_<small/medium/large>
```

You can also provide your own text-file:
```
./bin/huffman <filename>
```

*NOTES:*
 - *I assume that the characters are ASCII encoded, otherwise we would gain even more space.*
 - *If we would really encode the provided file, we would have to also write the associated huffman-tree to be able to decode it later, which would take additional space.*
