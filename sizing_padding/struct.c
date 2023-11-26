#include <stdio.h>

struct student1{    //구조체 함수 선언
    char lastName;
    int studentId;
    char grade;
};

typedef struct {    //typedef구조체 함수 선언
    char lastName;
    int studentId;
    char grade;
}student2;

int main(){
    printf("Name=Do young park,studentID=2018038077");
    struct student1 st1={'A',100,'A'}; //구조체 변수 정의와 초기화

    printf("st1.lastName = %c\n",st1.lastName); //구조체 안의 변수들에 접근하는 방식
    printf("st1.studentId = %d\n",st1.studentId);
    printf("st1.grade = %c\n",st1.grade);

    student2 st2 = {'B',200,'B'};   //구조체 변수 정의와 초기화

    printf("\nst2.lastName = %c\n",st2.lastName);   //구조체 안의 변수들에 접근하는 방식
    printf("st2.studentId = %d\n",st2.studentId);
    printf("st2.grade = %c\n",st2.grade);

    student2 st3; //구조체 함수 선언

    st3=st2;    //구조체 함수 복사

    printf("\nst3.lastName = %c\n",st3.lastName);   //구조체 함수가 잘 복사되었는지 출력하여 확인
    printf("st3.studentId = %d\n",st3.studentId);
    printf("st3.grade = %c\n",st3.grade);

    /* equality test */     //이 부분은 주석제거시 에러가난다, 구조체끼리는 안의 변수 하나하나 비교해야한다
    /*
    if(st3 == st2)
        printf("equal\n");
    else
        printf("not equal\n");
    */

   return 0;
}
