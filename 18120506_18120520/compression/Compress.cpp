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

// Taòo daŞy maŞ hoìa baÒng tra cıìu neìn tıÌ Huffman Codes
string encodeCompressTable(vector<HuffmanCode*> huffCodes) {
	string encoded = "";

	for (int i = 0; i < huffCodes.size(); i++)
	{
		// môŞi mâŞu encoded = kiì tıò gôìc + daòng kiì tıò cuÒa code
		encoded = encoded + huffCodes[i]->c + bitsToChar(huffCodes[i]->code);
	}

	return encoded;
}

// HaÌm thêm sôì 0 sau daŞy cho ğuÒ bit vaÌ traÒ vêÌ sôì bit ğaŞ thêm
int fillBit(string &sequenceOfBit) {
	int addedBit = 8 - (sequenceOfBit.length() % 8);

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

	return newText;
}

void compressToFile(string filename, vector<HuffmanCode*> huffCodes, string text) {
	HashTable<string>* table = buildCompressTable(huffCodes);

	// Taòo maŞ hoìa baÒng tra cıìu tıÌ huffCodes
	string encodedCompressTable = encodeCompressTable(huffCodes);

	// Taòo daŞy bit tıÌ text dıòa trên baÒng tra cıìu neìn
	string sequenceOfBit = getSequenceOfBit(text, table);

	// Thêm sôì 0 vaÌo sau daŞy bit cho ğôò daÌi laÌ bôòi cuÒa 8
	int addedBit = fillBit(sequenceOfBit);

	string newText = getNewText(sequenceOfBit);
	cout << "\n" << sequenceOfBit << "\n";
	cout << "\n" << newText << "\n";

	ofstream fo;
	fo.open(filename);

	if (fo) {
		// Ghi sôì kiì tıò trong header vaÌo doÌng ğâÌu cuÒa line
		fo << encodedCompressTable.length() + 1 << endl;
		// Ghi Header (kiì tıò dı cuÌng daŞy maŞ hoìa baÒng tra cıìu) 
		fo << addedBit << encodedCompressTable;
		// Ghi nôòi dung neìn
		fo << newText;

		fo.close();
	}
}