#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int days(char* day, char *month) {
	char com[25] = "7z x secret.7z -p";
	char command[40];
	char pass[9];
	char year[5] = "1991";
	for (int i = 48; i <= 51; i++) {
		day[0] = i;
		for (int j = 48; j <= 57; j++)
		{
			day[1] = j;

			strcpy_s(pass, 9,day);
			strcat_s(pass, 9, month);
			strcat_s(pass, 9, year);
			strcpy_s(command, 40, com);
			strcat_s(command, 40, pass);
			
			if (system(command) == 0) { 
				printf("\nSuccess"); 
				printf("\n Password: %s \n", pass); 
				system("pause"); 
				return 0; }
			system("cls");
			if (i == 51 && j == 49) break;
		}
	}
}

int main() {
	system("@echo OFF");
	char day[3];
	day[2] = 0;
	day[0] = 48;
	day[1] = 48;
	char month[3];
	month[2] = 0;
	month[0] = 48;
	int work = 1;

	for (int i = 48; i <= 49; i++) {
		if (work == 0) break;
		month[0] = i;
		for (int j = 48; j <= 57; j++) {
			month[1] = j;
			if (days(day, month) == 0) { work = 0; break; }
			if (i == 49 && j == 50) break;
		}
	}
	printf("\n");




}