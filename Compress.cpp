#include "Compress.h"

bool Compress(std::string Compress_filename, std::string deCompress_filename)
{
	Node node[256];
	std::string CodeBuf;
	int Code_Length = 0;
	int File_Length = 0;
	int Code_Kinds = 0;
	Huffman Huffman_class;

	// ��ʼ�������� ͳ�ƽ��
	for (int i = 0; i < 256; i++)
	{
		node[i].first = (unsigned char)i;
		node[i].second = 0;
	}

	/* ���ļ� �ж�״̬ Ȼ��������ļ��������ַ����ֵ�Ƶ�ʽ��м��� ����֮�󹹽���������*/
	std::ifstream Read_Comp_file(Compress_filename, std::ios::in | std::ios::binary);
	if (!Read_Comp_file.is_open())
	{
		return false;
	}

	unsigned char c = '\0';
	while (Read_Comp_file.read((char*)&c, sizeof(unsigned char)))
	{
		node[c].second++;
		File_Length++;
	}
	Read_Comp_file.close();

	// ͳ���ַ�������
	// ���ַ�Ƶ�ʴ�С����
	std::sort(node, node + 256, [&](Node a, Node b) { return a.second > b.second; });
	for (int i = 0; i < 256; i++)
	{
		if (node[i].second)
			Code_Kinds++;
		else
			break;
	}

	// ѹ�� 
	std::ofstream Write_deComp_file(deCompress_filename, std::ios::out | std::ios::binary);
	if (!Write_deComp_file.is_open())
	{
		return false;
	}
	c = '\0';

	// ֻ��һ���ַ� ���⴦��
	if (Code_Kinds == 1)
	{
		Write_deComp_file.write((const char*)&Code_Kinds, sizeof(int));

		Write_deComp_file.write((const char*)&node[0].first, sizeof(unsigned char));
		Write_deComp_file.write((const char*)&node[0].second, sizeof(int));
	}
	else
	{
		// ������������
		int Nums_of_HuffmanNode = 2 * Code_Kinds - 1;
		HuffmanNode* HuffmanTree = Huffman_class.CreatHuffmanTree(node, Code_Kinds, Nums_of_HuffmanNode);

		// ���ɹ��������� �洢��HuffmanCodes�� (ʹ������)
		Huffman_class.getHuffmanCode(HuffmanTree, "");

		// �Ƚ��ַ����࣬�ַ���Ƶ�ʣ��ļ���������д��ѹ���ļ���ǰ����
		Write_deComp_file.write((const char*)&Code_Kinds, sizeof(int));
		for (int i = 0; i < Code_Kinds; i++)
		{
			Write_deComp_file.write((const char*)&node[i].first, sizeof(unsigned char));
			Write_deComp_file.write((const char*)&node[i].second, sizeof(int));
		}
		Write_deComp_file.write((const char*)&File_Length, sizeof(int));
		std::map<unsigned char, std::string>HuffmanCodes = Huffman_class.codes;
		//���ַ�����д��ѹ���ļ�
		Read_Comp_file.open(Compress_filename);
		while (Read_Comp_file.read((char*)&c, sizeof(unsigned char)))
		{
			
			// �ҵ�����ַ���Ӧ�Ĺ���������
			CodeBuf += HuffmanCodes[c];

			// ��8bitһ�� д����������� ����Ϊunsigned char��8λ���������ж��char�����һ�� �γ�һ��unsigned char ����CodeBuf������գ�
			while (CodeBuf.size() >= 8)
			{
				c = '\0';
				for (int i = 0; i < 8; i++) 
				{
					c <<= 1;
					if (CodeBuf[i] == '1')
						c |= 1;
				}
				Write_deComp_file.write((const char*)&c, sizeof(unsigned char));

				// ǰ��λ������ ɾȥ
				size_t len = CodeBuf.size() - 8;
				CodeBuf = CodeBuf.substr(8, len);
			}
		}

		// ʣ�µ��ַ�����8�� �����Ҫ��c���� ֱ�����λ��8
		size_t(Code_Length) = CodeBuf.size();
		if (Code_Length > 0)
		{
			c = '\0';
			for (size_t i = 0; i < Code_Length; i++)
			{
				c <<= 1;
				if ('1' == CodeBuf[i])
					c |= 1;
			}
			c <<= (8 - Code_Length);
			Write_deComp_file.write((const char*)&c, sizeof(unsigned char));
		}
	}

	Huffman_class.Show_Huffman_Code();

	Write_deComp_file.close();
	Read_Comp_file.close();
	return true;
}