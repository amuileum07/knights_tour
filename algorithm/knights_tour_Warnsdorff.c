#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

// XorShift-based random number generator from https://en.wikipedia.org/wiki/Xorshift
static inline uint32_t xorshift32(uint32_t *state) 
{
    uint32_t x = *state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    *state = x;
    return x;
}

static inline void num_ofcase(int** board, int size, int i, int j, int move[8], int di[], int dj[]) 
{
    for (int a = 0; a <= 7; a++) 
    {
        int ni = i + di[a];
        int nj = j + dj[a];
        
        int cnt = 0;
        if (ni >= 0 && ni < size && nj >= 0 && nj < size && !board[ni][nj]) 
        {
            for (int b = 0; b < 8; b++) 
            {
                int mi = ni + di[b];
                int mj = nj + dj[b];
                if (mi >= 0 && mi < size && mj >= 0 && mj < size && !board[mi][mj]) cnt += 1;
            }
        }
        move[a] = cnt;
    }
}

void sol_move(int** board, int size, int n1, int n2, int* i, int* j, int* order, uint32_t *rng_state, int di[], int dj[]) {
    int move[8];

    while (1) 
    {
        num_ofcase(board, size, *i, *j, move, di, dj);
        
        int min = 9, min_a = -1;
        for (int a = 0; a <= 7; a++) {
            if (move[a] < min && move[a] > 0) 
            {
                min = move[a];
                min_a = a;
            }
            else if (move[a] == min) 
            {
                int val = xorshift32(rng_state) % 2;
                if (val) {
                    min = move[a];
                    min_a = a;
                }
            }
        }

        if (min_a == -1) 
        {
            for (int a = 0; a <= 7; a++) 
            {
                int ni = *i + di[a];
                int nj = *j + dj[a];
                if (ni >= 0 && ni < size && nj >= 0 && nj < size && !board[ni][nj])
                {
                    board[ni][nj] = *order;
                    break;
                }
            }
            break;
        }

        *i += di[min_a];
        *j += dj[min_a];
        board[*i][*j] = (*order)++;
    }
}

int** make_board(int n1, int n2, int* size, int* i, int* j, int* order) 
{
    *size = (n1 > n2 ? n1 : n2) + 4;
    int** board = (int**)malloc((*size) * sizeof(int*));
    for (int a = 0; a < *size; a++) 
    {
        board[a] = (int*)malloc((*size) * sizeof(int));
        for (int b = 0; b < *size; b++) 
        {
            board[a][b] = -1;
        }
    }

    for (int a = 2; a <= n1 + 1; a++) 
    {
        for (int b = 2; b <= n2 + 1; b++) 
        {
            board[a][b] = 0;
        }
    }

    scanf("%d%d", j, i);
    (*i)++;
    (*j)++;
    board[*i][*j] = (*order)++;

    return board;
}

static inline void free_board(int** board, int size) {
    for (int a = 0; a < size; a++) {
        free(board[a]);
    }
    free(board);
}

void print_board(int** board, int size, int n1, int n2) {
    int cnt = 0;
    int axis = 1;
    // using ANSI escape code for color
    printf("       ");
    for (int j = 2; j <= n2 + 1; j++) printf("\033[0;34m%6d\033[0m    ", j - 1);
    puts("");

    printf("       ");
    for (int j = 0; j < n2; j++) printf("----------");
    puts("");

    for (int i = 2; i <= n1 + 1; i++) {
        printf("\033[0;34m%6d\033[0m |", axis++);
        for (int j = 2; j <= n2 + 1; j++) {
            if (!board[i][j]) cnt += 1;

            if (board[i][j] == 0 || board[i][j] == 1 || board[i][j] == n1 * n2) 
                printf("\033[0;31m%6d\033[0m  | ", board[i][j]);
            else 
                printf("%6d  | ", board[i][j]);
        }
        puts("");

        printf("       ");
        for (int j = 0; j < n2; j++) printf("----------");
        puts("");
    }
    puts("");

    if (!cnt) printf("success");
    else printf("fail");

    puts("");
}

int main() 
{
    int n1, n2;
    scanf("%d %d", &n2, &n1);

    // possible moves of a knight
    int di[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dj[] = {-1, 1, -2, 2, -2, 2, -1, 1};

    int size;
    int i, j, order = 1;

    uint32_t rng_state = (uint32_t)time(NULL); // Initialize RNG state with current time

    int** board = make_board(n1, n2, &size, &i, &j, &order);
    sol_move(board, size, n1, n2, &i, &j, &order, &rng_state, di, dj);
    print_board(board, size, n1, n2);

    free_board(board, size);
    return 0;
}
