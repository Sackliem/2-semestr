#include<stdio.h>
#include<stdlib.h>

int** board;

int x, y;

int check(int c, int r)
{                  
    for (int i = 0; i < c; ++i)
    {
        // Проверка горизонтали
        if (board[i][r]) return 0;
        // Проверка диагонали
        if (r - c + i >= 0) if (board[i][r - c + i]) return 0;
        if (r + c - i < y) if (board[i][r + c - i]) return 0;
    }
    return 1;
}


int vert(int i) // Установка i-й вертикали
{
    if (i == y) return 1;  
    for (int j = 0; j < y; ++j)  // Ищем место по ввертикали
        if (check(i, j, board))           
        {
            board[i][j] = 1;    
            if (vert(i + 1,board)) return 1; 
            board[i][j] = 0;    
        }
    return 0;
}

int main()
{
    int k = 0;
    scanf_s("%d %d", &x, &y);
    board = (int**)malloc(x * sizeof(int*) + 1);
    for (int i = 0; x > i; ++i)
        board[i] = (int*)malloc(y * sizeof(int));

    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
            board[i][j] = NULL;
    }

    vert(0, board);

    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
            //printf("%d", board[i][j]);
            printf("%c", board[i][j] ? '#' : '.');
        printf("\n");
    }
    printf("\n\n");
    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
            if (board[i][j] == 1) k++;
    }
    printf("Ferz: %d", k);
    for (int i = 0; x > i; ++i)
        free(board[i]);
    free(board);
    return 0;
}