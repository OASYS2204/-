/* ------------------------------------------------------------ */
/* C���ꑍ�������v���O����										*/
/*																*/
/*		�ԍ��F__												*/
/*																*/
/*		�����F______________________________					*/
/* ------------------------------------------------------------ */
#include <stdio.h>
#include <string.h>

#include "jinko_define.h"		/* ���[�U��`�̃w�b�_�t�@�C��	*/

#define POINTER 0				/* �|�C���^�[��i�߂�Version �� */
								/* �L���ɂ���					*/
/* ------------------------------------------------------------ */
/* Function : main()											*/
/* Input    : �Ȃ�												*/
/* Return   : ��� 0											*/
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

	system("cls");				/* ��ʃN���A						*/
	printf("*** 00 �n�`�V�X�e���J���� �b���ꑍ�������v���O���� �͂��� ***\n");

	menu_no = menu();
	switch (menu_no) {
#if !POINTER
	case MENU_ALL:				/* ���ׂẴ����N				*/
		calc_population(data, datacnt);
		sort_data(menu_no, data, datacnt);
		disp_data(MENU_ALL, data,datacnt);
		break;
	case MENU_SORT_A:			/* �����Ƀ\�[�g					*/
		calc_population(data, datacnt);
		sort_data(menu_no, data, datacnt);
		disp_data(MENU_SORT_A, data,datacnt);
		break;
	case MENU_SORT_D:			/* �~���Ƀ\�[�g					*/
		calc_population(data, datacnt);
		sort_data(menu_no, data, datacnt);
		disp_data(MENU_SORT_D, data,datacnt);
		break;
	case MENU_SORT_P:			/* ���ׂĂ��y�[�W�ɕ���			*/
		calc_population(data, datacnt);
		sort_data(menu_no, data, datacnt);
		disp_data(MENU_SORT_P, data,datacnt);
		break;
#else
	case MENU_ALL:				/* ���ׂẴ����N				*/
	case MENU_SORT_A:			/* �����Ƀ\�[�g					*/
	case MENU_SORT_D:			/* �~���Ƀ\�[�g					*/
	case MENU_SORT_P:			/* ���ׂĂ��y�[�W�ɕ���			*/
		calc_population(data, datacnt);
		sort_data(menu_no, data, datacnt);
		disp_data(MENU_ALL, data,datacnt);
		break;
#endif	
	default:
		printf("���j���[�ԍ����Ⴂ�܂�\n");
		break;
	}
	printf("\n*** 00 �n�`�V�X�e���J���� �b���ꑍ�������v���O���� ����� ***\n");
	return 0;
}

/* ------------------------------------------------------------ */
/* Function : menu()											*/
/* Input    : �Ȃ�												*/
/* Return   : ����I�� : ���j���[�R�[�h							*/
/*			:	"0" -> 0				 						*/
/*			:	"A" -> 1										*/
/*			:	"D" -> 2										*/
/*			:	"P" -> 3										*/
/*			: �ُ�I�� : -1										*/
/* ------------------------------------------------------------ */
int menu(void)
{
	char menu_input[512];
	size_t len;
	int ret;

	printf("\n");
	printf("*** �s���{�� ���\�����j���[ ***\n");
	printf("\n");
	printf("0 : ���ׂ�\n");
	printf("A : ����\n");
	printf("D : �~��\n");
	printf("P : �y�[�W����\n");
	printf("�I�� ==> ");

	fgets(menu_input, 512, stdin);		/* �Ǝ㐫�΍�	*/
	len = strlen(menu_input);
	if (len == 2) {						/* CR-LF �܂Ŋl��	*/
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
/* Input    : jdata : �f�[�^�ǂݍ��ݗp�\���̔z��̃A�h���X		*/
/*			: dcnt  : �f�[�^�ǂݍ��݌����i�s���j				*/
/* Return   : �Ȃ�												*/
/* ------------------------------------------------------------ */
void calc_population(JINKO_DATA *jdata, int dcnt)
{
#if POINTER		// --- �|�C���^��i�߂�Version ---
	JINKO_DATA *p;
	
	for (p = jdata; p < jdata + dcnt; p++) {
		p->population = p->man + p->woman;
	}
#else			// --- �J�E���^�ŏ�������Version ---
	int i;
	
	for (i = 0; i < dcnt; i++, jdata++) {
		jdata->population = jdata->man + jdata->woman;
	}
#endif
	return;
}
/* ------------------------------------------------------------ */
/* Function : sort_data											*/
/* Input    : order ; ���בւ���								*/
/*			: jdata ; �f�[�^�ǂݍ��ݗp�\���̔z��̃A�h���X		*/
/*			: dcnt  ; �f�[�^�ǂݍ��݌����i�s���j				*/
/* Return   : �Ȃ�												*/
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
/* Input    : jdata ; �f�[�^�ǂݍ��ݗp�\���̔z��̃A�h���X		*/
/*			: dcnt  ; �f�[�^�ǂݍ��݌����i�s���j				*/
/* Return   : �Ȃ�												*/
/* ------------------------------------------------------------ */
void disp_data(int mode, JINKO_DATA *jdata, int dcnt)
{
	int i;

#if POINTER		// --- �|�C���^��i�߂�Version ---
	JINKO_DATA *p;

	printf("*** ���׃f�[�^ ***\n");				/* �^�C�g��						*/

	/* --- ���׍s�\�� --- */
	printf("�R�[�h  �s���{����  �ʐ�(����km)  ���l��(��l)  �l��(�j)  �l��(��)\n");

	for (p = jdata, i = 1; p < jdata + dcnt; p++, i++) {
		printf("%6s  %-10s  %12.2f  %12d  %8d  %8d\n",
				p->code, p->name, 
						p->area, p->population,
								p->man, p->woman);
#else			// --- �J�E���^�ŏ�������Version ---

	printf("*** ���׃f�[�^ ***\n");				/* �^�C�g��						*/

	/* --- ���׍s�\�� --- */
	printf("�R�[�h  �s���{����  �ʐ�(����km)  ���l��(��l)  �l��(�j)  �l��(��)\n");
	for (i = 1; i <= dcnt; i++) {
		printf("%6s  %-10s  %12.2f  %12d  %8d  %8d\n",
				(jdata + i - 1)->code, (jdata + i - 1)->name, 
						(jdata + i - 1)->area, (jdata + i - 1)->population,
								(jdata + i - 1)->man, (jdata + i - 1)->woman);
#endif
		if ((mode == MENU_SORT_P) && (i % LINE_PAR_PAGE == 0)) {
											/* �w�茏���\��������			*/
			printf("Enter�L�[�������Ă������� ");
			(void)getchar();
		}
	}
	return;
}
