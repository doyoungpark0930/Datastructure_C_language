#include <stdio.h>
#include <stdlib.h>

void main(){
    printf("Name=Do young park,StduentId=2018038077\n");
    int **x;   //더블포인터 선언

    printf("sizeof(x)   = %lu\n",sizeof(x));    //x는 주소값을 담고 있고 32bit 주소체제를 쓰므로 4byte
    printf("sizeof(*x)  = %lu\n",sizeof(*x));   //*x는 주소값을 담고 있고 32bit 주소체제를 쓰므로 4byte
    printf("sizeof(**x) = %lu\n",sizeof(**x));  //**x int형 값이므로 4byte

}