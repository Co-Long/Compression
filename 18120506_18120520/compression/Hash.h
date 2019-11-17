#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include"Huffman.h"
using namespace std;
#define MAX 256

//Hash Table
class HashTable {
private:
	vector<int> table;
public:
	HashTable() {
		table.resize(MAX, 0);
	}
	//Get hash key for character
	//Input: char, output: hashKey
	int getHash(char c) {
		return (int)c % MAX;
	}
	//Insert freq to table using hashKey
	void insert(char c) {
		int key = getHash(c);
		table[key]++;
	}
	//Return table
	const vector<int>& getTable() {
		return this->table;
	}
};

//Init Frequence Table
//Input: text, output: HuffNode Table
vector<HuffNode*> initFreqTable(string str);
//Get content from a file
//Input: file name, output: content in file
string getStringFromFile(string filename);