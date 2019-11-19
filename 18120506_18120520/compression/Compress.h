#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Huffman.h"
#include "Hash.h"

using namespace std;

// ChuyêÒn daŞy bit sang kiì tıò 
char bitsToChar(string code);
// Xây dıòng baÒng tra cıìu neìn tıÌ Huffman Codes
HashTable<string>* buildCompressTable(vector<HuffmanCode*> huffCodes);
// Taòo daŞy bit tıÌ text dıòa vaÌo baÒn tra cıìu neìn
string getSequenceOfBit(string text, HashTable<string>* table);
// Neìn vaÌo file
void compressToFile(string filename, vector<HuffNode*> freqTable, string text);

