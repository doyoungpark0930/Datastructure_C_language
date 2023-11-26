/*
 *  doubly-linked-list.c
 *	작성자 : 박도영
 *  작성일자 : 2021/04/24
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
 /* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
		 singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h); /*반환할 때 주소를 반환하지 않는다. singly-linked-list의 initialize 함수에서 만약 h= (headNode*)malloc(sizeof(headNode));
하게 된다면 함수를 빠져나올때 힙영역에 할당은 되었는데 h가 함수의 종료와 함께 소멸됨으로써 main함수에 있던 headnode가 동적할당 된 곳을 가리키지도 않게되고,
동적 할당 된 것은 아무 기능도 하지 못한 채 있게 된다. 그걸 극복하기위해 여기선 더블포인터를 사용했다*/

/* note: freeList는 싱글포인터를 매개변수로 받음
		- initialize와 왜 다른지 이해 할것
		- 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	printf("2018038077 Do young park\n");
	char command;
	int key;
	headNode* headnode = NULL;
	printf("use it initializing\n");
	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
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
			initialize(&headnode);
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


int initialize(headNode** h) { //h는 headnode의 주소를 받는다
	//headnode 가 NULL이 아니면 freeList를 호출하여 할당해제
	if (*h != NULL)
		freeList(*h);

	// headNode에 대한 메모리를 할당하고 할당된 곳의 주소를 *h에 대입한다
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;
	
	return 1;
}

int freeList(headNode* h) {
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; //포인터 p가 first가 가리키고있는 노드를 가리키게한다
	listNode* prev = NULL;
	while (p != NULL) { //포인터 p가 NULL이 아니라면 (반복문을 빠져 나올때 first가 가리키고 있는 노드는 없는 상태)
		prev = p; // p가 가리키는 곳을 prev이 가리킨다
		p = p->rlink; //p는 다음 노드를 가리킨다
		free(prev); // prev이 가리키는 곳을 할당 해제 한다
	}
	free(h); //h가 가리키고 있는 힙 영역의 공간을 해제한다







	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}
	
	p = h->first;

	
	while(p!=NULL){		//p가 NULL을 가리킬 때까지 반복한다.
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);
	return;

	
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode * p=h->first;
	listNode* trail = NULL; //노드가 하나 이상 있을 경우, p의 전 노드를 가리키기 위해 이용
	listNode* node = (listNode*)malloc(sizeof(listNode)); // node하나를 동적 할당
	node->key = key; //node에 key값을 대입
	
	if (p == NULL) { //노드가 없다면 
		h->first = node;
		h->first->llink = NULL; //첫 노드니까 llink,rlink모두 NULL을 가리킨다
		h->first->rlink = NULL;
	}
	else { //노드가 하나 이상 있다면
		while (p != NULL) {
			trail = p; // 마지막 빠져나올때 trail은 마지막 노드를 가리키고 있다.
			p = p->rlink;
		}
		trail->rlink = node; //마지막에 노드 삽입
		node->llink = trail;
		node->rlink = NULL;
	}
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* p = h->first; //p는 first가 가리키는 노드를 가리킴
	if (p != NULL) { //노드가 하나 이상 있을 때
		if (p->rlink==NULL) { //노드가 하나밖에 없다면
			free(p);
			h->first = NULL; //가리키는 노드가 없으므로 NULL을 가리킨다
			return 0;
		}
		else // 노드가 두개 이상 있을 때
		{
			while (p->rlink != NULL) { //마지막 나올 때 p가 마지막 노드를 가리키고 있음
				p = p->rlink;
			}
			p->llink->rlink = NULL;// 마지막에서 두번 째 노드가 NULL을 가리키게 한다
			free(p); //그리고 마지막 노드 해제


		}
	}
	else
	{
		printf("No nodes assigned\n");
	}


	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	listNode* p = h->first;
	listNode* node = (listNode*)malloc(sizeof(listNode)); // node하나를 동적 할당
	node->key = key; //node에 key값을 대입
	if (p == NULL) { //노드가 없다면 
		h->first = node;
		h->first->llink = NULL; //첫 노드니까 llink,rlink모두 NULL을 가리킨다
		h->first->rlink = NULL;
	}
	else { //노드가 하나 이상 있다면
		p->llink = node;
		node->rlink = p;
		node->llink = NULL;
		h->first = node; // first가 새로 생긴 첫 노드를 가리키게 한다.
	
	}
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* p = h->first; //p는 first가 가리키는 노드를 가리킴
	listNode* trail = NULL;
	if (p != NULL) { //노드가 한 개 이상 있을 때
		if (p->rlink==NULL) { //노드가 하나 뿐이라면
			free(p);
			h->first = NULL;
		}
		else { //노드가 두 개 이상 있을때
			h->first = p->rlink;
			p->rlink->llink = NULL;
			free(p);
		}

	}
	else {
		printf("No nodes assigned\n");
	}
	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode* lead = h->first; //lead포인터는 맨 앞에 중간은 middle, 중간 앞에는 trail
	if (lead != NULL) { //노드가 하나 이상 있을때 
		lead = h->first->rlink; //lead가 두번 째 노드를 가리킨다 , 노드가 하나밖에 없을 떄는 자기자신을 가리킴
		listNode* middle = h->first; // middle은 첫 노드를 가리킨다
		listNode* trail = NULL;
		


		while (lead != NULL) { //노드가 가리키는 방향을 뒤집음으로써 역순배치
			middle->rlink = trail;
			middle->llink = lead;
			trail = middle;
			middle = lead;
			lead = lead->rlink;
		}
		middle->rlink = trail; //마지막은 반복문에서 빠져나올때 처리가 안됨으로 여기서 처리
		middle->llink = lead;
		h->first = middle;// middle이 가리키고 있는 값이 첫 노드가 됨으로 first가 middle이 가리키는 곳을 가리킨다.
	}
	else
	{
		printf("No nodes assgined\n");
	}
	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	listNode* p = h->first;
	listNode* trail = NULL;

	if (p != NULL) { //노드가 한 개 이상이라면
		while (p != NULL && node->key > p->key) { //node의 값이 p가 가리키는 값보다 크다면
			trail = p;
			p = p->rlink; //p는 다음 노드를 가리킨다
		}
		if (p == h->first) { // node의 값이 첫 번째 노드의 값보다 작다는 뜻이니 맨 앞에 삽입
			node->rlink = p;
			node->llink = NULL;
			p->llink = node;
			h->first = node;
		}
		else {
			node->rlink = p;
			node->llink = trail;
			trail->rlink = node;
			if (p != NULL) { //p가 가리키는 값이 NULL이 아니라면, 즉 입력받은 key보다 큰 값이 어떤 노드에 존재한다면
				p->llink = node;
			}
		}

			
	}
	else //노드가 없다면
	{ //할당된 노드를 추가한다
		node->llink = NULL;
		node->rlink = NULL;
		h->first = node;
	}
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* p = h->first;
	if (p != NULL) { //first가 가리키는 노드가 있다면

		while (p!= NULL && p->key != key) { // p가 가리키는 값과 입력받은 key가 다르다면
			p = p->rlink;
			
		}
		if (p == h->first) { //첫번째 노드의 값과 입력받은 key가 같다면
			h->first = p->rlink;
			free(p);
			if (h->first != NULL) { //노드가 두 개 이상 존재 했다면
				h->first->llink = NULL;
			}
		}
		else { 
			if (p != NULL) { //p가 가리키는 노드의 값과 입력받은 key가 같을 때
				p->llink->rlink = p->rlink;
				if (p->rlink != NULL) { //p가 가리키는 값이 맨 마지막 노드가 아닐 때
					p->rlink->llink = p->llink;
				}
				free(p);
			}
			else {//p가 NULL을 가리킬 때, 즉 일치하는 노드가 없을 때
				printf("can't find the vaule.\n");
			}
		}

	}
	else
	{//first가 가리키는 노드가 없다면
		printf("No node assigned\n");
	}
	return 1;
}


