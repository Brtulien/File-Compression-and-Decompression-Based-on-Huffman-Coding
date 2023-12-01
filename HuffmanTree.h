#pragma once

#include <map>
#include <cstring>
#include <queue>

#include "Node.h"

class Huffman
{
public:

	// 优先队列的比较方式 对【字符：频率】按频率排序
	bool operator()(HuffmanNode* a, HuffmanNode* b) const {
		return a->codeNode.second > b->codeNode.second;
	}

	HuffmanNode* CreatHuffmanTree(Node* node, int Code_kinds, int Nums_of_HuffmanNode);

	void getHuffmanCode(HuffmanNode* HuffmanTree, std::string code);

	void Show_Huffman_Code();

	std::map<unsigned char, std::string>codes;
};

