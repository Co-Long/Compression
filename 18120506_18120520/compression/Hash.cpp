#include"Hash.h"

using namespace std;


//Init Frequence Table
//Input: text, output: HuffNode Table
vector<HuffNode*> initFreqTable(string str) {
	HashTable hash;
	vector<HuffNode*> freqTable(0);

	for (int i = 0; i < str.length(); i++) {
		hash.insert(str[i]);
	}
	vector<int> hashTable = hash.getTable();

	for (int i = 0; i < MAX; i++) {
		if (hashTable[i] != 0) {
			freqTable.push_back(newNode((char)i, hashTable[i]));
		}
	}

	return freqTable;
}
//Get content from a file
//Input: file name, output: content in file
string getStringFromFile(string filename) {
	ifstream fi;
	fi.open(filename);
	if (!fi) return "";

	string str = "";
	while (!fi.eof()) {
		string temp;
		getline(fi, temp);
		str += temp + '\n';
	}

	return str;
}