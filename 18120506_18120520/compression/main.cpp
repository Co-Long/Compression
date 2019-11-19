// C program for Huffman Coding 
#include <stdio.h> 
#include <stdlib.h> 
#include"Huffman.h"
#include"Hash.h"
#include "Compress.h"
#include "Decompress.h"

// This constant can be avoided by explicitly 
// calculating height of Huffman Tree 
#define MAX_TREE_HT 100 
int main()
{
	string str = getStringFromFile("text.txt");
	vector<HuffNode*> freqTable = initFreqTable(str);

	compressToFile("compress", freqTable, str);
	decompressFromFile("compress", "extract.txt");

	/*ifstream fi;
	fi.open("output", ios::binary);
	ofstream fo;
	fo.open("concho.txt");
	char c;
	fi.read(&c, 1);*/


	return 0;
}
