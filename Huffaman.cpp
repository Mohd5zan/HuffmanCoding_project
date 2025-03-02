#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <bitset>
using namespace std;

// Huffman tree Node
struct Node
{
    char ch;
    int freq;
    Node *left, *right;
    Node(char ch, int freq, Node *left = nullptr, Node *right = nullptr)
    {
        this->ch = ch;
        this->freq = freq;
        this->left = left;
        this->right = right;
    }
};

// custom comparison operator for priority queue
struct compare
{
    bool operator()(Node *a, Node *b)
    {
        return a->freq > b->freq;
    }
};

// generating Huffman codes
void GenerateHuffmanCodes(Node *root, string code, unordered_map<char, string> &huffmanMap)
{
    if (!root)
        return;
    if (!root->left && !root->right)
    {
        huffmanMap[root->ch] = code;
    }
    GenerateHuffmanCodes(root->left, code + "0", huffmanMap);
    GenerateHuffmanCodes(root->right, code + "1", huffmanMap);
}

// Building Huffman Tree and Getting codes
Node *buildHuffmanTree(string text, unordered_map<char, string> &huffmanMap)
{
    unordered_map<char, int> freq;
    for (char ch : text)
        freq[ch]++;
    priority_queue<Node *, vector<Node *>, compare> pq;
    for (auto pair : freq)
    {
        Node *newnode = new Node(pair.first, pair.second);
        pq.push(newnode);
    }
    while (pq.size() > 1)
    {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();
        pq.push(new Node('\0', left->freq + right->freq, left, right));
    }
    Node *root = pq.top();
    GenerateHuffmanCodes(root, "", huffmanMap);
    return root;
}

// Encoding the text
string EncodeText(string text, unordered_map<char, string> &huffmanMap)
{
    string encodedText = "";
    for (char ch : text)
        encodedText += huffmanMap[ch];
    return encodedText;
}

// Decoding the Huffman-Encoded text
string decodeText(string encodedText, Node *root)
{
    string decodedText = "";
    Node *current = root;
    for (char bit : encodedText)
    {
        if (bit == '0')
            current = current->left;
        else
            current = current->right;
        if (!current->left && !current->right)
        {
            decodedText += current->ch;
            current = root;
        }
    }
    return decodedText;
}

// save Huffman encoded data to a file
void savingtoFile(string filename, string encodedText)
{
    ofstream outfile(filename, ios::binary);

    // Convert "010101..." to actual bytes
    char buffer = 0;
    int bitCount = 0;

    for (char bit : encodedText)
    {
        buffer = (buffer << 1) | (bit - '0'); // Shift bits and add new bit
        bitCount++;

        if (bitCount == 8) // If we have a full byte
        {
            outfile.put(buffer);
            buffer = 0;
            bitCount = 0;
        }
    }

    // Write the last remaining bits (if not a full byte, pad with 0s)
    if (bitCount > 0)
    {
        buffer <<= (8 - bitCount);
        outfile.put(buffer);
    }

    outfile.close();
}

// Reading the encoded data from a file
string readFromFile(string filename)
{
    ifstream infile(filename, ios::binary);
    string encodedText;
    char ch;

    while (infile.get(ch))
    {
        encodedText += bitset<8>(ch).to_string(); // Convert each byte to an 8-bit binary string
    }

    infile.close();
    return encodedText;
}

// function to free memory
void freeHuffmanTree(Node *root)
{
    if (!root)
        return;
    freeHuffmanTree(root->left);
    freeHuffmanTree(root->right);
    delete root;
}

// calculating fileSize
long long getfilesize(string filename)
{
    ifstream in(filename, ios::binary | ios::ate);
    return in.tellg();
}
int main()
{
    string text;
    cout << "Enter the text to compress :" << '\n';
    getline(cin, text);

    // orginal size
    long long originalSize = text.size();

    unordered_map<char, string> huffmanMap;
    Node *root = buildHuffmanTree(text, huffmanMap);
    string encodedtext = EncodeText(text, huffmanMap);

    cout << "\n Encoded Text:" << encodedtext << endl;

    // save compressed File
    savingtoFile("sample.txt", encodedtext);

    // calculate compressed file size
    long long compressedSize = getfilesize("sample.txt");

    // Display Compression Results
    cout << "\n Original File Size:" << originalSize << "Bytes";
    cout << "\n Compressed File Size:" << compressedSize << "Bytes";
    cout << "\n Compression Ratio:" << (1.0 - ((double)compressedSize / originalSize)) * 100 << "%\n";
    freeHuffmanTree(root);
}
