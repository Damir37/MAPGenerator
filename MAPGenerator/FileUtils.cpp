#define _CRT_SECURE_NO_WARNINGS

#include "FileUtils.h"

/*
* Передаём путь до нашего бинарного файла
* Возвращает байты, то, что удалось прочитать
*/
char* ReadFile(std::string path)
{
	std::ifstream fileStream;
	fileStream.open(path, std::ios::in | std::ios::binary);

	if (fileStream.fail())
	{
		std::cerr << "[X] MAPGenerator. Failed to open file!" << std::endl;
	}

	fileStream.seekg(0, std::ifstream::end);

	size_t sizeBuffer = fileStream.tellg();
	char* buffer = new char[sizeBuffer];

	fileStream.seekg(0, std::ios::beg);
	fileStream.read(buffer, sizeBuffer);
	fileStream.close();

	std::cout << "[+] MAPGenerator. Reading Successfully." << std::endl;

	return buffer;
}


/*
* Пишет МАП файл
* По хорошему ее надо разбить
* pathToWrite - куда будем писать MAP файл
* binaryFile - Наш файл который мы считали
*/
bool WriteMAPFile(std::string pathToWrite, char* binaryFile)
{
	std::ofstream mapFileOutput;
	mapFileOutput.open(pathToWrite);

	if (!mapFileOutput.is_open())
	{
		std::cerr << "[X] MAPGenerator. Failed to open file!" << std::endl;
		return false;
	}

	ULONG imageAddress = GetImageBase(binaryFile);

	if (!imageAddress)
	{
		std::cerr << "[X] MAPGenerator. Failed to get ImageBase Address!" << std::endl;
		return false;
	}

	std::cout << "[+] MAPGenerator. Get ImageBase Address!" << std::endl;
	

	time_t times = GetTimeStamp(binaryFile);
	if (!times)
	{
		std::cerr << "[X] MAPGenerator. Failed to get TimeStamp!" << std::endl;
		return false;
	}

	std::cout << "[+] MAPGenerator. Get TimeStamp!" << std::endl;

	std::string hexTime = DecToHex<time_t>(times);

	struct tm* utc;
	char* gmt;
	utc = localtime(&times);
	gmt = SetTimeGMT(utc);

	if (!gmt)
	{
		std::cerr << "[X] MAPGenerator. Failed to get GMT time!" << std::endl;
		return false;
	}

	std::cout << "[+] MAPGenerator. Get GMT time!" << std::endl;

	std::string GMTtime = " (";
	GMTtime += gmt;
	GMTtime += ")";

	DWORD EntryPoint = GetEntryPoint(binaryFile);

	if (!EntryPoint)
	{
		std::cerr << "[X] MAPGenerator. Failed to get EntryPoint!" << std::endl;
		return false;
	}

	std::cout << "[+] MAPGenerator. Get EntryPoint!" << std::endl;

	mapFileOutput << " " << "nameFile #edit file name" << std::endl;
	mapFileOutput << "\n Timestamp is " << hexTime << GMTtime << std::endl;
	mapFileOutput << "\n Preferred load address is " << DecToHex<ULONG>(imageAddress) << std::endl;
	mapFileOutput << "\n Start         Length     Name                   Class" << std::endl;
	for (std::string str : GetSections(binaryFile))
	{
		mapFileOutput << " ";
		mapFileOutput << str << std::endl;
	}
	mapFileOutput << "#Change section .text or .code  DATA->CODE!" << std::endl;
	std::cout << "[+] MAPGenerator. Get Sections!" << std::endl;
	mapFileOutput << "\n  Address         Publics by Value              Rva+Base               Lib:Object" << std::endl;
	mapFileOutput << "#Primer: 0001:000991A78       func1!" << std::endl;
	mapFileOutput << "\n\n  entry point at        0001:00" << DecToHex<DWORD>(EntryPoint) << std::endl;

	free(gmt);


	return true;
}