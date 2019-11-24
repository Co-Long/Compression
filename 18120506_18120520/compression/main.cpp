// C program for Huffman Coding 
#include <stdio.h> 
#include <stdlib.h>
#include"Huffman.h"
#include"Hash.h"
#include "Compress.h"
#include "Decompress.h"
#include"UnicodeFile.h"

// This constant can be avoided by explicitly 
// calculating height of Huffman Tree 
#define MAX_TREE_HT 100 
int main()
{
	/*string str = getStringFromFile("text.txt");
	vector<HuffNode*> freqTable = initFreqTable(str);

	compressToFile("compress", freqTable, str);
	decompressFromFile("compress", "extract.txt");*/

	
	FindFile(L"E:\\Bai tap\\CTDL_Seminar_2\\*.*");


	return 0;
}
