#include <stdio.h>

int tele(int count) {
	if (count == 1)
	{
		printf_s("8");
		return -1;
	}
	int a[10][122] = { 0 };
	for (int i = 0, j = 2; i < 10; i++)
	{
		a[i][j] = 2;
	}
	for (int n = 3; n <= count; n++)
	{
		a[0][n] = a[6][n - 1] + a[4][n - 1];
		a[1][n] = a[6][n - 1] + a[8][n - 1];
		a[2][n] = a[7][n - 1] + a[9][n - 1];
		a[3][n] = a[4][n - 1] + a[8][n - 1];
		a[4][n] = a[9][n - 1] + a[0][n - 1] + a[3][n - 1];
		a[6][n] = a[1][n - 1] + a[0][n - 1] + a[7][n - 1];
		a[7][n] = a[6][n - 1] + a[2][n - 1];
		a[8][n] = a[3][n - 1] + a[1][n - 1];
		a[9][n] = a[4][n - 1] + a[2][n - 1];
	}
	long long int result = 0;
	for (int n = 0; n <= 9; n++)
	{
		if ((n == 8) || (n == 0))
			continue;
		result += a[n][count];
	}
	printf_s("%lld\n", result);
	return 0;
}


int main()
{
	int count;
	scanf_s("%d", &count);
	tele(count);
	return 0;
}