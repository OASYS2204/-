/* ------------------------------------------------------------ */
/* C言語総合試験プログラム										*/
/*																*/
/*		番号：__												*/
/*																*/
/*		氏名：______________________________					*/
/* ------------------------------------------------------------ */
#include <stdio.h>
#include <string.h>

#include "jinko_define.h"		/* ユーザ定義のヘッダファイル	*/

#define POINTER 0				/* ポインターを進めるVersion を */
								/* 有効にする					*/
/* ------------------------------------------------------------ */
/* Function : main()											*/
/* Input    : なし												*/
/* Return   : 常に 0											*/
/* ------------------------------------------------------------ */
int main(void)
{
	int datacnt;
	int menu_no;

	JINKO_DATA data[MAX_DATACNT];

	int menu(void);
	int data_read(char *, JINKO_DATA *, size_t);
	void calc_population(JINKO_DATA *, int);
	void sort_data(int, JINKO_DATA *, int);
	void disp_data(int, JINKO_DATA *, int);
	
	
	datacnt = data_read("./data.txt", &data[0], sizeof(data)/sizeof(JINKO_DATA));

	system("cls");				/* 画面クリア						*/
	printf("*** 00 ＯＡシステム開発科 Ｃ言語総合試験プログラム はじめ ***\n");

	menu_no = menu();
	switch (menu_no) {
#if !POINTER
	case MENU_ALL:				/* すべてのランク				*/
		calc_population(data, datacnt);
		sort_data(menu_no, data, datacnt);
		disp_data(MENU_ALL, data,datacnt);
		break;
	case MENU_SORT_A:			/* 昇順にソート					*/
		calc_population(data, datacnt);
		sort_data(menu_no, data, datacnt);
		disp_data(MENU_SORT_A, data,datacnt);
		break;
	case MENU_SORT_D:			/* 降順にソート					*/
		calc_population(data, datacnt);
		sort_data(menu_no, data, datacnt);
		disp_data(MENU_SORT_D, data,datacnt);
		break;
	case MENU_SORT_P:			/* すべてをページに分割			*/
		calc_population(data, datacnt);
		sort_data(menu_no, data, datacnt);
		disp_data(MENU_SORT_P, data,datacnt);
		break;
#else
	case MENU_ALL:				/* すべてのランク				*/
	case MENU_SORT_A:			/* 昇順にソート					*/
	case MENU_SORT_D:			/* 降順にソート					*/
	case MENU_SORT_P:			/* すべてをページに分割			*/
		calc_population(data, datacnt);
		sort_data(menu_no, data, datacnt);
		disp_data(MENU_ALL, data,datacnt);
		break;
#endif	
	default:
		printf("メニュー番号が違います\n");
		break;
	}
	printf("\n*** 00 ＯＡシステム開発科 Ｃ言語総合試験プログラム おわり ***\n");
	return 0;
}

/* ------------------------------------------------------------ */
/* Function : menu()											*/
/* Input    : なし												*/
/* Return   : 正常終了 : メニューコード							*/
/*			:	"0" -> 0				 						*/
/*			:	"A" -> 1										*/
/*			:	"D" -> 2										*/
/*			:	"P" -> 3										*/
/*			: 異常終了 : -1										*/
/* ------------------------------------------------------------ */
int menu(void)
{
	char menu_input[512];
	size_t len;
	int ret;

	printf("\n");
	printf("*** 都道府県 情報表示メニュー ***\n");
	printf("\n");
	printf("0 : すべて\n");
	printf("A : 昇順\n");
	printf("D : 降順\n");
	printf("P : ページ分割\n");
	printf("選択 ==> ");

	fgets(menu_input, 512, stdin);		/* 脆弱性対策	*/
	len = strlen(menu_input);
	if (len == 2) {						/* CR-LF まで獲得	*/
		switch(menu_input[0]) {
		case '0':
			ret =  MENU_ALL;
			break;
		case 'A':
			ret =  MENU_SORT_A;
			break;
		case 'D':
			ret =  MENU_SORT_D;
			break;
		case 'P':
			ret =  MENU_SORT_P;
			break;
		default:
			ret = MENU_ILLIGAL;
			break;
		}
	} else {
		ret = MENU_ILLIGAL;
	}
	return ret;
}
/* ------------------------------------------------------------ */
/* Function : calc_population									*/
/* Input    : jdata : データ読み込み用構造体配列のアドレス		*/
/*			: dcnt  : データ読み込み件数（行数）				*/
/* Return   : なし												*/
/* ------------------------------------------------------------ */
void calc_population(JINKO_DATA *jdata, int dcnt)
{
#if POINTER		// --- ポインタを進めるVersion ---
	JINKO_DATA *p;
	
	for (p = jdata; p < jdata + dcnt; p++) {
		p->population = p->man + p->woman;
	}
#else			// --- カウンタで処理するVersion ---
	int i;
	
	for (i = 0; i < dcnt; i++, jdata++) {
		jdata->population = jdata->man + jdata->woman;
	}
#endif
	return;
}
/* ------------------------------------------------------------ */
/* Function : sort_data											*/
/* Input    : order ; 並べ替え順								*/
/*			: jdata ; データ読み込み用構造体配列のアドレス		*/
/*			: dcnt  ; データ読み込み件数（行数）				*/
/* Return   : なし												*/
/* ------------------------------------------------------------ */
void sort_data(int order, JINKO_DATA *jdata, int dcnt)
{
	int i;
	int j;
	JINKO_DATA temp;
	
	for (i = 0; i < dcnt -1; i++) {
		for (j = i + 1; j < dcnt; j++) {
			switch (order) {
			case MENU_ALL:
				if ((jdata + i)->code > (jdata + j)->code) {
					temp = *(jdata + i);
					*(jdata + i) =*(jdata + j);
					*(jdata + j) = temp;
				}
				break;
			case MENU_SORT_A:
				if ((jdata + i)->area > (jdata + j)->area) {
					temp = *(jdata + i);
					*(jdata + i) =*(jdata + j);
					*(jdata + j) = temp;
				}
				break;
			case MENU_SORT_D:
				if ((jdata + i)->area < (jdata + j)->area) {
					temp = *(jdata + i);
					*(jdata + i) =*(jdata + j);
					*(jdata + j) = temp;
				}
				break;
			case MENU_SORT_P:
				if ((jdata + i)->population < (jdata + j)->population) {
					temp = *(jdata + i);
					*(jdata + i) =*(jdata + j);
					*(jdata + j) = temp;
				}
				break;
			default:
				break;
			}
		}
	}
	return;
}

/* ------------------------------------------------------------ */
/* Function : disp_data											*/
/* Input    : jdata ; データ読み込み用構造体配列のアドレス		*/
/*			: dcnt  ; データ読み込み件数（行数）				*/
/* Return   : なし												*/
/* ------------------------------------------------------------ */
void disp_data(int mode, JINKO_DATA *jdata, int dcnt)
{
	int i;

#if POINTER		// --- ポインタを進めるVersion ---
	JINKO_DATA *p;

	printf("*** 明細データ ***\n");				/* タイトル						*/

	/* --- 明細行表示 --- */
	printf("コード  都道府県名  面積(平方km)  総人口(千人)  人口(男)  人口(女)\n");

	for (p = jdata, i = 1; p < jdata + dcnt; p++, i++) {
		printf("%6s  %-10s  %12.2f  %12d  %8d  %8d\n",
				p->code, p->name, 
						p->area, p->population,
								p->man, p->woman);
#else			// --- カウンタで処理するVersion ---

	printf("*** 明細データ ***\n");				/* タイトル						*/

	/* --- 明細行表示 --- */
	printf("コード  都道府県名  面積(平方km)  総人口(千人)  人口(男)  人口(女)\n");
	for (i = 1; i <= dcnt; i++) {
		printf("%6s  %-10s  %12.2f  %12d  %8d  %8d\n",
				(jdata + i - 1)->code, (jdata + i - 1)->name, 
						(jdata + i - 1)->area, (jdata + i - 1)->population,
								(jdata + i - 1)->man, (jdata + i - 1)->woman);
#endif
		if ((mode == MENU_SORT_P) && (i % LINE_PAR_PAGE == 0)) {
											/* 指定件数表示したか			*/
			printf("Enterキーを押してください ");
			(void)getchar();
		}
	}
	return;
}
