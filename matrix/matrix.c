/*
* 작성자: 박도영
* 작성일자 : 2021/03/28
* 파일 이름: matrix.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS 


/* Method Declaration */
int** create_matrix(int row, int col); // 입력받은 행과 열을 구성하는 행렬을 생성하는 함수, 더블포인터를 사용해 주소를 반환받는다
void print_matrix(int** matrix, int row, int col); // 행렬을 받아서 출력하는 함수  
int free_matrix(int** matrix, int row, int col);  // 행렬을 받아서 동적 할당 해제 하는 함수
int fill_data(int** matrix, int row, int col);      //0~19까지의 랜덤값을 행렬에 할당하는 함수
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);  //a와 b행렬을 더하는 함수
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);   //a와 b행렬을 뺄셈하는 함수
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);   //행렬을 입력받고,그 행렬의 전치행렬을 생성하는 함수
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);  //행렬과 그 전치행렬을 받고 곱하는 함수

int main()
{

    char command;
    printf("[----- [Do young park]  [2018038077] -----]\n");

    int row, col;
    srand(time(NULL));

    printf("Input row and col : "); //행과 열을 입력받는다
    scanf("%d %d", &row, &col);
    int** matrix_a = create_matrix(row, col);       //행렬 생성
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row); //전치 행렬 생성이라, 열과 행을 바꾼다

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) { return -1; } //비정상 적으로 행렬이 정의 됐을때 리턴 -1을반환하여 실행을 끝낸다

    do {
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command); //명령을 입력받는다

        switch (command) {
        case 'z': case 'Z': 
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
   
      
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    /* check pre conditions */
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }
   
    int** matrix = (int**)malloc(sizeof(int*) * row); //비 순차적으로 배열 형성

     /* check post conditions */
    if (matrix == NULL) {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }
    for (int i = 0; i < row; i++) {
        matrix[i] = (int*)malloc(sizeof(int) * col); //비 순차적 2차원 배열 형성
    }
   
    return matrix;  //포인터의 주소를 반환

}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%4d", matrix[i][j]); //행렬 출력 앞에 4는 어차피 최댓값인 19*19가 3자리수 이기 떄문이다
        }
        putchar('\n');
    }
        


}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return -1;
    }
    /* check post conditions */
    if (matrix == NULL) {
        printf("Check the sizes of row and col!\n");
        return -1;
    }
    for (int i = 0; i < row; i++) {     
        free(matrix[i]); //2차원 동적 할당 해제
    }
    free(matrix);
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return -1;
    }
    /* check post conditions */
    if (matrix == NULL) {
        printf("Check the sizes of row and col!\n");
        return -1;
    }
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            matrix[i][j] = rand() % 20; //0~ 19까지의 랜덤 값으로 초기화

}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return -1;
    }
    /* check post conditions */
    if (matrix_a == NULL || matrix_b==NULL) {
        printf("Check the sizes of row and col!\n");
        return -1;
    }
    int **sum_matrix = create_matrix(row, col); //row*col 새로운 행렬을 만들고 a행렬과 b행렬을 더한다
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            sum_matrix[i][j] = matrix_a[i][j] + matrix_b[i][j];
    }

    print_matrix(sum_matrix, row, col);
    
    free_matrix(sum_matrix, row, col);
    return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
  
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return -1;
    }
    /* check post conditions */
    if (matrix_a == NULL || matrix_b == NULL) {
        printf("Check the sizes of row and col!\n");
        return -1;
    }
    int** subtract_matrix = create_matrix(row, col); //row*col 새로운 행렬을 만들고 a행렬과 b행렬을 뺀다.
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            subtract_matrix[i][j] = matrix_a[i][j] - matrix_b[i][j];
    }

    print_matrix(subtract_matrix, row, col);

    free_matrix(subtract_matrix, row, col);
    return 1;
}


/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return -1;
    }
    /* check post conditions */
    if (matrix == NULL || matrix_t == NULL) {
        printf("Check the sizes of row and col!\n");
        return -1;
    }
    for (int i = 0; i < col; i++) { //전치행렬에 값을 넣는 반복분
        for (int j = 0; j < row; j++) {   
            matrix_t[j][i] = matrix[i][j];
        }
    }

    return 1;

}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    if (row <= 0 || col <= 0) {
        printf("Check the sizes of row and col!\n");
        return -1;
    }
    /* check post conditions */
    if (matrix_a == NULL || matrix_t == NULL) {
        printf("Check the sizes of row and col!\n");
        return -1;
    }
    int i, j, k;
    int** multi_matrix = create_matrix(row, row);  //곱하기 행렬을 형성한다

    for (i = 0; i < row; i++) { 
        for (j = 0; j < row; j++) {
            multi_matrix[i][j] = 0; //multi_matrix의 원소 0으로 초기화
            for (k = 0; k < col; k++) {
                multi_matrix[i][j] += matrix_a[i][k] * matrix_t[k][j]; //행렬의 곱하기 연산 공식
            }
        }
    }
    print_matrix(multi_matrix, row, row);
    free_matrix(multi_matrix, row, row);
    
    return 1;
}

