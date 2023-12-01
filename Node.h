#pragma once

#include <iostream>

// Node �� �ַ��Ľṹ �洢ÿ���ַ�������ֵĴ���
typedef std::pair<unsigned char, int> Node;

/* HuffmanNode�Ķ��� ��Ҫ���ַ������Ϊ������
code �������ַ��ļ��ϣ���256���� 
��Ҫ�и��ڵ� �����ӽڵ�*/
struct HuffmanNode
{
	Node codeNode;
	HuffmanNode* lchild, * rchild;

	HuffmanNode(Node codeNode) :codeNode(codeNode), lchild(nullptr), rchild(nullptr) {};
};