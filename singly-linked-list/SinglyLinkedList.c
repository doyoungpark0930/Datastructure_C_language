/*
 * singly linked list
 * 작성자: 박도영
 * 작성일자: 2021/04/11
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
 /* 필요한 헤더파일 추가 */

typedef struct Node { // 노드 구조체 형성
	int key;
	struct Node* link;
} listNode;

typedef struct Head { // 더블포인터 대신 구조체안의 구조체의 방법을 이용
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	printf("Name=Do young park,StudentID=2018038077\n");
	char command;
	int key;
	headNode* headnode = NULL;

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (h != NULL)
		freeList(h); 

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; //포인터 p가 first가 가리키고있는 노드를 가리키게한다
	

	listNode* prev = NULL; 
	while (p != NULL) { //포인터 p가 NULL이 아니라면 (반복문을 빠져 나올때 first가 가리키고 있는 노드는 없는 상태)
		prev = p; // p가 가리키는 곳을 prev이 가리킨다
		p = p->link; //p는 다음 노드를 가리킨다
		free(prev); // prev이 가리키는 곳을 할당 해제 한다
	}
	free(h); //h가 가리키고 있는 힙 영역의 공간을 해제한다
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) { 

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node하나를 동적 할당
	node->key = key; //node에 key값을 대입

	node->link = h->first; //node의 link가 first가 가리키는 노드를 가리킴
	h->first = node; //first가 node를 가리킨다 

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰 값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* p = h->first;
	listNode* node = (listNode*)malloc(sizeof(listNode)); // node하나를 동적 할당
	listNode* trail;
	node->key = key;
	if (h->first != NULL) //first가 가리키는 노드가 있다면
	{ 
		if ((node->key) < (p->key)) //첫 노드의 key보다 입력받은 key가 더 작을때
		{ 
			node->link = p; // node를 첫 노드앞에 삽입한다
			h->first = node;
		}
		else 
		{ //node가 노드들 사이에 끼거나 맨 마지막에 삽입 될 때
			while ((node->key >= p->key)&&p->link!=NULL) {
				trail = p;
				p = p->link;
			}
			if (node->key<p->key) { //node의 key가 p의 key보다 작을 때 
				trail->link = node;
				node->link = p;
			}
			else { // node의 key가 p의 key보다 작지도 않은데 반복문을 빠져 나온 경우,즉 p->link=NULL이라서 빠져 나온 것이다. 맨 마지막에 삽입해준다
				p->link = node;
				node->link = NULL;
			}
			
		}
	
	}
	else {// first가 가리키는 노드가 없다면 그냥 삽입한다
		node->link = NULL;
		h->first = node;

	}
	return 0;

}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // node하나를 동적 할당
	listNode* p = h->first;
	node->key = key; //node에 key값을 대입

	node->link = NULL; //node의 link가 아무것도 가리키지 않도록 한다
	
	if (h->first) { //first가 가리키는 노드가 잇을때
		while ((p->link) != NULL) { //p가 가리키는 노드의 다음 노드가 NULL이라면 반복
			p = p->link; // p는 다음 노드를 가리킨다
		}
		p->link = node; //p가 가리키는 노드의 다음 노드가 node가 되도록 한다
	}
	else { //first가 가리키는 노드가 없을 때
		h->first = node; //first가 node를 가리키게한다
	}

	

	return 0;
}


/**
 * list의 첫 번째 노드 삭제
 */
int deleteFirst(headNode* h){
	if ((h->first) != NULL) { //first가 아무것도 가리키지 않는다면 노드가 없음을 알리는 내용 출력
		listNode* p = h->first;
		h->first = p->link; //두 번째 노드를 first가 가리키게한다
		free(p);
	}
	else
		printf("노드가 없습니다\n");

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* p = h->first;
	listNode* trail;// p가 가리키는 노드의 선행 노드를 가리킴
	if (h->first) { // first가 가리키는 노드가 있을때
		if(p->key==key){ // 첫 노드부터 key값이 일치할 경우
			h->first = p->link;
			free(p);
		}
		else { //첫 노드가 key값과 일치하지 않을 경우

			while (p->key != key && p->link != NULL) {
				trail = p;
				p = p->link;
			}
			if (p->key==key) { //p가 가리키는 값이 key와 같은경우
				trail->link = p->link;
				free(p);
			}
			else //key를 찾지 못했을때 즉 p->link는 NULL이면서 p->key가 key가 아닐경우
			{
				printf("입력하신 값을 찾을 수 없습니다\n");
			}
			
		}
	}
	else
	{
		printf("삭제할 노드가 없습니다\n");
	}
	return 0;


}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	listNode* p = h->first;
	listNode* trail; //trail이 가리키는 노드는 p가 가리키는 노드의 선행노드 


	if (h->first) { // first가 가리키는 노드가 잇을때
		while ((p->link) != NULL) { // p가 가리키는 노드의 다음 노드가 NULL이라면 반복
			trail = p;
			p = p->link; // p는 다음 노드를 가리킨다
		}
		free(p);
		trail->link = NULL;
	
	}
	else { //first가 가리키는 노드가 없을 때
		printf("삭제할 노드가 없습니다\n");
		
	}

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) { 
	listNode* trail, *middle,*lead; //역순 배치할 때 다음 노드,전 노드,현재 노드에 대한 정보를 다 알아야하므로 3개의 포인터가 필요하다
	trail = NULL;
	middle = NULL;
	lead = h->first;
	
	if (lead != NULL) { //노드가 하나이상 있다면
		while (lead) {
			trail = middle;
			middle = lead;
			lead = lead->link;
			middle->link = trail;
		}
		h->first = middle; // 반복문 빠져나올때 middle은 마지막 노드를 가리키고 있으므로 first가 마지막 노드를 가리키게 한다
	}
	else
	{
		printf("노드가 없습니다\n");
	}
	return 0;

}


void printList(headNode* h) { // 연결된 노드들을 출력한다
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

