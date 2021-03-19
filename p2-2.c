#include <stdio.h>

void print1 (int *ptr,int rows); //배열의 주소와 해당 값을 출력하는 함수

int main(){
    printf("Name=Do young park,StudentId=2018038077\n");

    int one[]={0,1,2,3,4};  //배열 선언과 초기화

    printf("one        = %p\n",one);        //배열의 이름이 주소이다
    printf("&one       = %p\n",&one);       //배열의 주소는 배열의 이름과 같다
    printf("&one[0]    = %p\n",&one[0]);    //배열 첫번쨰 요소값의 주소는 배열의 이름 one=&one[0]
    printf("\n");

    print1(&one[0],5);  //배열의 첫번 째 요소의 주소를 전달하고,배열의 요소수를 전달

    return 0;
}

void print1 (int *ptr, int rows)
{
    /*print out a one-dimensional array using a pointer */

    int i;
    printf("Address \t Contents\n");
    for(i=0;i<rows;i++)
    printf("%p \t   %d\n",ptr+i,*(ptr+i));  //배열의 주소와 해당 값 출력
    printf("\n");
}