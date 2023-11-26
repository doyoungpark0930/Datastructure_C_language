/*
 *  doubly circular linked list
 *	작성자 : 박도영
 *  작성일자 : 2020/04/23
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
 /* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	printf("2018038077 Do young park\n");
	char command;
	int key;
	listNode* headnode = NULL;

	do {
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)
		freeList(*h);
	*h = NULL;
	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999; //첫 노드의 값은 따지지 않는다. 
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h) {
	listNode* p = h->rlink;
	listNode* prev;
	while (p!=h) { //p가 첫노드(값이없는 노드)를 가리키지 않는다면
		prev = p; //prev은 p가 가리키는 곳을 가리킨다
		p->llink->rlink = p->rlink;
		p->rlink->llink = p->llink;
		p = p->rlink;
		free(prev);
	}
	free(h); //첫 노드마저 할당해제한다

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while (p != NULL && p != h) {  
		printf("[ [%d]=%d ] ", i, p->key);  //노드들의 값 하나씩 출력
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i); //총 노드들의 개수, 첫노드는 아무것도 없는 노드이기 때문에 첫노드만 있으면 0개로 친다


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while (p != NULL && p != h) { 
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink); //각 노드의 주소와 llink,rlink의 주소 출력
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	if (h != NULL) { //노드가 하나라도 있다면
		listNode* node = (listNode*)malloc(sizeof(listNode));
		node->key = key;
		node->rlink = h;
		node->llink = h->llink;
		h->llink->rlink = node;
		h->llink = node;

	}
	else { //아무 노드가 없다면
		printf("There are no Nodes, try it again after initializing\n");
	}
	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	if (h != NULL && h->rlink != h) { 
		listNode* p = h->llink;
		p->llink->rlink = h;
		p->rlink->llink = p->llink;
		free(p);
	}
	else //노드가 아예 없거나 하나만(값이없는 노드만) 있을 경우, 삭제할 노드가 없다고 출력
	{
		printf("can't find node to delete.\n");
	}

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	if (h != NULL) { //노드가 하나라도 있다면
		listNode* node = (listNode*)malloc(sizeof(listNode));
		node->key = key;
		node->rlink = h->rlink;
		node->llink = h;
		h->rlink->llink = node;
		h->rlink = node;


	}
	else { //아무 노드가 없다면
		printf("There are no Nodes, try it again after initializing\n");
	}
	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	if (h != NULL && h->rlink != h) {
		listNode* p = h->rlink;
		p->rlink->llink = p->llink;
		p->llink->rlink = p->rlink;
		
		free(p);
	}
	else //노드가 아예 없거나 하나만(값이없는 노드만) 있을 경우, 삭제할 노드가 없다고 출력
	{
		printf("can't find node to delete.\n");
	}

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	listNode* lead = h; //lead포인터는 맨 앞에, 중간은 middle, 뒤에는 trail
	if (lead != NULL&&lead->rlink!=h) { //값이 있는 노드가 하나 이상 있을때 
		lead = h->rlink->rlink; //lead가 세번 째 노드를 가리킨다 , 노드가 하나밖에 없을 떄는 자기자신을 가리킴
		listNode* trail = h; //trail은 첫 노드(값이 없는 노드)를 가리킨다
		listNode* middle = h->rlink; // middle은 두번째 노드를 가리킨다


		while (lead != h->rlink) { //노드가 가리키는 방향을 뒤집음으로써 역순배치
			middle->rlink = trail;
			middle->llink = lead;
			trail = middle;
			middle = lead;
			lead = lead->rlink;
		}
		middle->rlink = trail; //마지막은 반복문에서 빠져나올때 처리가 안됨으로 여기서 처리
		middle->llink = lead;
	}
	else
	{
		printf("can't find nodes to invert.\n");
	}

	return 0;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
 **/
int insertNode(listNode* h, int key) {
	if (h != NULL) { //노드가 하나라도 있다면
		listNode* node = (listNode*)malloc(sizeof(listNode));
		node->key = key;
		listNode* p = h->rlink;
			while (p!=h&&node->key >= p->key) { 
				p = p->rlink;

				
			}
			if (p == h) { //p가 첫 노드를 가리킬 때는 입력받은 key값이 모든 노드의 값보다 가장 크다는 뜻이므로 노드끝에삽입
				node->rlink = h;
				node->llink = h->llink;
				h->llink->rlink = node;
				h->llink = node;
			}
			else {//node의값이 p의 값보다 작을때 
				node->rlink = p;
				node->llink = p->llink;
				p->llink->rlink = node;
				p->llink = node;
			}
		

	}
	else { //아무 노드가 없다면
		printf("There are no Nodes, try it again after initializing\n");
	}
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	if (h != NULL) { //노드가 하나라도 있다면
		listNode* node = (listNode*)malloc(sizeof(listNode));
		node->key = key;
		listNode* p = h->rlink;
		while (p != h && node->key != p->key) {
			p = p->rlink;
		}
		if (p == h) { //일치하는 값이 없을 때
			printf("can't find same value.\n");
			
		}
		else {//p의 key와 node의 key가 같을 때
			p->llink->rlink = p->rlink;
			p->rlink->llink = p->llink;
			free(p);
		}


	}
	else { //아무 노드가 없다면
		printf("There are no Nodes, try it again after initializing\n");
	}

	return 0;
}
