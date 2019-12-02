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

using namespace std;

int main()
{
	/*string str = getStringFromFile("text.txt");
	vector<HuffNode*> freqTable = initFreqTable(str);

	compressToFile("compress", freqTable, str);
	decompressFromFile("compress", "extract.txt");*/

	
	string s;
	cout << "Nhap duong dan: " << endl;
	getline(cin, s);
	if (boost::filesystem::is_directory(s)) {
		compressFolder(s, true, "");
	}
	else {
		string output;
		output = s + "_compress";
		compressFile(s,output);
	}

	cout << "-----Decompress-----" << endl;
	cout << "Nhap duong dan: " << endl;
	getline(cin, s);

	if (boost::filesystem::is_directory(s)) {
		decompressFolder(s, true, "");
	}
	else {
		string output(s);
		output.resize(s.size() - strlen("_compress"));
		decompressFile(s, output);
	}


	return 0;
}
