/*
 * postfix.c
 * 작성자: 2018038077 박도영
 * 작성일자:2021/04/05
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20


typedef enum {
	lparen = 0, //왼쪽괄호
	rparen = 6,//오른쪽괄호
	times = 5,   //곱하기
	divide = 4,	//나누기
	plus = 3,   //더하기
	minus = 2,   //빼기
	operand = 1 //피연산자
} precedence;
int isp[] = { 0,1,2,3,4,5,6 }; //in stack precedence
int icp[] = { 7,1,2,3,4,5,6 }; // incoming precedence
char infixExp[MAX_EXPRESSION_SIZE];    //중위 표기식	
char postfixExp[MAX_EXPRESSION_SIZE];	//후위 표기식
char postfixStack[MAX_STACK_SIZE];	//중위표기식을 후위 표기식으로 가는 과정의 스택
int evalStack[MAX_STACK_SIZE];		//후위 연산표기식을 푸는 과정의 스택

int postfixStackTop = -1;  //후위 연산자 스택 안의 인덱스
int evalStackTop = -1;	  //후위 연산한 스택 안의 인덱스

int evalResult = 0;	

void postfixPush(char x); //후위 연산식으로 바꾸는 스택안에 x Push
char postfixPop(); //후위 연산식으로 바꾸는 스택 안에 x를 pop하고 반환,그리고 스택 인덱스를 하나 내린다
void evalPush(int x);//후위 연산한 스택에 x를 Push한다
int evalPop();//후위 연산한 스택에서 맨 위의 값을 pop해서 반환한다
void getInfix(); // 중위 표기 식 입력 함수
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c); //문자열 c의 맨 앞자리 문자를 postfixExp에 붙여넣는다
void toPostfix(); //중위 연산식을 후위 연산식으로 바꾸는 함수
void debug(); //중위 연산식, 후위연산식, 후위연산,중위표기식을 후위 표기식으로 가는 과정의 스택을 보여준다.
void reset(); //처음 실행 시킬때처럼 초기화
void evaluation();// 후위 연산식을 계산하는 함수

int main()
{
	printf("----- [Do young park] [2018038077] -----]");
	infixExp[0] = '\0';
	postfixExp[0] = '\0';
	char command;

	do {
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

void postfixPush(char x) //후위 연산식으로 바꾸는 스택안에 x Push
{
	postfixStack[++postfixStackTop] = x;
}

char postfixPop() //후위 연산식으로 바꾸는 스택 안에 x를 pop하고 반환,그리고 스택 인덱스를 하나 내린다
{
	char x;
	if (postfixStackTop == -1) //스택안에 아무것도 없다면 NULL값 반환
		return '\0';
	else {
		x = postfixStack[postfixStackTop--]; 
	}
	return x;// 스택안의 맨 윗 값 반환
}

void evalPush(int x) //후위 연산한 스택에 x를 Push한다
{
	evalStack[++evalStackTop] = x; // 후위 연산한 스택의 인덱스를 하나 증가시키고 x를 Push
}

int evalPop() //후위 연산한 스택에서 맨 위의 값을 pop해서 반환한다
{
	if (evalStackTop == -1)
		return -1;
	else
		return evalStack[evalStackTop--];
}


 
void getInfix() //중위 표기 식 입력 함수
{
	printf("Type the expression >>> ");
	scanf("%s", infixExp);
}

precedence getToken(char symbol)  //문자하나가 들어오면 연산자 토큰 반환
{
	switch (symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	default: return operand;
	}
}

precedence getPriority(char x) //문자 하나를 받아들여 연산자 토큰 반환
{ 
	return getToken(x);
}


void charCat(char* c) //문자열 c의 맨 앞자리 문자를 postfixExp에 붙여넣는다,(toPostfix함수에서 쓰임)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1); //문자열c의 맨 앞자리 문자를 postfixExp에 복사
	else
		strncat(postfixExp, c, 1); //문자열c의 맨 앞자리 문자를 postfixExp의 맨 뒤에 붙여넣는다
}


void toPostfix()
{
	
	char* exp = infixExp; //중위표기식 문자열 받음
	char x; //getToken에 들어갈 symbol
	precedence token;
	char temp;
	x = *exp; //중위표기식의 첫번째 문자
	int len; //문자열의 길이 

	while (*exp != '\0') //중위 표기식이 NULL이 나올때까지 반복한다는건, 중위표기식의  마지막 문자 까지 실행한다는 뜻
	{
		token = getToken(x);
		if (token == operand) {
			printf("%c", x);
			charCat(exp); //문자열 exp의 맨 앞자리 문자를 postfixExp에 붙여넣는다
		}
		else if (token == rparen) { 
			while (getToken(postfixStack[postfixStackTop]) != lparen) { //왼쪽 괄호가 나올 때까지 토큰들을 제거해서 출력시킴
				temp = postfixPop(); //pop한것을 temp로 받는다
				printf("%c", temp);	//받은 temp를 출력
				len = strlen(postfixExp); //postfixExp에 문자 temp를 넣음
				postfixExp[len] = temp;  //temp를 postfixExp끝에 넣는다
				postfixExp[len + 1] = '\0'; //문자열의 끝은 NULL이어야 하므로 postfixExp에 NULL을 붙여준다

			}
			postfixPop();//왼쪽 괄호를 버린다
		}
		else
		{
			while (isp[getPriority(postfixStack[postfixStackTop])] >= icp[token]) {
				temp = postfixPop();
				printf("%c", temp);
				len = strlen(postfixExp); //postfixExp에 문자 temp를 넣음
				postfixExp[len] = temp;
				postfixExp[len + 1] = '\0';
			 }
			postfixPush(x);
			}
		x = *(++exp);// 다음차례 문자로 넘어간다
		
		
	}
	while (postfixStack[postfixStackTop] != '\0') { //infixExp에 더 이상 문자가 없을경우, postfixStack의 모든 문자를 postfixExp에 pop을 이용하여 붙여넣는다
		temp = postfixPop();
		printf("%c", temp);
		len = strlen(postfixExp); //postfixExp에 문자 temp를 넣음
		postfixExp[len] = temp;
		postfixExp[len + 1] = '\0';
	}
	putchar('\n');


}
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postfixExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for (int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for (int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()
{
	char* exp = postfixExp; //후위표기식 문자열 받음
	char x; //getToken에 들어갈 symbol
	precedence token;
	char temp;
	x = *exp; //후위 표기식의 첫번째 문자

	int op1, op2; // pop해서 값을 받을 변수
	token = getToken(x);

	while (x != '\0') { //postfixExp의 끝이 NULL이라면 빠져나온다 

		if (token == operand)
			evalPush(x-'0'); //postfixExp의 숫자는 정수형이 아니라 문자라서 아스키 코드를 이용한다
		else
		{
			op2 = evalPop(); //pop해서 반환값을 받는다
			op1 = evalPop(); //pop해서 반환값을 받는다
			switch (token) {
			case plus: evalPush(op1 + op2); break;
			case minus:evalPush(op1 - op2); break;
			case times: evalPush(op1 * op2); break;
			case divide: evalPush(op1 / op2); break;
			}
		}
		x = *(++exp); 
		token = getToken(x);
	}
	evalResult = evalPop(); //evalStack의 마지막 남은 값이 결과 값이다,반환한다
	
}