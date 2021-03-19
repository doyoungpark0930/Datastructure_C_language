#include <stdio.h>

#define MAX_SIZE 100 //상수 선언

float sum(float [],int); //총 합 함수   선언
float input[MAX_SIZE],answer;   //요소의 개수가 MAX_SIZE인 input배열과 총 합을 담을 변수 전역변수로서 선언
int i;  //전역변수 i선언

void main(void){
    printf("Name=Do young park, StudentId=2018038077\n");
    for(i=0;i<MAX_SIZE;i++) //input에 값0부터 99까지 초기화
    input[i]=i;

    /*for checking call by reference */
    printf("address of input = %p\n",input);   //배열의 이름이 배열의 주소와 같다

    answer = sum(input,MAX_SIZE);   //answer에 총 합을 넣는다
    printf("The sum is : %f\n",answer); //총 합 출력

    return 0;
}

float sum(float list[],int n)   //float list[]는 float *list와 같으며 주소를 받는다
{
    printf("value of list = %p\n",list);    //list의 값은 input의 주소가된다
    printf("address of list = %p\n\n",&list);//여기서 list는 input의 주소를 받을 뿐 input이 아니다.

    int i;
    float tempsum=0;    
    for(i=0; i<n;i++)       //0부터 99까지의 합
        tempsum+=list[i];
    return tempsum;
}