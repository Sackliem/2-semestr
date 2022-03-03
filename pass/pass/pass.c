#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

int main()
{
	char pass[23];
	pass[22] = 0;
	char sym;
	int count = 0;
	int safe = 0;
	printf("input password in lenght 20:\n");
	while (1) {
		if (strlen(pass) == 20) {
			break;
		}
		sym = getch();
		if (sym >= 33 && sym <= 57 || sym >= 65 && sym <= 90 || sym >= 97 && sym <= 122) {
			putch(42);	
			pass[count] = sym;
			pass[count + 1] = 0;
			count++;
		}
		else
		{
			if (sym == 13) {
				pass[count + 1] = 0;
				break;
			}
			if (sym == 8) {
				putch(8);
				putch(32);
				putch(8);
				count--;
				pass[count] = 0;
				continue;
			}
		}
	}
	system("cls");
	printf("%s\n", pass);
	int i = 0, c=0;
	int haveUppercase = 0, haveDigits = 0, havePunct = 0, lenght = 0;
	while (i < count - 1) {
		if (isupper(pass[i])) { 
			if (haveUppercase < 3) haveUppercase += 1; }
		if (isdigit(pass[i])) { 
			if (haveDigits < 3) haveDigits += 1; }
		if (ispunct(pass[i])) { 
			if (havePunct < 3) havePunct += 1; }
		i++;
	}
	if (count > 5) lenght = 5; else lenght = count;
	safe = ((lenght * 10) - 20) + (haveDigits * 10) + (havePunct * 10) + (haveUppercase * 10) + 5;

	printf("Password Safe:%d", safe);
}