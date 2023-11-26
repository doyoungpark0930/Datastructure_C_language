
/*
 * circularQ.c
 * 작성자 :박도영 2018038077
 * 작성일자: 2021/04/03
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS


#define MAX_QUEUE_SIZE 4

typedef char element; //typedef를 이용하여 char를 element로 써서 편하게본다
typedef struct {
	element queue[MAX_QUEUE_SIZE]; //큐의 자리 MAX만큼 할당,하지만 넣을 수 있는 값은 MAX-1개
	int front, rear; 
}QueueType;


QueueType* createQueue(); //큐 생성 함수
int freeQueue(QueueType* cQ); //할당 된 큐의 동적 할당 해제
int isEmpty(QueueType* cQ); //큐가 비어있는지 확인하는 함수
int isFull(QueueType* cQ);	//큐가 꽉 찼는지 확인하는 함수
void enQueue(QueueType* cQ, element item); //큐에 값을 넣는 함수
void deQueue(QueueType* cQ, element* item); // 큐의 값 하나를 삭제하는 함수, 엄밀히 말하면 삭제되지는 않고, front가 움직이면서 삭제되는 것 처럼 보인다
void printQ(QueueType* cQ);	//큐 출력
void debugQ(QueueType* cQ);	//큐의 내부 요소 확인
element getElement();	//입력할 값을 입력받는다

int main(void)
{
	printf("[---- - [Do young park] [2018038077] ---- - ]");
	QueueType* cQ = createQueue();	//힙에 새로 생성된 큐를 포인터 cQ가 가리키게함
	element data;	//입력받을 값
	char command; //메뉴를 선택할 명령어 키

	do {
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
			freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');


	return 1;
}

QueueType* createQueue()
{
	QueueType* cQ;
	cQ = (QueueType*)malloc(sizeof(QueueType)); //힙에 동적 할당 
	cQ->front = 0;//front와 rear은 반드시 0으로 초기화를 해야함
	cQ->rear = 0;
	return cQ; //주소를 반환하여 call by reference가 가능하도록 함
}

int freeQueue(QueueType* cQ)
{
	if (cQ == NULL) return 1;
	free(cQ);
	return 1;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType* cQ)		//큐의 자리가 비어있는지 검사
{
	if (cQ->front == cQ->rear) {  //front와 rear이 같다면 비어있는 것이고 비어있다면 1을 반환하여 deQueue함수에서 삭제할지 판단하도록 한다
		printf("Queue is already empty");
		return 1;
	}
	return 0;
}

/* complete the function */
int isFull(QueueType* cQ)	// 큐의 자리가 꽉 차있는지 검사
{	
	int index_check = (cQ->rear + 1) % MAX_QUEUE_SIZE; 
	if (index_check == cQ->front) {		//front와 다음 rear의 값이 같다면 꽉 차있는것이고, 그렇다면 1을 반환하여 enQueue함수에서 추가할지 판단하도록 한다
		printf("you can't add a value any more.");
		return 1;
	}
	return 0;
}


/* complete the function */
void enQueue(QueueType* cQ, element item) 
{
	if (!isFull(cQ)) { // 꽉 찼는지 검사, 꽉 찼다면 빠져나간다
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; //rear가 다음 칸으로 이동한다
		cQ->queue[cQ->rear] = item;	//rear가 가리키는 곳에 입력한 값을 넣는다
	}

	return 0;
}

/* complete the function */
void deQueue(QueueType* cQ, element* item)
{
	if (!isEmpty(cQ)) {//비어있는지 검사, 비어 있다면 빠져나간다
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; //front가 다음 칸을 가리키도록 하면서 요소 하나가 삭제 됌
	}
	return 0;
}


void printQ(QueueType* cQ)
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE; //값이 처음 시작되는 곳
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE; //last-1이 값이 마지막으로 끝나는 곳이다

	printf("Circular Queue : [");

	i = first;
	while (i != last) {
		printf("%3c", cQ->queue[i]);
		i = (i + 1) % MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType* cQ)
{

	printf("\n---DEBUG\n");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if (i == cQ->front) { 
			printf("  [%d] = front\n", i); // front의 값은 따로 출력한다
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);	//나머지값은  그냥 출력한다

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //front와 rear의 값 출력
}

