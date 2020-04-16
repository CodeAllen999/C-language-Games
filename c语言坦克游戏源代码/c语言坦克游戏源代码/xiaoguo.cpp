# include "tanke.h"

bool LuoShui( int * x_, int * y_, int * tileBlue_x, int *tileBlue_y, int *d,int *gold)
{
	IMAGE imgBoom;
	loadimage(&imgBoom,_T("res\\explode1.bmp"));
	if (*x_ + 14 <= *tileBlue_x + 32 && *x_ + 14 >= *tileBlue_x && *y_ + 14 <= *tileBlue_y + 32 && *y_ + 14 >= *tileBlue_y)
	{
		putimage(*x_, *y_, 28, 28, &imgBoom,0 ,0 );
		(*d)++;
		*gold -= 2; 
	
		if (*d >= 40)
		{
			*d = 0;
			return false;
		}
	}
	return true;
}

bool BossMiaoRen(int *y_,int *y9)
{

	if (*y_ <= *y9 + 67)
	{
		mciSendString("open sound//boom.mp3 alias mymusic_1", NULL, 0, NULL);
		mciSendString("play mymusic_1", NULL, 0, NULL);
		return false;
	}
	return true;
}


bool HuoWu(int *x_, int *y_, int *wupinx, int *wupiny, int *d, int *HWsd)
{
	IMAGE imgXing;
	loadimage(&imgXing, _T("res\\bore.bmp"));
	if (*x_ + 14 <= *wupinx + 32 && *x_ + 14 >= *wupinx && *y_ + 14 <= *wupiny + 32 && *y_ + 14 >= *wupiny)
	{
		putimage(*x_ - 4, *y_ - 4, 32, 32, &imgXing, 32 * 3 ,0 );
		(*d)++;

		if (*d >= *HWsd)
		{
			if (*HWsd != 0)
				printf("\a");
			*d = 0;
			return false;
		}
	}
	return true;
}