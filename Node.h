#pragma once

#include <iostream>

// Node 是 字符的结构 存储每个字符及其出现的次数
typedef std::pair<unsigned char, int> Node;

/* HuffmanNode的定义 需要有字符结点作为数据域
code 是所有字符的集合（共256个） 
需要有父节点 左右子节点*/
struct HuffmanNode
{
	Node codeNode;
	HuffmanNode* lchild, * rchild;

	HuffmanNode(Node codeNode) :codeNode(codeNode), lchild(nullptr), rchild(nullptr) {};
};