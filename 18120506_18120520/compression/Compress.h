#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Huffman.h"
#include "Hash.h"

using namespace std;

// Chuy��n da�y bit sang ki� t�� 
char bitsToChar(string code);
// X�y d��ng ba�ng tra c��u ne�n t�� Huffman Codes
HashTable<string>* buildCompressTable(vector<HuffmanCode*> huffCodes);
// Ta�o da�y bit t�� text d��a va�o ba�n tra c��u ne�n
string getSequenceOfBit(string text, HashTable<string>* table);
// Ne�n va�o file
void compressToFile(string filename, vector<HuffNode*> freqTable, string text);

