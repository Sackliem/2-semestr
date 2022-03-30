#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "netapi32.lib")

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <lm.h>
#include <locale.h>
#include <time.h>

#pragma warning(disable : 4996)

void getUserInfo(char* localname) {
	printf("getUserInfo:\n");
	NET_API_STATUS status;
	LPUSER_INFO_1 pBuf1 = NULL;
	status = NetUserGetInfo(0, localname, 1, (LPBYTE*)&pBuf1);

	if (status == NERR_Success)
	{
		if (pBuf1 != NULL)
		{
			wprintf(L"\tUser account name: %s\n", pBuf1->usri1_name);
			wprintf(L"\tPassword: %s\n", pBuf1->usri1_password);
			wprintf(L"\tPassword age (seconds): %d\n",pBuf1->usri1_password_age);
			wprintf(L"\tPrivilege level: %d\n", pBuf1->usri1_priv);
			wprintf(L"\tHome directory: %s\n", pBuf1->usri1_home_dir);
			wprintf(L"\tUser comment: %s\n", pBuf1->usri1_comment);
			wprintf(L"\tFlags (in hex): %x\n", pBuf1->usri1_flags);
			wprintf(L"\tScript path: %s\n", pBuf1->usri1_script_path);
		}
	}
	printf("\n");
}

void sysinfo() {
	printf("sysinfo:\n");
	char buff[MAX_COMPUTERNAME_LENGTH+1];
	unsigned long size = MAX_COMPUTERNAME_LENGTH + 1;
	GetComputerNameA(buff, &size);
	printf("\tComputer name: %s\n", buff);

	char buff2[UNLEN + 1];
	DWORD size2 = sizeof(buff2);
	GetUserNameA(buff2, &size2);
	printf("\tUser name: %s\n", buff2);

	time_t rawtime;
	time(&rawtime);
	printf("\tData and time: %s", ctime(&rawtime));
	printf("\n\n");
}

void UsersInfo() {
	printf("UsersInfo:\n");
	LPUSER_INFO_0 pTmpBuf;
	NET_API_STATUS result;
	DWORD dwfilter = 0;
	DWORD dwlevel = 0;
	DWORD dwprefmaxlen = 512;
	DWORD dwentriesread;
	DWORD dwtotalentries;
	result = NetUserEnum(NULL, dwlevel, dwfilter, (LPBYTE*)&pTmpBuf, dwprefmaxlen, &dwentriesread, &dwtotalentries, NULL);
	for (DWORD i = 0; i < dwentriesread; i++)
	{
		printf("\t%i: ", i + 1);
		wprintf(L"%s \n", pTmpBuf[i].usri0_name);
	}
	printf("\n");
}

int main() {
	setlocale(LC_ALL, "Rus");
	char buff2[UNLEN + 1];
	DWORD size2 = sizeof(buff2);
	GetUserNameW(buff2, &size2);
	UsersInfo();
	getUserInfo(buff2);
	sysinfo();
	system("pause");
	return 0;
}