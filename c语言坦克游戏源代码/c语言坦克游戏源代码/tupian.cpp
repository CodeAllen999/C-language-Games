# include "tanke.h"

////////////////////////////////////////////////’œ∞≠ŒÔ
void LaoWang(int * tilex, int * tiley)
{
	IMAGE img;
	loadimage(&img, _T("res\\tile.bmp"));
	
	putimage(*tilex, *tiley, 32 , 32 , &img, 32 * 5, 0 );
	
}
void tileHong(int * tilex, int * tiley)
{
	IMAGE img;
	loadimage(&img, _T("res\\tile.bmp"));
	
	putimage(*tilex, *tiley, 32, 32, &img, 32 * 0,  0 );
	
	return;
	
}

void tileLv(int * tilex, int * tiley)
{
	IMAGE img;
	loadimage(&img, _T("res\\tile.bmp"));
	
	putimage(*tilex, *tiley, 32, 32, &img, 32 * 2, 0 );
	return;
}

void tileBai(int * tilex, int * tiley)
{
	IMAGE img;
	loadimage(&img, _T("res\\tile.bmp"));
	
	putimage(*tilex, *tiley, 32, 32, &img, 32 * 1, 0 );
	return;
}

void tileBlue(int *tilex, int *tiley)
{
	IMAGE img;
	loadimage(&img, _T("res\\tile.bmp"));
	
	putimage(*tilex, *tiley, 32, 32, &img, 32 * 3, 0 );
}
//////////////////////////////////////////////////ŒÔ∆∑
void FaZhang(int *wupinx, int *wupiny)
{
	IMAGE img;
	loadimage(&img, _T("res\\fazhang.jpg"));
	
	putimage(*wupinx, *wupiny, 24, 24, &img, 0, 0 );
}

void ShouQiang(int *wupinx, int *wupiny)
{
	IMAGE img;
	loadimage(&img, _T("res\\shouqiang.jpg"));
	
	putimage(*wupinx, *wupiny, 24, 24, &img, 0, 0 );
}

void ShangDian(int *wupinx, int *wupiny)
{
	IMAGE img;
	loadimage(&img,_T("res\\shangdian.jpg"));
	
	putimage(*wupinx, *wupiny, 32, 32, &img, 0, 0 );
}

void YaoShui(int *wupinx, int *wupiny)
{
	IMAGE img;
	loadimage(&img, _T("res\\yaoshui.jpg"));

	putimage(*wupinx, *wupiny, 28, 28, &img, 0, 0 );
}

void DunPai(int *wupinx, int *wupiny)
{
	IMAGE img;
	loadimage(&img, _T("res\\dunpai.jpg"));
	
	putimage(*wupinx, *wupiny, 28, 28, &img, 0, 0 );
}

void XieZi(int *wupinx, int *wupiny)
{
	IMAGE img;
	loadimage(&img, _T("res\\xiezi.jpg"));
	
	putimage(*wupinx, *wupiny, 28, 28, &img, 0, 0 );
}

void Boss(int *wupinx, int *wupiny)
{
	IMAGE img;
	loadimage(&img, _T("res\\boss.jpg"));
	
	putimage(*wupinx, *wupiny, 32, 32, &img, 0, 0 );
}

void BigBoss(int *wupinx, int *wupiny)
{
	IMAGE img;
	loadimage(&img, _T("res\\bigboss.jpg"));

	putimage(*wupinx, *wupiny, 32, 32, &img, 0, 0 );
}