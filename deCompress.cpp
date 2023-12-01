#include "deCompress.h"

bool deCompress(std::string deCompress_filename, std::string Original_filename)
{
	Node node[256];
	unsigned char c = '\0';
	int Code_Kinds = 0;
	int File_Length = 0;
	int Code_freq = 0;
	int Now_Length = 0;
	Huffman Huffman_class;

	std::ifstream Read_deComp_file(deCompress_filename, std::ios::in | std::ios::binary);
	if (!Read_deComp_file.is_open())
	{
		return false;
	}
	std::ofstream Write_Ori_file(Original_filename, std::ios::out | std::ios::binary);
	if (!Write_Ori_file.is_open())
	{
		return false;
	}

	// 从压缩文件提取字符种类
	Read_deComp_file.read((char*)&Code_Kinds, sizeof(int));
	
	// 特殊情况 只有一个字符 直接还原
	if (Code_Kinds == 1)
	{
		Read_deComp_file.read((char*)&c, sizeof(unsigned char));
		Read_deComp_file.read((char*)&File_Length, sizeof(int));
		
		while (--File_Length)
		{
			Write_Ori_file.write((const char*)&c, sizeof(unsigned char));
		}
	}
	else
	{
		int Nums_of_HuffmanNode = 2 * Code_Kinds - 1;
		
		// 将压缩文件的字符和频率写入结点 建成哈夫曼树
		for (int i = 0; i < Code_Kinds; i++)
		{
			Read_deComp_file.read((char*)&c, sizeof(unsigned char));
			Read_deComp_file.read((char*)&Code_freq, sizeof(int));
			node[i].first = c;
			node[i].second = Code_freq;
		}
		HuffmanNode* HuffmanTree = Huffman_class.CreatHuffmanTree(node, Code_Kinds, Nums_of_HuffmanNode);

		// 读取文件长度 用于判断是否读取完了整个文件
		Read_deComp_file.read((char*)&File_Length, sizeof(int));

		// 开始解压缩
		// 每次从根节点开始 遇到0就左移 遇到1就右移 到达根节点就说明找到了一个字符
		HuffmanNode* Root = HuffmanTree;
		while (true) 
		{
			Read_deComp_file.read((char*)&c, sizeof(unsigned char));
			
			for (int i = 0; i < 8; i++)
			{
				// 从高位开始取
				if (c & 128)
				{
					Root = Root->rchild;
				}
				else
				{
					Root = Root->lchild;
				}

				// 到达叶子结点
				if ((Root->lchild == nullptr && Root->rchild == nullptr))
				{
					Write_Ori_file.write((const char*)&Root->codeNode.first, sizeof(unsigned char));
					Now_Length++;
					if (Now_Length == File_Length)
					{
						break;
					}
					Root = HuffmanTree;
				}
				c <<= 1;
			}
			if (Now_Length == File_Length)
			{
				break;
			}
		}
	}

	Read_deComp_file.close();
	Write_Ori_file.close();
	return true;
}
