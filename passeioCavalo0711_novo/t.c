#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX = 100;
int cols = 5;
int rows = 5; 

int N = 5;

int **transforma5(int visited[5][5]){

        int k, i, j;
        int **resultado = malloc(N * sizeof(int *));
        resultado[0] = malloc(N * N * sizeof(int));

        for(k = 1; k < N; k++){
                resultado[k] = resultado[0] + k * N;
	}

        for(i=0; i< N; i++){
                for(j=0; j< N; j++){
                        resultado[j][i] = visited[i][j];
                }
        }

        return resultado;
}
  
//void imageSwap(int mat[][4], int n)
void imageSwap(int mat[][5], int n)  
{ 
    // traverse a matrix and swap  
    // mat[i][j] with mat[j][i] 
    for (int i = 0; i < n; i++){ 
        for (int j = 0; j <= i; j++){  
            mat[i][j] = mat[i][j] + mat[j][i] -  
                       (mat[j][i] = mat[i][j]);
        }
    }        
} 

void imageSwap2(int **mat, int n)  
{ 
    // traverse a matrix and swap  
    // mat[i][j] with mat[j][i] 
    for (int i = 0; i < n; i++){ 
        for (int j = 0; j <= i; j++){  
            mat[i][j] = mat[i][j] + mat[j][i] -  
                       (mat[j][i] = mat[i][j]);
        }
    }        
} 
  
// Utility function to print a matrix 
//void printMatrix(int mat[][4], int n) 
void printMatrix(int mat[][5], int n) 
{ 
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++){ 
            printf("%d ", mat[i][j]);
        } 
        printf("\n");
    } 
} 

void printMatrix2(int **mat, int n) 
{ 
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++){ 
            printf("%d ", mat[i][j]);
        } 
        printf("\n");
    } 
}


void printMatrix3(int *mat, int n) 
{ 
    //int offset = i * cols + j;
    int offset;
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++){ 
            offset = i * n + j;
            printf("%d ", mat[offset]);
        } 
        printf("\n");
    } 
}

void imageSwap3(int *mat, int n)  
{ 
    // traverse a matrix and swap  
    // mat[i][j] with mat[j][i] 
    //int offset = i * cols + j;
    int offset1;
    int offset2;
    for (int i = 0; i < n; i++){ 
        for (int j = 0; j <= i; j++){ 
            offset1 = i * n + j;
            offset2 = j * n + i;
            mat[offset1] = mat[offset1] + mat[offset2] -
                        (mat[offset2] = mat[offset1]);
            /* 
            mat[i][j] = mat[i][j] + mat[j][i] -  
                       (mat[j][i] = mat[i][j]);
            */
        }
    }        
} 
  
// driver program to test above function 
int main() 
{ 
    // int mat[][4] = { { 1, 2, 3, 4 }, 
    //                  { 5, 6, 7, 8 }, 
    //                  { 9, 10, 11, 12 }, 
    //                  { 13, 14, 15, 16 } }; 
/*
    int mat[5][5] = { {1, 20, 17, 12, 3},
                    {16, 11, 2, 7, 18},
                    {21, 24, 19, 4, 13},
                    {10, 15, 6, 23, 8},
                    {25, 22, 9, 14, 5}};                 
    //int n = 4; 
    int n = 5; 
    printMatrix(mat, n);
    printf("\n");
    //imageSwap(mat, n);
    imageSwap2(&mat, n);  
    printMatrix(mat, n); 
    printf("\n");
    imageSwap(mat, n); 
    printMatrix(mat, n);
*/
    //int *mat = (int *)malloc(rows * cols * sizeof(int));

    //int offset = i * cols + j;
    // now mat[offset] corresponds to m(i, j)
    //mat = [1, 20, 17, 12, 3, 16, 11, 2, 7, 18, 21, 24, 19, 4, 13, 10, 15, 6, 23, 8, 25, 22, 9, 14, 5]; 
/*
    memcpy(mat, (int []){1, 20, 17, 12, 3, 16, 11, 2, 7, 18, 21, 24, 19, 4, 13, 10, 15, 6, 23, 8, 25, 22, 9, 14, 5}, 25 * sizeof mat[0]);

    printMatrix3(mat, 5);

    imageSwap3(mat, 5);
    printf("\n");
    printMatrix3(mat, 5);


    imageSwap3(mat, 5);
    printf("\n");
    printMatrix3(mat, 5);

    free(mat);
    */
    //int (*mat)[cols];
   // mat=(int (*)[cols])malloc(sizeof(*mat) * rows);

   //mat = {{1, 20, 17, 12, 3}, {16, 11, 2, 7, 18}, {21, 24, 19, 4, 13}, {10, 15, 6, 23, 8}, {25, 22, 9, 14, 5}};
    // memcpy(mat[0], (int []){1, 20, 17, 12, 3}, 5 * sizeof(mat[0]));
    // memcpy(mat[1], (int []){16, 11, 2, 7, 18}, 5 * sizeof(mat[0]));
    // memcpy(mat[2], (int []){21, 24, 19, 4, 13}, 5 * sizeof(mat[0]));
    // memcpy(mat[3], (int []){10, 15, 6, 23, 8}, 5 * sizeof(mat[0]));
    // memcpy(mat[4], (int []){25, 22, 9, 14, 5}, 5 * sizeof(mat[0]));

    // (*mat)[0] = [1, 20, 17, 12, 3];
    // (*mat)[1] = {16, 11, 2, 7, 18};
    // (*mat)[2] {21, 24, 19, 4, 13};
    // (*mat)[3] {10, 15, 6, 23, 8};
    // (*mat)[4] {25, 22, 9, 14, 5};


    int mat[5][5] = { {1, 20, 17, 12, 3},
                    {16, 11, 2, 7, 18},
                    {21, 24, 19, 4, 13},
                    {10, 15, 6, 23, 8},
                    {25, 22, 9, 14, 5}};   

//         int mat[5][5] = {
//             {3, 12, 17, 20, 1}, 
// {18, 7, 2, 11, 16}, 
// {13, 4, 19, 24, 21}, 
// {8, 23, 6, 15, 10}, 
// {5, 14, 9, 22, 25}};

    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            printf("%2d ", mat[i][j]);
        }
        printf("\n");
    }

    int mt1[5][5] = { {0, 0, 0, 0, 1},
                     {0, 0, 0, 1, 0},
                     {0, 0, 1, 0, 0},
                     {0, 1, 0, 0, 0},
                     {1, 0, 0, 0, 0}
                };

    int mt2[5][5] = { {1, 0, 0, 0, 0},
                     {0, -1, 0, 0, 0},
                     {0, 0, -1, 0, 0},
                     {0, 0, 0, -1, 0},
                     {0, 0, 0, 0, -1}
                };

    int resultado[5][5] = { {0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0}
                };
    // for (int i=0; i<5; i++){
    //     for(int j=0; j<5; j++){       
    //         for (int k=0; k<5; k++){
    //             resultado[i][j] += mat[i][k] * mt2[k][j];
    //         }
    //     }
    // }
    for(int i=0; i<5; i++){       
        for (int j=0; j<5; j++){
            // resultado[j][6-i] = mat[i][j];
            resultado[j][4-i] = mat[i][j];
        }
    }
  

    printf("\n");
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            printf("%2d ", resultado[i][j]);
        }
        printf("\n");
    }

    for(int i=0; i<5; i++){       
        for (int j=0; j<5; j++){
            // resultado[j][6-i] = mat[i][j];
            resultado[i][4-j] = mat[i][j];
        }
    }
  

    printf("\n");
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            printf("%2d ", resultado[i][j]);
        }
        printf("\n");
    }

    for(int i=0; i<5; i++){       
        for (int j=0; j<5; j++){
            // resultado[j][6-i] = mat[i][j];
            resultado[4-i][4-j] = mat[i][j];
        }
    }
  

    printf("\n");
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            printf("%2d ", resultado[i][j]);
        }
        printf("\n");
    }


    for(int i=0; i<5; i++){       
        for (int j=0; j<5; j++){
            // resultado[j][6-i] = mat[i][j];
            resultado[4-i][j] = mat[i][j];
        }
    }
  

    printf("\n");
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            printf("%2d ", resultado[i][j]);
        }
        printf("\n");
    }


    for(int i=0; i<5; i++){       
        for (int j=0; j<5; j++){
            // resultado[j][6-i] = mat[i][j];
            resultado[4-j][i] = mat[i][j];
        }
    }
  

    printf("\n");
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            printf("%2d ", resultado[i][j]);
        }
        printf("\n");
    }


    for(int i=0; i<5; i++){       
        for (int j=0; j<5; j++){
            // resultado[j][6-i] = mat[i][j];
            resultado[j][i] = mat[i][j];
        }
    }
  

    printf("\n");
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            printf("%2d ", resultado[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");
    
    int **teste = transforma5(mat);
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            printf("%2d ", teste[i][j]);
        }
        printf("\n");
    }



    return 0; 
} 


// int mt2[5][5] = { {1, 0, 0, 0, 0},
//                      {0, 1, 0, 0, 0},
//                      {0, 0, 1, 0, 0},
//                      {0, 0, 0, 1, 0},
//                      {0, 0, 0, 0, 1}
//                 };