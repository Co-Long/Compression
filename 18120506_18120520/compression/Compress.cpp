﻿#include "Compress.h"

// Bin to Char
char bitsToChar(string bits) {
	int dec = 0;

	for (int i = 0; i < bits.length(); i++)
	{
		// Add bit
		if (bits[i] == '1') dec += 1;
		// shift left
		dec <<= 1;
	}
	// shift right to remove excess bit
	dec >>= 1;

	return (char)dec;
}

// Build Huffman Codes
HashTable<string>* buildCompressTable(vector<HuffmanCode*>& huffCodes) {
	HashTable<string>* table = new HashTable<string>("string");
	
	for (int i = 0; i < huffCodes.size(); i++)
	{
		table->insert(huffCodes[i]->c, huffCodes[i]->code);
	}

	return table;
}

void compress(string filename, vector<HuffNode*> freqTable, HashTable<string>* table, string text) {
	ofstream fo;
	fo.open(filename, ios::binary);

	// write freq table size 
	int size = freqTable.size();

	fo.write((char*)& size, sizeof(int));

	// write freq table
	for (int i = 0; i < size; i++)
	{
		fo.write((char*)freqTable[i], sizeof(HuffNode));
	}
	
	// write compressed text
	int temp = 0;
	int count = 0;
	int length = 0;
	for (int i = 0; i < text.length(); i++) {
		string* bin = table->get(text[i]);
		// Add bits to bin
		for (int j = 0; j < (*bin).length(); j++) {
			if ((*bin)[j] == '1') {
				temp += 1;
			}
			else {
				temp += 0;
			}
			count++;
			// When bin length is 8, write it to file 
			if (count == 8) {
				length++;
				char c = temp;
				fo.write(&c, 1);
				temp = 0;
				count = 0;

			}
			else temp <<= 1;
		}
	}

	// Add 0-bits to fill last bin
	int addedBit = 0;
	if (count > 0) {
		while (count != 8) {
			addedBit++;
			temp <<= 1;
			count++;
		}

		temp >>= 1;
		char c = temp;
		fo.write(&c, 1);

	}
	// write numbers of added bits to file
	fo.write((char*)& addedBit, sizeof(int));
}

void compressToFile(string filename, vector<HuffNode*>& freqTable, string text) {
	// Create list of huff codes from freq table and build compress table
	vector<HuffmanCode*> huffCodes = HuffmanCodes(freqTable);
	HashTable<string>* table = buildCompressTable(huffCodes);

	// Compress
	compress(filename, freqTable, table, text);
}

void compressFile(const boost::filesystem::path& relative_path, string output) {
	string fname = relative_path.generic_path().generic_string();
	
	// Read text from file then initialize freq table
	string str = getStringFromFile(fname);
	vector<HuffNode*> freqTable = initFreqTable(str);

	compressToFile(output, freqTable, str);

	// Delete freq table
	for (int i = 0; i < freqTable.size(); i++)
	{
		delete freqTable[i];
	}
}

//Input: Đường dẫn thư mục cần nén, đây có phải là thư mục gốc hay sub Folder, đường dẫn sub Folder
//Nếu là thư mục gốc thì tham số cuối là chuỗi rỗng
void compressFolder(const boost::filesystem::path& relative_path,bool root, string rname) {
	string s;
	using namespace boost::filesystem;

	if (!boost::filesystem::exists(relative_path)) {
		cerr << relative_path << " does not exist!" << endl;
		return;
	}
	
	string name;
	if (root && is_directory(relative_path)) {
		_chdir(relative_path.generic_path().generic_string().c_str());
		name = current_path().generic_path().generic_string() + "_compress";
		create_directories(name);
		cout << "Root: " << endl;
		cout << relative_path.generic_path().generic_string().c_str() << endl;
		cout << name << endl;
		cout << "----------------------------" << endl;
	}
	else {
		name = rname;
		_chdir(rname.c_str()); //Cho lá
	}
	
	//Duyệt thư mục
	boost::filesystem::directory_iterator end_itr;

	for (boost::filesystem::directory_iterator itr(relative_path); itr != end_itr; itr++) {
		if (boost::filesystem::is_directory(*itr)) {
			path Sub(*itr);
			_chdir(name.c_str());
			string subname = Sub.filename().generic_string() + "_compress";
			subname= current_path().generic_path().generic_string() + "\\" + subname;
			cout << "cwd: " << current_path() << endl;
			cout << "Directory: " << endl;
			cout << subname << endl;
			
			create_directories(subname);
			compressFolder(*itr, false, subname);
		}
		else {
			_chdir(name.c_str()); 
			cout << "cwd: " << current_path() << endl;
			cout << "**** FILE ***" << endl;
			path File(*itr);
			string fname =File.filename().generic_string() + "_compress";
			cout << "File: " << fname << endl;
			compressFile(*itr, fname);
			}
	}
}
