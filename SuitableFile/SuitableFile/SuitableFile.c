#include <stdio.h>
#include <windows.h>
#include <conio.h>

int main()
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	hf = FindFirstFile(L"*.txt*", &FindFileData);
	if (hf != INVALID_HANDLE_VALUE)
	{
		do
		{
			if((FindFileData.nFileSizeHigh*(MAXDWORD * 1) + FindFileData.nFileSizeLow) > 20){ printf("%S\n", FindFileData.cFileName); }
		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}
	hf = FindFirstFile(L"*.exe*", &FindFileData);
	if (hf != INVALID_HANDLE_VALUE)
	{
		do
		{
			printf("%S\n", FindFileData.cFileName);
		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}
	_getch();
	return 0;
}