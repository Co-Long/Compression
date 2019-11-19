#include "Compress.h"

// ChuyêÒn daŞy bit thaÌnh kiì tıò
char bitsToChar(string bits) {
	int dec = 0;

	for (int i = 0; i < bits.length(); i++)
	{
		// Thêm bit vaÌo trong dec 
		if (bits[i] == '1') dec += 1;
		// Diòch bit qua traìi
		dec <<= 1;
	}
	// Diòch bit qua phaÒi ğêÒ loaòi boÒ bit dı cuôìi
	dec >>= 1;

	return (char)dec;
}

// Xây dıòng baÒng tra cıìu neìn tıÌ Huffman Codes
HashTable<string>* buildCompressTable(vector<HuffmanCode*> huffCodes) {
	HashTable<string>* table = new HashTable<string>("string");
	
	for (int i = 0; i < huffCodes.size(); i++)
	{
		table->insert(huffCodes[i]->c, huffCodes[i]->code);
	}

	return table;
}

// Taòo daŞy bit tıÌ text dıòa vaÌo baÒn tra cıìu neìn
string getSequenceOfBit(string text, HashTable<string>* table) {
	string sequence = "";

	for (int i = 0; i < text.length(); i++)
	{
		sequence += table->get(text[i]);
	}

	return sequence;
}

// HaÌm thêm sôì 0 sau daŞy cho ğuÒ bit vaÌ traÒ vêÌ sôì bit ğaŞ thêm
int fillBit(string &sequenceOfBit) {
	int addedBit = 8 - (sequenceOfBit.length() % 8);
	cout << "addbit: " << addedBit << endl;
	// Thêm sôì 0 sau daŞy cho ğuÒ bit
	for (int i = 0; i < addedBit; i++)
	{
		sequenceOfBit += '0';
	}

	return addedBit;
}

// Taòo text mõìi tıÌ daŞy bit
string getNewText(string sequenceOfBit) {
	int pos = 0;
	int length = sequenceOfBit.length();
	string newText = "";

	// Duyêòt môŞi 8 bit ğêÒ chuyêÒn thaÌnh char
	while (pos < length) {
		string tempBit = sequenceOfBit.substr(pos, 8);
		newText += bitsToChar(tempBit);
		pos += 8;
	}
	//cout << newText.length();
	return newText;
}

void compressToFile(string filename, vector<HuffNode*> freqTable, string text) {
	vector<HuffmanCode*> huffCodes = HuffmanCodes(freqTable);
	HashTable<string>* table = buildCompressTable(huffCodes);

	// Taòo daŞy bit tıÌ text dıòa trên baÒng tra cıìu neìn
	string sequenceOfBit = getSequenceOfBit(text, table);

	// Thêm sôì 0 vaÌo sau daŞy bit cho ğôò daÌi laÌ bôòi cuÒa 8
	int addedBit = fillBit(sequenceOfBit);
	cout << "addbit: " << addedBit << endl;
	string newText = getNewText(sequenceOfBit);
	cout << "\n" << sequenceOfBit << "a\n";

	ofstream fo;
	fo.open(filename, ios::binary);

	if (fo) {
		int size = freqTable.size();
		fo.write((char*)&size, sizeof(int));

		for (int i = 0; i < size; i++)
		{
			fo.write((char*)freqTable[i], sizeof(HuffNode));
		}

		fo.write((char*)& addedBit, sizeof(int));

		fo.write(newText.c_str(), newText.length());

		fo.close();
	}
}