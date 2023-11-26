/*
 * hw12-sorting-hashing.c
 *
 *  Created on: May 22, 2021
 *  작성자: 박도영
 *  작성일자: 2021/05/31
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
    printf("2018038077 Do young park\n");
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array); 
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할 수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL) //a가 가리키는 값이 있다면 동적 할당 초기화
		free(a);
	return 0;
}

void printArray(int *a) 
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a) //단순 선택 정렬
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; //배열의 최솟값의 인덱스 
		min = a[i]; //최솟 값이 a[i]라고 가정한다
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j]) //a[j]가 min보다 작다면, a[j]를 최솟 값으로 가정하고, 최솟값의 인덱스도 j로 바뀐다
			{
				min = a[j];
				minindex = j;
			}
		}
		a[minindex] = a[i]; //a[i]에 a[i]의 뒤쪽에서 발견된 최솟값과 교체한다
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a) //단순 삽입 정렬
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++) //a[1]부터 선택해서 선택된 a[i]이전의 요소에 적절한 위치를 찾아서 삽입된다
	{
		t = a[i]; //t는 선택된,삽입될 값
		j = i;
		while (a[j-1] > t && j > 0) //이전의 요소중에 자기보다 작은값이 나올때까지 반복
		{
			a[j] = a[j-1];
			j--;
		}
		a[j] = t;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a) //버블정렬
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++) //총 MAX_ARRAY_SIZE만큼 반복하나, 하나씩 비교해가며 정렬을 해나가기 때문에 i가 커질수록 반복문은 돌아가지만, 교체하는 량은 적어진다
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++) //a[1]부터 마지막 요소까지 실행, 한 칸 위의것과 하나씩 비교해가며 바꾼다
		{
			if (a[j-1] > a[j]) //a[j-1]>a[j]라면 a[j-1]과 a[j]를 서로 바꾼다
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) //간격이 h나는 만큼의 배열끼리 쌍을 이루겠다는 뜻
	{
		for (i = 0; i < h; i++) //a[0]부터 h만큼 차이나는 쌍을 a[h-1]의 쌍까지 반복
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)//간격이 h만큼 나는 쌍끼리 크기 비교해서 교체
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v) //크기 비교해서 교체하는 과정
				{
					a[k] = a[k-h]; //a[k]와 앞쪽으로 h만큼 떺어져있는 배열의 요소와 바꾼다
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)// recursive방식으로 퀵정렬 ,가장 효율적
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1]; //기준점을 정함
		i = -1; //배열의 첫 요소부터 시작할 인덱스
		j = n - 1; //배열의 끝 요소부터 시작할 인덱스

		while(1)
		{
			while(a[++i] < v); //기준점보다 크거나 같은 값이 나올 때 까지 반복
			while(a[--j] > v); //기준점보다 작거나 같은 값이 나올 떄 까지 반복

			if (i >= j) break; //i가 j보다 크다면 바꿀 필요가 없다는 뜻
			t = a[i];   //a[j]와 a[i]를 바꾸는 작업
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];   //a[i]와 a[n-1]을바꿈> 순서에 맞게 정렬
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);//a[0]부터 a[i-1]까지 다룸
		quickSort(a+i+1, n-i-1); //a[i+1]부터 마지막 까지 다룸
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++) //hash table의 값을 모두 -1로 초기화
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1) //전에 방문한 적이 없다면 hashcode의 값을 넣는다
		{
			hashtable[hashcode] = key;
		} else 	{ //전에 방문한 적이 있다면

			index = hashcode;

			while(hashtable[index] != -1) //방문한 적이 없는 hashtable을 찾을때까지 반복
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key; //비어있는 hashtable에 key대입
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);

	if(ht[index] == key)
		return index;

	while(ht[++index] != key) //key값을 찾을떄까지 인덱스를 올린다 , 찾으면 반환
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}



