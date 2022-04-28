#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tlhelp32.h>
#include <string.h>

int main() {
	HKEY R;
	DWORD Value = 1;
	DWORD cBuff = 4;
	char* path = TEXT("Count");
	if (RegCreateKeyEx(HKEY_CURRENT_USER, path, NULL, NULL, 0x00000001L, KEY_ALL_ACCESS, NULL, &R, NULL) == ERROR_SUCCESS) {
		if (RegQueryValueEx(R, TEXT("Count"), NULL, NULL, &Value, &cBuff) == ERROR_SUCCESS) {
			if (Value > 0) return 0;
			Value++;
			RegSetValueEx(R, TEXT("Count"), NULL, REG_DWORD, &Value, 4);
		}
		else {
			RegSetValueEx(R, TEXT("Count"), NULL, REG_DWORD, &Value, 4);
			Value++;
			printf("Normal program start\n");
		}
	}
	system("pause");
	if (RegQueryValueEx(R, TEXT("Count"), NULL, NULL, &Value, &cBuff) == ERROR_SUCCESS) {
		Value = 0;
		RegSetValueEx(R, TEXT("Count"), NULL, REG_DWORD, &Value, 4);
	}
	return 0;
}
