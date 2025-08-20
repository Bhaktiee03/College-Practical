#include <stdio.h>
#include <stdlib.h>

#define SIZE 2  // Set matrix size (must be power of 2)

// Function to allocate a 2D matrix
int** allocate_matrix(int size) {
int** matrix = (int**)malloc(size * sizeof(int*));
for (int i = 0; i < size; i++)
matrix[i] = (int*)calloc(size, sizeof(int));
return matrix;
}

// Function to add two matrices
void add(int** A, int** B, int** result, int size) {
for (int i = 0; i < size; i++)
for (int j = 0; j < size; j++)
result[i][j] = A[i][j] + B[i][j];
}

// Function to subtract two matrices
void subtract(int** A, int** B, int** result, int size) {
for (int i = 0; i < size; i++)
for (int j = 0; j < size; j++)
result[i][j] = A[i][j] - B[i][j];
}

// Strassen's matrix multiplication
void strassen(int** A, int** B, int** C, int size) {
if (size == 1) {
C[0][0] = A[0][0] * B[0][0];
return;
}

int newSize = size / 2;

// Allocate submatrices
    int** A11 = allocate_matrix(newSize);
    int** A12 = allocate_matrix(newSize);
    int** A21 = allocate_matrix(newSize);
    int** A22 = allocate_matrix(newSize);
    int** B11 = allocate_matrix(newSize);
    int** B12 = allocate_matrix(newSize);
    int** B21 = allocate_matrix(newSize);
    int** B22 = allocate_matrix(newSize);
    int** C11 = allocate_matrix(newSize);
    int** C12 = allocate_matrix(newSize);
    int** C21 = allocate_matrix(newSize);
    int** C22 = allocate_matrix(newSize);

// Temporary matrices
    int** M1 = allocate_matrix(newSize);
    int** M2 = allocate_matrix(newSize);
    int** M3 = allocate_matrix(newSize);
    int** M4 = allocate_matrix(newSize);
    int** M5 = allocate_matrix(newSize);
    int** M6 = allocate_matrix(newSize);
    int** M7 = allocate_matrix(newSize);
    int** temp1 = allocate_matrix(newSize);
    int** temp2 = allocate_matrix(newSize);

// Dividing matrices into submatrices
for (int i = 0; i < newSize; i++) {
for (int j = 0; j < newSize; j++) {
    A11[i][j] = A[i][j];
    A12[i][j] = A[i][j + newSize];
    A21[i][j] = A[i + newSize][j];
    A22[i][j] = A[i + newSize][j + newSize];
            
    B11[i][j] = B[i][j];
    B12[i][j] = B[i][j + newSize];
    B21[i][j] = B[i + newSize][j];
    B22[i][j] = B[i + newSize][j + newSize];
}
}

// M1 = (A11 + A22) * (B11 + B22)
    add(A11, A22, temp1, newSize);
    add(B11, B22, temp2, newSize);
    strassen(temp1, temp2, M1, newSize);

// M2 = (A21 + A22) * B11
    add(A21, A22, temp1, newSize);
    strassen(temp1, B11, M2, newSize);

// M3 = A11 * (B12 - B22)
    subtract(B12, B22, temp2, newSize);
    strassen(A11, temp2, M3, newSize);

// M4 = A22 * (B21 - B11)
    subtract(B21, B11, temp2, newSize);
    strassen(A22, temp2, M4, newSize);

// M5 = (A11 + A12) * B22
    add(A11, A12, temp1, newSize);
    strassen(temp1, B22, M5, newSize);

// M6 = (A21 - A11) * (B11 + B12)
    subtract(A21, A11, temp1, newSize);
    add(B11, B12, temp2, newSize);
    strassen(temp1, temp2, M6, newSize);

// M7 = (A12 - A22) * (B21 + B22)
    subtract(A12, A22, temp1, newSize);
    add(B21, B22, temp2, newSize);
    strassen(temp1, temp2, M7, newSize);

// C11 = M1 + M4 - M5 + M7
    add(M1, M4, temp1, newSize);
    subtract(temp1, M5, temp2, newSize);
    add(temp2, M7, C11, newSize);

// C12 = M3 + M5
    add(M3, M5, C12, newSize);

// C21 = M2 + M4
    add(M2, M4, C21, newSize);

// C22 = M1 - M2 + M3 + M6
    subtract(M1, M2, temp1, newSize);
    add(temp1, M3, temp2, newSize);
    add(temp2, M6, C22, newSize);

// Combine submatrices into result matrix C
for (int i = 0; i < newSize; i++) {
for (int j = 0; j < newSize; j++) {
     C[i][j] = C11[i][j];
     C[i][j + newSize] = C12[i][j];
     C[i + newSize][j] = C21[i][j];
     C[i + newSize][j + newSize] = C22[i][j];
}
}

// Free all allocated matrices
int** matrices[] = {
      A11, A12, A21, A22,
      B11, B12, B21, B22,
      C11, C12, C21, C22,
      M1, M2, M3, M4, M5, M6, M7,
      temp1, temp2
};

for (int i = 0; i < sizeof(matrices) / sizeof(matrices[0]); i++) {
for (int j = 0; j < newSize; j++)
      free(matrices[i][j]);
      free(matrices[i]);
}
}

// Function to print a matrix
void print_matrix(int** matrix, int size) {
for (int i = 0; i < size; i++) {
for (int j = 0; j < size; j++)
printf("%4d ", matrix[i][j]);
printf("\n");
}
}

int main() {
// Define your matrices here
    int** A = allocate_matrix(SIZE);
    int** B = allocate_matrix(SIZE);
    int** C = allocate_matrix(SIZE);

// Example values
    A[0][0] = 1; A[0][1] = 2;
    A[1][0] = 3; A[1][1] = 4;

    B[0][0] = 5; B[0][1] = 6;
    B[1][0] = 7; B[1][1] = 8;

printf("Matrix A:\n");
print_matrix(A, SIZE);
printf("\nMatrix B:\n");
print_matrix(B, SIZE);

// Perform Strassen multiplication
strassen(A, B, C, SIZE);

printf("\nResult Matrix C (A * B):\n");
print_matrix(C, SIZE);

// Free memory
for (int i = 0; i < SIZE; i++) {
    free(A[i]);
    free(B[i]);
    free(C[i]);
}
    free(A);
    free(B);
    free(C);

return 0;
}

