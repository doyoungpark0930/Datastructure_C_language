/*
 * Binary Search Tree #2
 * 작성자 :박도영
 * 작성일자: 2021/05/09
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	int key;
	struct node* left;
	struct node* right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE]={NULL,};
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE]={NULL,};
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;
	printf("Do young park/2018038077\n");
	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			//printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;
	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if (ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224s
 */
void iterativeInorder(Node* node)
{
	for(;;)
	{
		for(;node;node=node->left) 
			push(node);		//스택에 삽입
		node=pop();		//스택에서 삭제

		if(!node)//공백 스택이라면
		{
			memset(stack,NULL,sizeof(stack)); //끝날떄는 스택 초기화
			top=-1;
			break;
		}
		printf(" [%d] ",node->key);
		node=node->right;
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr) //레벨 순서 트리 순회
{
	if(!ptr) return ; //공백 트리라면 함수를 빠져나간다
	enQueue(ptr); //ptr이 가리키고 있는 노드을 rear이 가리키게 한다

	for(;;){
		ptr=deQueue(); //front가 다음 노드을 가리키게하고 그 노드를 ptr이 가리킨다
		if(ptr)
		{
			printf(" [%d] ",ptr->key);
			if(ptr->left)
				enQueue(ptr->left);
			if(ptr->right)
				enQueue(ptr->right);

		}
		else
		{	
			memset(queue,NULL,sizeof(queue)); //끝날 떄는 큐 초기화
			front=rear=-1;
			break;
		}
		
		
	}
}



	
int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while (ptr != NULL) {

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	Node* ptr=head->left;
	Node* trail = head; 
	int returnKey = 0;
	if (ptr != NULL) //노드가 하나라도 있다면
	{
		while (ptr != NULL) {
			if (key == ptr->key) //key값을 갖고있는 노드를 발견한다면
				break;
			trail = ptr;
			if (key < ptr->key)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
		if (ptr == NULL) { //ptr이 NULL을 가리킨다는 것은 값을 찾을 수 없다는 뜻
			printf("Cannot find the value\n");
			return NULL;

		}
		if (ptr->left == NULL && ptr->right == NULL) //자식노드가 없다면,즉 leaf노드라면
		{ 
			if (trail == head) //트리의 노드가 하나 밖에 없다면
			{ 
				trail->left = NULL;
				returnKey = ptr->key;
				free(ptr);
				return returnKey;
			}
			if (ptr->key < trail->key) //leafNode의 key가 부모노드의 key보다 작다면 부모노드의 leftChild는 NULL을 가리킨다
				trail->left = NULL;
			if (ptr->key > trail->key) //leaftNode의 key가 부모노드의 key보다 크다면 부모노드의 rightChild는 NULL을 가리킨다
				trail->right = NULL;
			returnKey = ptr->key;
			free(ptr);
			return returnKey;
		}
		else if(ptr->left!=NULL&&ptr->right!=NULL) //자식 노드가 두 개 라면
		{
			//오른쪽 서브트리에서 가장 작은원소로 대체하는 방식
			Node* endptr=ptr->right;
			Node* endptrTrail=ptr;
			while(endptr->left){ //endptr이 오른쪽 서브트리의 가장 작은 원소를 가리키게 되면 반복문을 빠져나온다
				endptrTrail=endptr;
				endptr=endptr->left;
			}

			if(endptrTrail->key==ptr->key) //오른쪽 서브트리의 최솟값이 서브트리의 첫번째 노드라면
			{
				endptr->left=ptr->left;
			}
			else
			{
				endptrTrail->left=NULL;
				endptr->left=ptr->left;
				endptr->right=ptr->right;
			}

			if (ptr->key < trail->key) //지울 노드의 key가 부모노드의 key보다 작다면
				trail->left=endptr;
			else	//지울 노드의 key가 부모노드의 key보다 크다면
				trail->right=endptr;
			returnKey = ptr->key;
			free(ptr);
			return returnKey;



		}
		else //자식 노드가 한 개 라면
		{
			
			if(ptr->left!=NULL) //ptr의 왼쪽 노드에 자식이 있다면
			{
				if (ptr->key < trail->key) //삭제할 노드가 부모노드의 왼쪽에 있다면
				trail->left=ptr->left;
				else	//삭제할 노드가 부모노드의 오른쪽에 있다면
				trail->right =ptr->left;
				returnKey=ptr->key;
				free(ptr);
				return returnKey;
			}
			else //ptr의 오른쪽 노드에 자식이 있다면
			{	
				if (ptr->key < trail->key) //삭제할 노드가 부모노드의 왼쪽에 있다면
				trail->left=ptr->right;
				else	//삭제할 노드가 부모노드의 오른쪽에 있다면
				trail->right =ptr->right;
				returnKey=ptr->key;
				free(ptr);
				return returnKey;
			}
		}
	}
	else { 
		printf("There is no Node to delete\n");
	}
}


void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{//스택에서 pop
	return stack[top--];
}

void push(Node* aNode)
{ //스택에 삽입
	stack[++top]=aNode;
}



Node* deQueue()
{ //front가 다음 노드을 가리키게하고 그 노드를 반환한다
	return queue[++front];
}

void enQueue(Node* aNode)
{ //rear을 하나 증가시키고, queue[rear]가 aNode가 가리키는 노드를 가리킴으로써, 큐 삽입
	queue[++rear]=aNode;
}





