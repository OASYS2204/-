#include<stdio.h>
int main(void)
{
    int genka, kakaku;
    double riritu;

    printf("���� ==> ");
    scanf("%d", &genka);
    printf("���i ==> ");
    scanf("%d", &kakaku);
    
    riritu = (double)(kakaku - genka) / kakaku * 100;
    printf("���v����%.1f%%�ł��B\n", riritu);

    return 0;
}