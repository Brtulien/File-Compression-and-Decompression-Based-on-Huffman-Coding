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

	// ��ѹ���ļ���ȡ�ַ�����
	Read_deComp_file.read((char*)&Code_Kinds, sizeof(int));
	
	// ������� ֻ��һ���ַ� ֱ�ӻ�ԭ
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
		
		// ��ѹ���ļ����ַ���Ƶ��д���� ���ɹ�������
		for (int i = 0; i < Code_Kinds; i++)
		{
			Read_deComp_file.read((char*)&c, sizeof(unsigned char));
			Read_deComp_file.read((char*)&Code_freq, sizeof(int));
			node[i].first = c;
			node[i].second = Code_freq;
		}
		HuffmanNode* HuffmanTree = Huffman_class.CreatHuffmanTree(node, Code_Kinds, Nums_of_HuffmanNode);

		// ��ȡ�ļ����� �����ж��Ƿ��ȡ���������ļ�
		Read_deComp_file.read((char*)&File_Length, sizeof(int));

		// ��ʼ��ѹ��
		// ÿ�δӸ��ڵ㿪ʼ ����0������ ����1������ ������ڵ��˵���ҵ���һ���ַ�
		HuffmanNode* Root = HuffmanTree;
		while (true) 
		{
			Read_deComp_file.read((char*)&c, sizeof(unsigned char));
			
			for (int i = 0; i < 8; i++)
			{
				// �Ӹ�λ��ʼȡ
				if (c & 128)
				{
					Root = Root->rchild;
				}
				else
				{
					Root = Root->lchild;
				}

				// ����Ҷ�ӽ��
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
