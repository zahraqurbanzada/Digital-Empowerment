#include <iostream>
#include <fstream>
using namespace std;

// Compress function using Run-Length Encoding
void compressFile(const string &inputFile, const string &outputFile) {
    ifstream in(inputFile);
    ofstream out(outputFile);
    if (!in || !out) { cerr << "File error.\n"; return; }

    char ch, prev;
    int count = 1;
    in.get(prev);

    while (in.get(ch)) {
        if (ch == prev) count++;
        else { out << prev << count; prev = ch; count = 1; }
    }
    out << prev << count;
}

// Decompress function 
void decompressFile(const string &inputFile, const string &outputFile) {
    ifstream in(inputFile);
    ofstream out(outputFile);
    if (!in || !out) { cerr << "File error.\n"; return; }

    char ch;
    int count;
    while (in >> ch >> count) while (count--) out.put(ch);
}

// Main function to test compression and decompression
int main() {
    compressFile("input.txt", "compressed.txt");
    decompressFile("compressed.txt", "decompressed.txt");
    return 0;
}
