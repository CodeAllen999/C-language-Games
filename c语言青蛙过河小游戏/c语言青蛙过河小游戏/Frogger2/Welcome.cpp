#include "stdafx.h"

int initWelcome(ImageType *img)
{
	putimage(0,0,&(img->welcome));
	
	while(!_kbhit())
	{
		Sleep(TICK);
	}
	char key=_getch();
	if(27==key){return 0;}
	else{return 1;}
}