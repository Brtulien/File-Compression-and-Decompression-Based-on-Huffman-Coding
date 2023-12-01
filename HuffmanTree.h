#pragma once

#include <map>
#include <cstring>
#include <queue>

#include "Node.h"

class Huffman
{
public:

	// ���ȶ��еıȽϷ�ʽ �ԡ��ַ���Ƶ�ʡ���Ƶ������
	bool operator()(HuffmanNode* a, HuffmanNode* b) const {
		return a->codeNode.second > b->codeNode.second;
	}

	HuffmanNode* CreatHuffmanTree(Node* node, int Code_kinds, int Nums_of_HuffmanNode);

	void getHuffmanCode(HuffmanNode* HuffmanTree, std::string code);

	void Show_Huffman_Code();

	std::map<unsigned char, std::string>codes;
};

