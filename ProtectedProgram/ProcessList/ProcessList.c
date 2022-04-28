#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tlhelp32.h>


int main() {
    int p = 0;
    PROCESSENTRY32 peProcessEntry;
    HANDLE CONST hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }
    peProcessEntry.dwSize = sizeof(PROCESSENTRY32);
    Process32First(hSnapshot, &peProcessEntry);
    while (Process32Next(hSnapshot, &peProcessEntry)) {
        wprintf(L"%ul %s \n", peProcessEntry.th32ProcessID, peProcessEntry.szExeFile);
    }
    system("pause");
    CloseHandle(hSnapshot);
}