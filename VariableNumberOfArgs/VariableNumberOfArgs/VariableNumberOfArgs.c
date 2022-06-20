#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

int sum(int n, ...)
{
	va_list arglist;
	va_start(arglist, n);
	int result = 0, i = 0;
	while (n > 0)
	{
		i = va_arg(arglist, int);
		result += i;
		--n;
	}
	va_end(arglist);
	return result;
}

double sumDouble(double n, ...)
{
	double result = 0.0;
	double* ptr = &n + 1;
	while (n)
	{
		result += *(ptr++);
		n--;
	}
	return result;
}


double sum_double_via_stdarg(double n, ...)
{
	double result = 0.0;
	va_list ptr;
	va_start(ptr, n);
	while (n)
	{
		result += va_arg(ptr, double);
		n--;
	}
	va_end(ptr);
	return result;
}


char* concat(char* arg, ...)
{
	va_list ptr;
	va_start(ptr, arg);
	char* result = (char*)malloc(100 * sizeof(char));
	int j = 0;
	for (int i = 0; i < strlen(arg); i++)
	{
		result[j] = arg[i];
		j++;
	}
	while (arg[0] != '\0')
	{
		arg = va_arg(ptr, char*);
		for (int i = 0; i < strlen(arg); i++)
		{
			result[j] = arg[i];
			j++;
		}
	}
	result[j] = '\0';
	va_end(ptr);
	return result;
}


int main() {
	char* str1 = concat("one ", "two ", "three ", "four", "\0");
	printf("%s\n", str1);
	free(str1);
	str1 = concat("Happy ", "new ", "year!", "\0");
	printf("%s\n", str1);
	free(str1);
	str1 = concat("Hello ", "world!", "\0");
	printf("%s\n", str1);
	free(str1);
}