#include <iostream>
#include <cstring>
#include <ctime>
#include <vector>

#include "Compress.h"
#include "deCompress.h"

int main()
{
	bool flag;
	std::string Compress_filename, deCompress_filename, Original_filename;

	while (true)
	{
		std::cout << "\t____________________________________________\n";
		std::cout << "\t|__________________________________________|\n";
		std::cout << "\t|_________Press 'C' to Compress file_______|\n";
		std::cout << "\t|_________Press 'D' to deCompress file_____|\n";
		std::cout << "\t|_________Press 'Q' to Quit _______________|\n";
		std::cout << "\t|__________________________________________|\n";
		std::cout << "\t|__________________________________________|\n";
		std::cout << "\n";
		char choice;
		do 
		{
			std::cout << "Please selece a function\n";
			std::cin >> choice;
			choice = toupper(choice);
			if (choice != 'C' && choice != 'D' && choice != 'Q')
				std::cout << "Input error, please enter again\n";
		} while (choice != 'C' && choice != 'D' && choice != 'Q');

		if (choice == 'Q')break;
		else if (choice == 'C')
		{
			clock_t begin_Compress, end_Compress;

			std::cout << "Please enter the filename to be compressed: ";
			std::cin >> Compress_filename;
			std::cout << "\n";
			std::cout << "Please enter the filename to store the decompressd data: ";
			std::cin >> deCompress_filename;
			std::cout << "\n";
			
			begin_Compress = clock();
			std::cout << "Compressing...\n";
			flag = Compress(Compress_filename, deCompress_filename);
			end_Compress = clock();
			std::cout << "\n";
			
			if (flag == false)
			{
				std::cout << "Fail to open the file\n";
				exit(1);
			}
			else
			{
				std::cout << "Compress completed\ntotal time elapsed: " << (end_Compress - begin_Compress) / 1000.0 << "/s\n";
			}
		}
		else if (choice == 'D')
		{
			clock_t begin_deCompress, end_deCompress;

			std::cout << "Please enter the filename to be decompressed: ";
			std::cin >> deCompress_filename;
			std::cout << "\n";
			std::cout << "Please enter the filename to store the data: ";
			std::cin >> Original_filename;
			std::cout << "\n";

			begin_deCompress = clock();
			std::cout << "deCompressing...\n";
			flag = deCompress(deCompress_filename, Original_filename);
			end_deCompress = clock();
			std::cout << "\n";

			if (flag == false)
			{
				std::cout << "Fail to open the file\n";
				exit(1);
			}
			else
			{
				std::cout << "deCompress completed\ntotal time elapsed: " << (end_deCompress - begin_deCompress) / 1000.0 << "/s\n";
			}
		}

		std::cout << "Press any key to continue\n";

		system("pause");
		system("cls");
	}
	std::cout << "Thank you for using\n";
	return 0;
}