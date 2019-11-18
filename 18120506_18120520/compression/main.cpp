// C program for Huffman Coding 
#include <stdio.h> 
#include <stdlib.h> 
#include"Huffman.h"
#include"Hash.h"
#include "Compress.h"

// This constant can be avoided by explicitly 
// calculating height of Huffman Tree 
#define MAX_TREE_HT 100 
int main()
{
	string str = getStringFromFile("text3.txt");
	vector<HuffNode*> freqTable = initFreqTable(str);
	vector<HuffmanCode*> out = HuffmanCodes(freqTable);
	
	compressToFile("output3", out, str);

	//test read
	//ifstream fi;
	//fi.open("output");
	//string a = "";
	//int num;

	//fi >> num;
	//fi.ignore(1);
	//
	//while(!fi.eof())
	//{
	//	string temp;
	//	getline(fi, temp);
	//	a += temp + '\n';
	//}

	//string header = a.substr(0, num);

	return 0;
}
