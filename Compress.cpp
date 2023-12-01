#include "Compress.h"

bool Compress(std::string Compress_filename, std::string deCompress_filename)
{
	Node node[256];
	std::string CodeBuf;
	int Code_Length = 0;
	int File_Length = 0;
	int Code_Kinds = 0;
	Huffman Huffman_class;

	// 初始化编码域 统计结点
	for (int i = 0; i < 256; i++)
	{
		node[i].first = (unsigned char)i;
		node[i].second = 0;
	}

	/* 打开文件 判断状态 然后对整个文件的所有字符出现的频率进行计数 用于之后构建哈夫曼树*/
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

	// 统计字符的种类
	// 按字符频率大小排序
	std::sort(node, node + 256, [&](Node a, Node b) { return a.second > b.second; });
	for (int i = 0; i < 256; i++)
	{
		if (node[i].second)
			Code_Kinds++;
		else
			break;
	}

	// 压缩 
	std::ofstream Write_deComp_file(deCompress_filename, std::ios::out | std::ios::binary);
	if (!Write_deComp_file.is_open())
	{
		return false;
	}
	c = '\0';

	// 只有一种字符 特殊处理
	if (Code_Kinds == 1)
	{
		Write_deComp_file.write((const char*)&Code_Kinds, sizeof(int));

		Write_deComp_file.write((const char*)&node[0].first, sizeof(unsigned char));
		Write_deComp_file.write((const char*)&node[0].second, sizeof(int));
	}
	else
	{
		// 创建哈夫曼树
		int Nums_of_HuffmanNode = 2 * Code_Kinds - 1;
		HuffmanNode* HuffmanTree = Huffman_class.CreatHuffmanTree(node, Code_Kinds, Nums_of_HuffmanNode);

		// 生成哈夫曼编码 存储到HuffmanCodes中 (使用引用)
		Huffman_class.getHuffmanCode(HuffmanTree, "");

		// 先将字符种类，字符，频率，文件长度依次写入压缩文件的前部分
		Write_deComp_file.write((const char*)&Code_Kinds, sizeof(int));
		for (int i = 0; i < Code_Kinds; i++)
		{
			Write_deComp_file.write((const char*)&node[i].first, sizeof(unsigned char));
			Write_deComp_file.write((const char*)&node[i].second, sizeof(int));
		}
		Write_deComp_file.write((const char*)&File_Length, sizeof(int));
		std::map<unsigned char, std::string>HuffmanCodes = Huffman_class.codes;
		//将字符编码写入压缩文件
		Read_Comp_file.open(Compress_filename);
		while (Read_Comp_file.read((char*)&c, sizeof(unsigned char)))
		{
			
			// 找到这个字符对应的哈夫曼编码
			CodeBuf += HuffmanCodes[c];

			// 按8bit一组 写入哈夫曼编码 （因为unsigned char是8位）（可能有多个char组合在一起 形成一个unsigned char 所以CodeBuf不能清空）
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

				// 前八位已填入 删去
				size_t len = CodeBuf.size() - 8;
				CodeBuf = CodeBuf.substr(8, len);
			}
		}

		// 剩下的字符不足8个 最后需要让c左移 直到最高位在8
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