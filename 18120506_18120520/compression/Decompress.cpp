#include "Decompress.h"

// ChuyêÒn kiì týò chuyêÌn vaÌo thaÌnh daÞy 8 bit
string charToBits(char c) {
	int dec = (int)c;
	// KiêÒm tra extended ascii
	if (dec < 0) dec = dec + 129 + 127;
	string bits = "";

	// Ðoòc týÌng bit cuÒa dec vaÌo string bits
	while (dec) {
		int bit = dec & 1;
		if (bit == 1) bits = "1" + bits;
		else bits = "0" + bits;
		dec >>= 1;
	}

	// padding start with 0 for 8-length bits
	while (bits.length() < 8) {
		bits = "0" + bits;
	}

	return bits;
}

vector<HuffNode*> getFreqTableFromFile(ifstream& fi) {
	int size;
	vector<HuffNode*> freqTable;

	fi.read((char*)& size, sizeof(int));
	freqTable.resize(size);

	for (int i = 0; i < size; i++)
	{
		freqTable[i] = new HuffNode;
		fi.read((char*)freqTable[i], sizeof(HuffNode));
	}

	return freqTable;
}

string getCompressTextFromFile(ifstream& fi) {
	string compressText = "";
	char c;

	while (fi.read(&c, sizeof(char))) {
		//fi.read(&c, sizeof(char));
		cout << c << endl;
		compressText += c;
	}

	cout << compressText << "*";
	return compressText;
}

string textToSequenceOfBit(string text) {
	string sequenceOfBit = "";

	for (int i = 0; i < text.length(); i++)
	{
		sequenceOfBit += charToBits(text[i]);
	}

	return sequenceOfBit;
}

string textFromHuffmanTree(HuffNode *root, string sequenceOfBit, int addedBit) {
	cout << "\n" << sequenceOfBit << "a\n";
	HuffNode* temp = root;
	string text = "";

	for (int i = 0; i < sequenceOfBit.length() - addedBit; i++)
	{
		if (sequenceOfBit[i] == '0') {
			temp = temp->left;
		}
		else {
			temp = temp->right;
		}

		if (isLeaf(temp)) {
			text += temp->data;
			temp = root;
		}
	}

	return text;
}

void decompressFromFile(string src, string des) {
	ifstream fi;
	ofstream fo;
	fi.open(src, ios::binary);
	fo.open(des);

	vector<HuffNode*> freqTable = getFreqTableFromFile(fi);
	HuffNode* root = buildHuffmanTree(freqTable);

	int addedBit;
	fi.read((char*)& addedBit, sizeof(int));

	string compressText = getCompressTextFromFile(fi);
	string sequenceOfBit = textToSequenceOfBit(compressText);
	string text = textFromHuffmanTree(root, sequenceOfBit, addedBit);

	fo << text;
	fi.close();
	fo.close();

	cout << "Done\n";
}