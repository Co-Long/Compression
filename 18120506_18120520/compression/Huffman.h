﻿#pragma once
#include<iostream>
#include<vector>
#define MAX_TREE_HT 100 

using namespace std;

// A Huffman tree node 
struct HuffNode {

	// One of the input characters 
	char data;

	// Frequency of the character 
	unsigned freq;

	// Left and right child of this node 
	HuffNode* left;
	HuffNode* right;
};

// A Min Heap:  Cây Huffman.
struct MinHeap {

	// Số HuffNode hiện tại có trong cây
	unsigned size;

	// Số lượng HuffNode tối đa mà cây có thể lưu trữ
	unsigned capacity;

	// Array of HuffNode pointers 
	HuffNode** array;
};

struct HuffmanCode {
	char c;
	string code;
};

// Tạo một Node mới
HuffNode* newNode(char data, unsigned freq);
// Tạo một cây mới, cấp phát vùng nhớ
MinHeap* createMinHeap(unsigned capacity);
// Heappify
void minHeapify(MinHeap* minHeap, int idx);
// Sắp xếp cây thành min heap
void buildMinHeap(MinHeap* minHeap);
// Tạo ra một min heap có size Node.
// Mỗi Node chứa một ký tự từ mảng data và trọng số tương ứng trong mảng freq
MinHeap* createAndBuildMinHeap(vector<HuffNode*> freqTable);


// Swap 2 Node
void swapHuffNode(HuffNode** a, HuffNode** b);
// Kiểm tra có đúng 1 phần tử trong cây
int isSizeOne(MinHeap* minHeap);
// Lấy ra Node có trọng số nhỏ nhất 
// Là node đầu tiên trong min heap
HuffNode* extractMin(struct MinHeap* minHeap);
// Thêm một Node mới vào cây
void insertMinHeap(MinHeap* minHeap, HuffNode* NewNode);
// In mảng có n phần tử
void printArr(int arr[], int n);
// Kiểm tra xem Node có phải lá không
bool isLeaf(HuffNode* root);

// Xây dựng cây Huffman
HuffNode* buildHuffmanTree(vector<HuffNode*> freqTable);
// In bảng mã ra màn hình
// Dùng mảng arr để lưu mã
void printCodes(HuffNode* root, int arr[], int top, vector<HuffmanCode*>& out);
// Chuyển bit array sang dạng string
string bitArrToString(int arr[], int n);
vector<HuffmanCode*> HuffmanCodes(vector<HuffNode*>& freqTable);

