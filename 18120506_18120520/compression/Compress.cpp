#include "Compress.h"

// Chuy��n da�y bit tha�nh ki� t��
char bitsToChar(string bits) {
	int dec = 0;

	for (int i = 0; i < bits.length(); i++)
	{
		// Th�m bit va�o trong dec 
		if (bits[i] == '1') dec += 1;
		// Di�ch bit qua tra�i
		dec <<= 1;
	}
	// Di�ch bit qua pha�i ��� loa�i bo� bit d� cu��i
	dec >>= 1;

	return (char)dec;
}

// X�y d��ng ba�ng tra c��u ne�n t�� Huffman Codes
HashTable<string>* buildCompressTable(vector<HuffmanCode*> huffCodes) {
	HashTable<string>* table = new HashTable<string>("string");
	
	for (int i = 0; i < huffCodes.size(); i++)
	{
		table->insert(huffCodes[i]->c, huffCodes[i]->code);
	}

	return table;
}

// Ta�o da�y bit t�� text d��a va�o ba�n tra c��u ne�n
string getSequenceOfBit(string text, HashTable<string>* table) {
	string sequence = "";

	for (int i = 0; i < text.length(); i++)
	{
		sequence += table->get(text[i]);
	}

	return sequence;
}

// Ha�m th�m s�� 0 sau da�y cho �u� bit va� tra� v�� s�� bit �a� th�m
int fillBit(string &sequenceOfBit) {
	int addedBit = 8 - (sequenceOfBit.length() % 8);
	cout << "addbit: " << addedBit << endl;
	// Th�m s�� 0 sau da�y cho �u� bit
	for (int i = 0; i < addedBit; i++)
	{
		sequenceOfBit += '0';
	}

	return addedBit;
}

// Ta�o text m��i t�� da�y bit
string getNewText(string sequenceOfBit) {
	int pos = 0;
	int length = sequenceOfBit.length();
	string newText = "";

	// Duy��t m��i 8 bit ��� chuy��n tha�nh char
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

	// Ta�o da�y bit t�� text d��a tr�n ba�ng tra c��u ne�n
	string sequenceOfBit = getSequenceOfBit(text, table);

	// Th�m s�� 0 va�o sau da�y bit cho ��� da�i la� b��i cu�a 8
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