#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <locale.h> 
#include <stdlib.h>

struct Bar {
	int count;
	int *bookCounter;
}co;

int comparator(const void* first, const void* second) {
	const char** tmp_1 = (char**)first;
	const char** tmp_2 = (char**)second;
	return (strlen(*tmp_1) - strlen(*tmp_2));
}

void sortedbookprint(char** txt, int count) {
	for (int i = 0; i < count; i++) {
		for (int j = 0; txt[i][j] != '\n'; j++) {
			printf("%c", txt[i][j]);
		}
		printf("\n ");
	}
}

char** copy_arrey(FILE* book, int count, int *bookCounter) {
	char** txt = (char**)malloc(count * sizeof(char*));
	for (int i = 0; i < count; i++) {
		txt[i] = (char*)malloc(bookCounter[i] * sizeof(char));
		for (int j = 0; j < bookCounter[i]; j++) {
			txt[i][j] = fgetc(book);
		}
	}
	return txt;
}

struct Bar counter(FILE* book) {
	int* bookCounter = NULL;
	int count = 0;
	int* tmp = NULL;
	int CharCount = 0;
	while (!feof(book)) {
		char symb = NULL;
		symb = fgetc(book);
		CharCount++;
		if (symb == '\n') {
			count++;
			tmp = (int*)realloc(bookCounter, count * sizeof(int));
			if (tmp != NULL) {
				bookCounter = tmp;
				bookCounter[count - 1] = CharCount;
				CharCount = 0;
			}
			else {
				free(bookCounter);
				free(tmp);
			}
		}
		else if (symb == '\0') break;
	}
	co.bookCounter = bookCounter;
	co.count = count;
	return co;
}

void openArg(FILE* book, char* name) {
	fopen_s(&book, name, "r");
	if (book == NULL) {
		printf("Fail on opening file\n");
		system("pause");
		return -1;
	}
	struct Bar co = counter(book);
	int* bookCounter = co.bookCounter;
	int count = co.count;
	rewind(book);
	char** txt = copy_arrey(book, count, bookCounter);
	qsort(txt, count, sizeof(char*), comparator);
	fclose(book);
	free(bookCounter);
	sortedbookprint(txt, count);
	system("pause");
	for (int i = 0; i < count; i++) {
		free(txt[i]);
	}
	free(txt);
}

void openConsole(FILE* book) {
	char Bookname[10];
	system("cls");
	printf(" input your name:\n ");
	gets(Bookname);
	system("cls");
	fopen_s(&book, Bookname, "r");
	if (book == NULL) {
		printf("Fail on opening file\n");
		system("pause");
		return -1;
	}
	struct Bar co = counter(book);
	int* bookCounter = co.bookCounter;
	int count = co.count;
	rewind(book);
	char** txt = copy_arrey(book, count, bookCounter);
	qsort(txt, count, sizeof(char*), comparator);
	fclose(book);
	free(bookCounter);
	sortedbookprint(txt, count);
	system("pause");
	for (int i = 0; i < count; i++) {
		free(txt[i]);
	}
	free(txt);
}

void openBookList(FILE* book) {
	printf("this function doesn`t work, but you can see the titles of your books:\n");
	FILE* booklist = NULL;
	int count = 0;
	char sym;
	int countsym = 0;
	char strbook[100];
	fopen_s(&booklist, "filenames.txt", "r");
	if (booklist == NULL) {
		printf("Fail on opening filenames.txt\n");
		system("pause");
		return -1;
	}
	while (!feof(booklist)) {
		sym = fgetc(booklist);
		if(sym == 10 || sym == EOF) count++;
	}
	sym = NULL;
	rewind(booklist);
	for (int i = 0; i < count; i++) {
		while (1){
			sym = fgetc(booklist);
			if (sym == 10 || sym == EOF) { strbook[countsym] = 0; countsym = 0; break; }
			if (countsym < 99) {
				strbook[countsym] = sym;
				countsym++;
			}
			else { printf("Name of book so long"); system("pause"); return -1; }
		}
		printf("%s\n", strbook);
	}
	system("pause");
}

int main(int argc, char** argv) {
	FILE* book = NULL;
	setlocale(0, "Russian");
	if (argc > 1) 
		openArg(book, argv[1]);
	else {
		printf(" to input file name from console write 1\n or 2 if you have a filenames.txt(it`s not delivered yet)");
		char vir = getch();
		system("cls");
		if (vir == 49) openConsole(book);
		else if (vir == 50) openBookList(book);
	}
	
	return 0;
}