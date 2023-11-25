#include <stdio.h>

struct student{
    char lastName[13]; // 13 bytes
    int studentId;     // 4 bytes
    short grade;       // 2 bytes
};

int main()
{
    printf("Name=Do young park,studentID=2018038077\n");
    struct student pst; //구조체 변수 선언

    printf("size of student = %ld\n",sizeof(struct student));
    /*결과값이 19bytes가 아니라면, 이 컴파일러는 padding을 한다는 뜻이다.그렇다면 4byte단위로
    할당되어 24bytes가 나올것이다.*/
    printf("size of int = %ld\n",sizeof(int));  //int의 크기
    printf("size of short = %ld\n",sizeof(short));  //short의 크기
}