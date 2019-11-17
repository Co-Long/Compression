// C program for Huffman Coding 
#include <stdio.h> 
#include <stdlib.h> 
#include"Huffman.h"
#include"Hash.h"

// This constant can be avoided by explicitly 
// calculating height of Huffman Tree 
#define MAX_TREE_HT 100 
int main()
{
	string str = getStringFromFile("text.txt");
	vector<HuffNode*> freqTable = initFreqTable(str);

	HuffmanCodes(freqTable);
	

	return 0;
}
