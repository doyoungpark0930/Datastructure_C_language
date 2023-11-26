#include <stdio.h>
#include <stdlib.h>
int main(void){
    printf("Name=Do young park, StudentId=2018038077\n");
   int list[5]; //원소의 개수가 5개고 이름이 list인 배열 선언
   int *plist[5]={NULL,};   //포인터배열 형성 후 plist[0]은 아무것도 가리키지 않는,NULL값으로 초기화

   plist[0]=(int*)malloc(sizeof(int)); //plist[0]에 int형크기의 동적 배열 한 칸 할당

   list [0]=1;      //list[0]의 값 1로 초기화
   list [1]=100;    //list [1]의 값 2로 초기화

   *plist[0]=200;   //plist[0]이 가리키는 변수의 값을 200으로 초기화

   printf("value of list[0] = %d\n",list[0]);   //list[0]의 값
   printf("address of list[0]      = %p\n",&list[0]);   //list[0]의 주소
   printf("value of list           = %p\n",list);       //배열의 이름이 주소이다.
   printf("address of list (&list)  = %p\n",&list);      //배열이름의 주소는 배열의 이름과 같다

   printf("-----------------------------------\n\n");
   printf("value of list[1]     = %d\n",list[1]);       //list[1]의 값
   printf("address of list[1]   = %p\n",&list[1]);      //list[1]의 주소
   printf("value of *(list+1)   = %d\n",*(list+1));     //list에서 1만큼 떨어진 값 참조하여 호출
   printf("address of list+1    = %p\n",list+1);        //list에서 1만큼 떨어진 변수의 주소

   printf("-----------------------------------\n\n");

   printf("value of *plist[0] = %d\n",*plist[0]);       //plist[0]이 가리키는 값
   printf("&plist[0]          = %p\n", &plist[0]);      //plist[0]의 주소
   printf("&plist             = %p\n",&plist);          //plist의 주소는 plist의 값과 같다
   printf("plist              = %p\n",plist);            //plist=&plist[0]
   printf("plist[0]           = %p\n",plist[0]);        //plist[0]이 가리키는 곳의 주소
   printf("plist[1]           = %p\n",plist[1]);        //plist[1]~plist[4]는 할당된 것이 없으므로 NULL값
   printf("plist[2]           = %p\n",plist[2]);
   printf("plist[3]           = %p\n",plist[3]);
   printf("plist[4]           = %p\n",plist[4]);
   
   free(plist[0]);      //동적 할당 해제

    return 0;
}