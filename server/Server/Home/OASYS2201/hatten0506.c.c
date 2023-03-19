#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void main(void)
{   
    int random[9][9];
    int muki, i, j;
    srand(time(0));
    printf(" | 1| 2| 3| 4| 5| 6| 7| 8| 9|\n");
    printf("-+--+--+--+--+--+--+--+--+--+\n");
    for(i=0; i<9; i++){
        printf("%d|", i+1);
        for(j=0; j<9; j++){
            random[i][j] = rand() % 10;     
            printf("%2d|", random[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("行 ==> ");
    scanf("%d", &i);
    printf("列 ==> ");
    scanf("%d", &j);
    printf("向き[1:右 2:下]  ");
    scanf("%d", &muki);
    if(muki == 2){
        if(i>0 && i<7){
            printf("暗証番号は%d%d%d%dです。\n", random[i-1][j-1], random[i][j-1], random[i+1][j-1], random[i+2][j-1]);
        }else if(i>=7 && i<10){
            switch(i){
                case 7:
                    printf("暗証番号は%d%d%d%dです。\n", random[6][j-1], random[7][j-1], random[8][j-1], random[0][j-1]);
                    break;
                case 8:
                    printf("暗証番号は%d%d%d%dです。\n", random[7][j-1], random[8][j-1], random[0][j-1], random[1][j-1]);
                    break;
                case 9:
                    printf("暗証番号は%d%d%d%dです。\n", random[8][j-1], random[0][j-1], random[1][j-1], random[2][j-1]);
            }
        }else{
            printf("エラー:行と列は1以上9以下で入力してください。\n");
        }
    }else if(muki == 1){
        if(j>0 && j<7){
            printf("暗証番号は%d%d%d%dです。\n", random[i-1][j-1], random[i-1][j], random[i-1][j+1], random[i-1][j+2]);
        }else if(j>=7 && j<10){
            switch(j){
                case 7:
                    printf("暗証番号は%d%d%d%dです。\n", random[i-1][6], random[i-1][7], random[i-1][8], random[i-1][0]);
                    break;
                case 8:
                    printf("暗証番号は%d%d%d%dです。\n", random[i-1][7], random[i-1][8], random[i-1][0], random[i-1][1]);
                    break;
                case 9:
                    printf("暗証番号は%d%d%d%dです。\n", random[i-1][8], random[i-1][0], random[i-1][1], random[i-1][2]);
            }
        }else{
            printf("エラー:行と列は1以上9以下で入力してください。\n");
        }
    }else{
            printf("エラー:向きは1か2を入力してください。\n");
    }

}