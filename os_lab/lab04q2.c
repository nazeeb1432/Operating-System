#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 3 // Change this value to match the size of your matrices

void multiplyRow(int row, int (*matrix1)[SIZE], int (*matrix2)[SIZE], int (*result)[SIZE]) {
    for (int col = 0; col < SIZE; col++) {
        int sum = 0;
        for (int i = 0; i < SIZE; i++) {
            sum += matrix1[row][i] * matrix2[i][col];
        }
        result[row][col] = sum;
    }
}

int main() {
    int matrix1[SIZE][SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int matrix2[SIZE][SIZE] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    int result[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            multiplyRow(i, matrix1, matrix2, result);
            exit(0);
        } else if (pid < 0) {
            perror("fork");
            exit(1);
        }
    }

    for (int i = 0; i < SIZE; i++) {
        wait(NULL);
    }

    // Print the result matrix
    printf("Resultant Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d\t", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}
