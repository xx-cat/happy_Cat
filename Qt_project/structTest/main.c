#include <stdio.h>

typedef struct PDU{
    int a;
    int b;
    int c;
}PDU;

int main()
{
    printf("%d\n", sizeof(PDU));
    printf("Hello World!\n");
    return 0;
}
