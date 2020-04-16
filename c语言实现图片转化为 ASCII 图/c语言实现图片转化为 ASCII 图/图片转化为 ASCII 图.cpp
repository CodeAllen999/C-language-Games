/* ����ѧȥ����վ�ռ� http://www.zixue7.com */

#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

/***********************�궨��***********************/
#define ASC_HEIGHT 8
#define ASC_WIDTH 8
#define ASCII_NUM 32

/*********************�ṹ�嶨��*********************/
struct ascii
{
	char asc[ASCII_NUM];
	int gray[ASCII_NUM];
}as = {' ', '`', '.', '^', ',', ':', '~', '"', '<', '!', 'c', 't', '+', '{', 'i', '7', '?',
		'u', '3', '0', 'p', 'w', '4', 'A', '8', 'D', 'X', '%', '#', 'H', 'W', 'M',
		0, 5, 7, 9, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43,
		45, 47, 49, 51, 53, 55, 59, 61, 63, 66, 68, 70};

/**********************��������***********************/
char SearchAsc(struct ascii as, int gray);
void Pic2Asc(struct ascii as, char filename[]);

/***********************������***********************/
int main(void)
{
	char filename[256];

	system("title, ͼƬת��ΪASCIIͼ��demo");

	printf("�������ļ���(����չ��)\n\n");
	gets(filename);
	system("cls");
	Pic2Asc(as, filename);

	printf("ת����ɣ�������˳�\n\n");
	system("pause");

	return 0;
}

/***********************������***********************/

//ͼƬת��ΪASCII���󣬲����浽txt��html�ļ���
void Pic2Asc(struct ascii as, char filename[])
{
	int height, width, gray;
	IMAGE img;
	FILE *fpAscPicText;

	//ͼ���豸��ʼ��
	loadimage(&img, filename);
	SetWorkingImage(&img);

	height = getheight() / ASC_HEIGHT;
	width = getwidth() / ASC_WIDTH;

	if((fpAscPicText = fopen("ASC_PIC.txt", "w")) == NULL)
	{
		printf("�ļ���ʧ��\n");
		exit(0);
	}

	//��ʼת����������
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			gray = 0;

			//ɨ��ÿһС��ĻҶȣ��������ƽ���Ҷ�
			for(int h = 0; h < ASC_HEIGHT; h++)
				for(int w = 0; w < ASC_WIDTH; w++)
				{
					gray += GetRValue(RGBtoGRAY(getpixel(j * ASC_WIDTH + w, i * ASC_HEIGHT + h))); 
				}
			gray /= (ASC_HEIGHT * ASC_WIDTH);
			gray = (255- gray) * 90 / 255; 
			
			fputc(SearchAsc(as, gray), fpAscPicText);
		}
		fputc('\n', fpAscPicText);
	}
	fclose(fpAscPicText);
}

//���ַ�����ASCII�ַ����͵Ͳ��͸�
char SearchAsc(struct ascii as, int gray)
{
	int lower = 0;
	int higher = ASCII_NUM;
	int mid;

	if(gray <= as.gray[0])
	{
		return as.asc[0];
	}
	else if (gray >= as.gray[ASCII_NUM - 1])
	{
		return as.asc[ASCII_NUM - 1];
	}
	else
	{
		while((higher - lower) > 1)
		{
			mid = (lower + higher) >> 1;
			if(gray > as.gray[mid])
			{
				lower = mid;
			}
			else
			{
				higher = mid;
			}
		}
		return as.asc[lower];
	}
}