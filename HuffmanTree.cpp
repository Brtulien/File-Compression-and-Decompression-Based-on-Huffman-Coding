#include "HuffmanTree.h"

HuffmanNode* Huffman::CreatHuffmanTree(Node* node, int Code_kinds, int Nums_of_HuffmanNode)
{
	std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Huffman>select_Node;

	// 初始化 加入所有结点
	for (int i = 0; i < 256; i++)
	{
		if (node[i].second)
		{
			HuffmanNode* temp = new HuffmanNode(node[i]);
			select_Node.push(temp);
		}
	}

	// 生成哈夫曼树
	while (select_Node.size() > 1)
	{
		HuffmanNode* left = select_Node.top();
		select_Node.pop();

		HuffmanNode* right = select_Node.top();
		select_Node.pop();

		HuffmanNode* parent = new HuffmanNode(Node('$', left->codeNode.second + right->codeNode.second));
		parent->lchild = left;
		parent->rchild = right;

		select_Node.push(parent);
	}

	return select_Node.top();
}

void Huffman::getHuffmanCode(HuffmanNode* HuffmanTree, std::string code)
{
	if (HuffmanTree == nullptr)
		return;

	if (!HuffmanTree->lchild && !HuffmanTree->rchild)
		Huffman::codes[HuffmanTree->codeNode.first] = code;

	// 递归结构：向左一位就加一个0 向右一位就加一个1 最终到叶子节点的时候 整条路径的-01值就是他的哈夫曼编码 
	getHuffmanCode(HuffmanTree->lchild, code + '0');
	getHuffmanCode(HuffmanTree->rchild, code + '1');
}

void Huffman::Show_Huffman_Code()
{
	std::cout << "The HuffmanCodes for each character are as follows:\n";
	std::map<unsigned char, std::string>codes = Huffman::codes;
	int i = 0;
	for (auto code : codes)
	{
		std::cout << code.first << "\t:" << code.second << "\n";
	}
}