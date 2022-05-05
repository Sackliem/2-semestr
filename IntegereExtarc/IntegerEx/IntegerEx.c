#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int main() {
	char str[200] = "";
	int digits[100] = {0};
	int countsym = 0;
	char sym;
	while (1) {
		sym = getche();
		if (sym == 13) printf("\n");
		if (sym == 27) {
			str[countsym] = 0;
			break;
		}
		if (isdigit(sym)) {
			str[countsym] = sym;
			countsym++;
		} 
		else if (str[countsym - 1] >= 48 && str[countsym - 1] <= 57) {
			str[countsym] = 32;
			countsym++;
		}
	}
	int j = 0;
	for (unsigned int i = 0; i < strlen(str); i++) {
		if (str[i] >= '0' && str[i] <= '9') {
			digits[j] = digits[j] * 10 + str[i] - '0';
		}
		else {
			j++;
		}
	}
	int counter = 0;
	for (int i = 0; i < 100; i++) {
		if (digits[i] > 0) {
			counter++;
		}
	}
	int* numbers = (int*)malloc(counter * sizeof(int));
	int z = 0;
	for (int i = 0; i < 100; i++) {
		if (digits[i] != 0) {
			numbers[z] = digits[i];
			z++;
		}
	}
	printf(" \n");
	for (int i = 0; i < counter; i++) {
		numbers[i] *= numbers[i];
		printf(" %d ", numbers[i]);
	}
	printf(" \n");
	free(numbers);
	system("pause");
	return 0;

}