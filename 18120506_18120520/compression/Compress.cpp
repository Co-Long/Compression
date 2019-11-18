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

// Ta�o da�y ma� ho�a ba�ng tra c��u ne�n t�� Huffman Codes
string encodeCompressTable(vector<HuffmanCode*> huffCodes) {
	string encoded = "";

	for (int i = 0; i < huffCodes.size(); i++)
	{
		// m��i m��u encoded = ki� t�� g��c + da�ng ki� t�� cu�a code
		encoded = encoded + huffCodes[i]->c + bitsToChar(huffCodes[i]->code);
	}

	return encoded;
}

// Ha�m th�m s�� 0 sau da�y cho �u� bit va� tra� v�� s�� bit �a� th�m
int fillBit(string &sequenceOfBit) {
	int addedBit = 8 - (sequenceOfBit.length() % 8);

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

	return newText;
}

void compressToFile(string filename, vector<HuffmanCode*> huffCodes, string text) {
	HashTable<string>* table = buildCompressTable(huffCodes);

	// Ta�o ma� ho�a ba�ng tra c��u t�� huffCodes
	string encodedCompressTable = encodeCompressTable(huffCodes);

	// Ta�o da�y bit t�� text d��a tr�n ba�ng tra c��u ne�n
	string sequenceOfBit = getSequenceOfBit(text, table);

	// Th�m s�� 0 va�o sau da�y bit cho ��� da�i la� b��i cu�a 8
	int addedBit = fillBit(sequenceOfBit);

	string newText = getNewText(sequenceOfBit);
	cout << "\n" << sequenceOfBit << "\n";
	cout << "\n" << newText << "\n";

	ofstream fo;
	fo.open(filename);

	if (fo) {
		// Ghi s�� ki� t�� trong header va�o do�ng ���u cu�a line
		fo << encodedCompressTable.length() + 1 << endl;
		// Ghi Header (ki� t�� d� cu�ng da�y ma� ho�a ba�ng tra c��u) 
		fo << addedBit << encodedCompressTable;
		// Ghi n��i dung ne�n
		fo << newText;

		fo.close();
	}
}