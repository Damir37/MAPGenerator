#define _CRT_SECURE_NO_WARNINGS

#include "PEUtils.h"

/*
* Здесь можно использовать инлайны, но я без них обошёлся
* Функция получает время, когда собран был бинарник
* hModule - передаём туда наш модуль
* Возвращает либо время, 0 если модуль не найден
*/
time_t GetTimeStamp(PVOID hModule)
{
	if (hModule != NULL)
	{
		PIMAGE_NT_HEADERS imageApi = ImageNtHeader(hModule);
		time_t timestamp = imageApi->FileHeader.TimeDateStamp;

		return timestamp;
	}

	return 0;
}

/*
* Функция возвращает ImageBase
* 0 - если модуль не найден
*/
ULONG GetImageBase(PVOID hModule)
{
	if (hModule != NULL)
	{
		PIMAGE_NT_HEADERS imageApi = ImageNtHeader(hModule);
		ULONG imageBase = imageApi->OptionalHeader.ImageBase;

		return imageBase;
	}

	return 0;
}


/*
* Получаем данные о секциях
* 1 - это номер 000n n - номер 1, 2 и т.д.
* 2 - это RAW Data
* 3 - это виртуальный размер
* 4 - это название
* 5 - это тип (DATA - там где хранятся данные CODE - исполняймая секция) Т.к. бинарник может быть не на С++
* Либо по дупаковщиком исполняймую секцию надо руками вправлять
* пример, что можно получить с функции: 0001:0000000000000400 0000000000001FBEH .text    		CODE
*/
std::vector<std::string> GetSections(PVOID hModule)
{
	if (hModule != NULL)
	{

		PIMAGE_NT_HEADERS imageApi = ImageNtHeader(hModule);
		PIMAGE_SECTION_HEADER pSecHeader;

		char tmp[100];
		int i = 0;
		std::vector<std::string> sections;

		for (pSecHeader = IMAGE_FIRST_SECTION(imageApi), i = 0; i < imageApi->FileHeader.NumberOfSections; i++, pSecHeader++)
		{
			
			std::snprintf(tmp, sizeof(tmp), "000%d:%016X %016XH %-8.8s \t\tDATA", i + 1, pSecHeader->PointerToRawData, 
						  pSecHeader->Misc.VirtualSize, pSecHeader->Name);

			std::string secStr = tmp;

			sections.push_back(secStr);

		}

		return sections;
	
	}

}

/*
* Функция получает EntryPoint - ну или же точку входа
*/
DWORD GetEntryPoint(PVOID hModule)
{
	if (hModule != NULL)
	{
		PIMAGE_NT_HEADERS imageApi = ImageNtHeader(hModule);
		IMAGE_OPTIONAL_HEADER opHeader;

		opHeader = imageApi->OptionalHeader;

		return opHeader.AddressOfEntryPoint;
	}

	return 0;
}