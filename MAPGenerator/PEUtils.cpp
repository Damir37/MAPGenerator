#define _CRT_SECURE_NO_WARNINGS

#include "PEUtils.h"

/*
* ����� ����� ������������ �������, �� � ��� ��� ��������
* ������� �������� �����, ����� ������ ��� ��������
* hModule - ������� ���� ��� ������
* ���������� ���� �����, 0 ���� ������ �� ������
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
* ������� ���������� ImageBase
* 0 - ���� ������ �� ������
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
* �������� ������ � �������
* 1 - ��� ����� 000n n - ����� 1, 2 � �.�.
* 2 - ��� RAW Data
* 3 - ��� ����������� ������
* 4 - ��� ��������
* 5 - ��� ��� (DATA - ��� ��� �������� ������ CODE - ����������� ������) �.�. �������� ����� ���� �� �� �++
* ���� �� ������������ ����������� ������ ���� ������ ���������
* ������, ��� ����� �������� � �������: 0001:0000000000000400 0000000000001FBEH .text    		CODE
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
* ������� �������� EntryPoint - �� ��� �� ����� �����
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