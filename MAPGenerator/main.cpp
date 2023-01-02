#include "sdk.h"

#define FILE_PATH "E:\\dev\\MAPGenerator\\x64\\Debug\\TestXyinu.exe"

#define FILE_OUT "E:\\dev\\MAPGenerator\\x64\\Debug\\TestXyinu.map"


/*
* Точка входа в программу
*/
int main(int argc, char** argv)
{
	std::cout << "[+] MAPGenerator loading." << std::endl;

	//if (argc == 1) 
	//{
		//ShowHelp();
	//}

	//-file <path>
	std::cout << "[+] MAPGenerator. Reading binary file." << std::endl;
	char* binaryFile = ReadFile(FILE_PATH);

	std::cout << "[+] MAPGenerator. Writing MAP file." << std::endl;

	bool status = WriteMAPFile(FILE_OUT, binaryFile);

	if (status)
	{
		std::cout << "[+] MAPGenerator. Write Successfully!" << std::endl;
		free(binaryFile);
	}

	return 0;
}
