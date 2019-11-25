#include "Compress.h"

// Chuyển dãy bit thành ký tự
char bitsToChar(string bits) {
	int dec = 0;

	for (int i = 0; i < bits.length(); i++)
	{
		// Thêm bit vaÌo trong dec 
		if (bits[i] == '1') dec += 1;
		// Dịch bit qua trái
		dec <<= 1;
	}
	// Diòch bit qua phaÒi ðêÒ loaòi boÒ bit dý cuôìi
	dec >>= 1;

	return (char)dec;
}

// Xây dýòng baÒng tra cýìu neìn týÌ Huffman Codes
HashTable<string>* buildCompressTable(vector<HuffmanCode*> huffCodes) {
	HashTable<string>* table = new HashTable<string>("string");
	
	for (int i = 0; i < huffCodes.size(); i++)
	{
		table->insert(huffCodes[i]->c, huffCodes[i]->code);
	}

	return table;
}

// Taòo daÞy bit týÌ text dýòa vaÌo baÒn tra cýìu neìn
string getSequenceOfBit(string text, HashTable<string>* table) {
	string sequence = "";

	for (int i = 0; i < text.length(); i++)
	{
		sequence += table->get(text[i]);
	}

	return sequence;
}

// HaÌm thêm sôì 0 sau daÞy cho ðuÒ bit vaÌ traÒ vêÌ sôì bit ðaÞ thêm
int fillBit(string &sequenceOfBit) {
	int addedBit = 8 - (sequenceOfBit.length() % 8);
	cout << "addbit: " << addedBit << endl;
	// Thêm sôì 0 sau daÞy cho ðuÒ bit
	for (int i = 0; i < addedBit; i++)
	{
		sequenceOfBit += '0';
	}

	return addedBit;
}

// Tạo chuỗi text mới từ dãy bit mới
string getNewText(string sequenceOfBit) {
	int pos = 0;
	int length = sequenceOfBit.length();
	string newText = "";

	// Duyêòt môÞi 8 bit ðêÒ chuyêÒn thaÌnh char
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

	// Taòo daÞy bit týÌ text dýòa trên baÒng tra cýìu neìn
	string sequenceOfBit = getSequenceOfBit(text, table);

	// Thêm sôì 0 vaÌo sau daÞy bit cho ðôò daÌi laÌ bôòi cuÒa 8
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

void compressFile(const wchar_t path[100]) {

	wstring str = getStringFromFile(path);
	string content = WidestringToString(str);
	vector<HuffNode*> freqTable = initFreqTable(content);
	string fname = "compress";

	compressToFile("compress", freqTable, content);

}

void compressFolder(const wchar_t path[100]) {
	WIN32_FIND_DATA data;
	// Tìm tập tin đầu tiên
	HANDLE hFile = FindFirstFile(path, &data);
	wstring s;

	do {
		//in tên thư mục, tập tin ra màn hình
		wprintf(L"%s\n", data.cFileName);
		//Nếu là thư mục
		if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			compressFolder(data.cFileName);
		}

		//Nếu là tập tin
		if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			//Nén tập tin
			/*wstring str = getStringFromFile(data.cFileName);
			string content = WidestringToString(str);
			vector<HuffNode*> freqTable = initFreqTable(content);
			string fname = "compress";

			compressToFile("compress", freqTable, content);*/
			compressFile(data.cFileName);
		}

	} while (FindNextFile(hFile, &data)); // Cho đến khi không còn tập tin kế

	FindClose(hFile);
}