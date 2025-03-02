Huffman Coding Text Compression Project
This project implements Huffman Coding, a lossless data compression algorithm used to reduce the size of text files. The program takes an input string, builds a Huffman Tree, and generates unique binary codes for each character based on their frequency. The more frequent a character is, the shorter its binary code.

Key Features:
Huffman Tree Construction:

Calculates character frequencies.
Builds a tree using a priority queue.
Assigns binary codes to characters.
Encoding:

Converts the input text into a binary sequence using Huffman codes.
Saves the compressed data to a file.
Decoding:

Reads the encoded binary data.
Traverses the Huffman tree to reconstruct the original text.
File Compression:

The program calculates the original and compressed file sizes.
Displays the compression ratio to indicate efficiency.
This project demonstrates how Huffman coding efficiently reduces file size, making it useful for text compression in applications like ZIP file creation and network data transmission. 
