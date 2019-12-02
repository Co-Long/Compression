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
HashTable<string>* buildCompressTable(vector<HuffmanCode*>& huffCodes) {
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

void compressToFile(string filename, vector<HuffNode*>& freqTable, string text) {
	vector<HuffmanCode*> huffCodes = HuffmanCodes(freqTable);
	cout<<"SIZE: "<< huffCodes.size() << endl;
	HashTable<string>* table = buildCompressTable(huffCodes);
	
	// Taòo daÞy bit týÌ text dýòa trên baÒng tra cýìu neìn
	string sequenceOfBit = getSequenceOfBit(text, table);

	// Thêm sôì 0 vaÌo sau daÞy bit cho ðôò daÌi laÌ bôòi cuÒa 8
	int addedBit = fillBit(sequenceOfBit);
	string newText = getNewText(sequenceOfBit);

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

void compressFile(const boost::filesystem::path& relative_path, string output) {
	string fname = relative_path.generic_path().generic_string();
	
	string str = getStringFromFile(fname);
	vector<HuffNode*> freqTable = initFreqTable(str);

	compressToFile(output, freqTable, str);

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
