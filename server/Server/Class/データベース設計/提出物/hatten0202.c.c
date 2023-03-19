#include<stdio.h>
int main(void)
{
    int genka, kakaku;
    double riritu;

    printf("Œ´‰¿ ==> ");
    scanf("%d", &genka);
    printf("‰¿Ši ==> ");
    scanf("%d", &kakaku);
    
    riritu = (double)(kakaku - genka) / kakaku * 100;
    printf("—˜‰v—¦‚Í%.1f%%‚Å‚·B\n", riritu);

    return 0;
}