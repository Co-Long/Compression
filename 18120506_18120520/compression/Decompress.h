#pragma once
#include <string>
#include"Huffman.h"
#include"Hash.h"
using namespace std;

void decompressFromFile(string src, string des); 
string charToBits(char c);