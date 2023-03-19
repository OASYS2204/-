#include<stdio.h>

int main(void)
{
    int a[4][5];
    printf("&a[0][0] = %p\n&a[0][1] = %p\n&a[1][0] = %p\n", &a[0][0], &a[0][1], &a[1][0]);
    printf("&a[0][2] = %p\n&a[0][3] = %p\n&a[0][4] = %p\n", &a[0][2], &a[0][3], &a[0][4]);
    printf("\nsizeof(a) = %zu\nsizeof(a[0]) = %zu\n", sizeof(a), sizeof(a[0]));
    printf("\n&a[0] = %p\n&a[1] = %p\n", &a[0], &a[1]);
    return 0;
}