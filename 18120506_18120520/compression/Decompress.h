#pragma once
#include <string>
#include <map>
#include"Huffman.h"
#include"Hash.h"
#include"File.h"
using namespace std;

void decompressFromFile(string src, string des); 
string charToBits(char c);

void decompressFile(const boost::filesystem::path& source_path, string output);
void decompressFolder(const boost::filesystem::path& source_path, bool root, string rname);