#include <stdio.h>

int main(void){
    printf("Name=Do young park, StudentId=2018038077\n");
    
    int list[5]; //요소의 개수가 5인 배열 선언
    int *plist[5];  //포인터요소의 개수가 5개인 포인터 배열선언

    list[0]=10; //list의 첫번째 값을 10으로 초기화
    list[1]=11; //list의 두번째 값을 11으로 초기화

    plist[1]=(int*)malloc(sizeof(int)); //int형 한 칸을 동적할당하고 plist[1]가 가리키게함

    printf("list[0]\t\t = %d\n", list[0]);           //list[0]의 값을 추력
    printf("address of list \t= %p\n",list);        //list의 값 즉,주소를 출력
    printf("address of list[0]  \t= %p\n",&list[0]);    //list[0]의 주소를 출력
    printf("address of list + 1 \t= %p\n",list +0);     //list의 값 즉,주소를 출력
    printf("address of list + 2 \t= %p\n",list +1);     //list[1]의 주소를 출력하는 것과 같다
    printf("address of list + 3 \t= %p\n",list +2);     //list[2]의 주소를 출력하는 것과 같다
    printf("address of list + 4 \t= %p\n",list +3);     //list[3]의 주소를 출력하는 것과 같다
    printf("address of list + 5 \t= %p\n",list +4);     //list[4]의 주소를 출력하는 것과 같다
    printf("address of list[4] \t= %p\n",&list[4]);     //list[4]의 주소 출력

    free(plist[0]);     //동적 할당 해제

    
}