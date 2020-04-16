# include "tanke.h"
/////////////////////////////////////////控制
void JFangXiang(int (*x)[2][3], int * x_, int * y_,  int * z,pBaiZhuan pbaizhuan,pHongZhuan phongzhuan, int *ydsd)
{
	if (GetAsyncKeyState('W') && GetAsyncKeyState('A') )
		return ;
	if (GetAsyncKeyState('W') && GetAsyncKeyState('D') )
		return ;
	if (GetAsyncKeyState('S') && GetAsyncKeyState('A') )
		return ;
	if (GetAsyncKeyState('S') && GetAsyncKeyState('D') )
		return ;

	if (GetAsyncKeyState('W') && *y_ > 0 && !( 
												(*y_ <= pbaizhuan[0].y +32 && *y_ >= pbaizhuan[0].y + 28 && *x_ + 28 >= pbaizhuan[0].x && *x_ <= pbaizhuan[0].x + 32)||
												(*y_ <= pbaizhuan[1].y +32 && *y_ >= pbaizhuan[1].y + 28 && *x_ + 28 >= pbaizhuan[1].x && *x_ <= pbaizhuan[1].x + 32)||
												(*y_ <= pbaizhuan[2].y +32 && *y_ >= pbaizhuan[2].y + 28 && *x_ + 28 >= pbaizhuan[2].x && *x_ <= pbaizhuan[2].x + 32) )
										 && !(  (*y_ <= phongzhuan[0].y +32 && *y_ >= phongzhuan[0].y + 28 && *x_ + 28 >= phongzhuan[0].x && *x_ <= phongzhuan[0].x + 32)||
												(*y_ <= phongzhuan[1].y +32 && *y_ >= phongzhuan[1].y + 28 && *x_ + 28 >= phongzhuan[1].x && *x_ <= phongzhuan[1].x + 32) )
												)
	{
		*y_ -= *ydsd;	
		x[*z + 1][0][1] = 0;//x坐标中的方向
		x[*z + 1][0][2] = -1;

	}
	if (GetAsyncKeyState('S') && *y_ + 28 < 480 && !(
														(*y_ + 28>= pbaizhuan[0].y  && *y_ + 28<= pbaizhuan[0].y + 4 && *x_ + 28 >= pbaizhuan[0].x && *x_ <= pbaizhuan[0].x + 32)||
														(*y_ + 28>= pbaizhuan[1].y  && *y_ + 28<= pbaizhuan[1].y + 4 && *x_ + 28 >= pbaizhuan[1].x && *x_ <= pbaizhuan[1].x + 32)||
														(*y_ + 28>= pbaizhuan[2].y  && *y_ + 28<= pbaizhuan[2].y + 4 && *x_ + 28 >= pbaizhuan[2].x && *x_ <= pbaizhuan[2].x + 32) )
												&& !(	(*y_ + 28>= phongzhuan[0].y  && *y_ + 28<= phongzhuan[0].y + 4 && *x_ + 28 >= phongzhuan[0].x && *x_ <= phongzhuan[0].x + 32)||
														(*y_ + 28>= phongzhuan[1].y  && *y_ + 28<= phongzhuan[1].y + 4 && *x_ + 28 >= phongzhuan[1].x && *x_ <= phongzhuan[1].x + 32) )
														)
	{		
		*y_ += *ydsd;
		x[*z + 1][0][1] = 0;
		x[*z + 1][0][2] = 1;

	}
	if (GetAsyncKeyState('A') && *x_ > 0 && !(
												(*x_ <= pbaizhuan[0].x +32 && *x_ >= pbaizhuan[0].x + 28 && *y_ <= pbaizhuan[0].y +32 && *y_ + 28 >= pbaizhuan[0].y )||
												(*x_ <= pbaizhuan[1].x +32 && *x_ >= pbaizhuan[1].x + 28 && *y_ <= pbaizhuan[1].y +32 && *y_ + 28 >= pbaizhuan[1].y )||
												(*x_ <= pbaizhuan[2].x +32 && *x_ >= pbaizhuan[2].x + 28 && *y_ <= pbaizhuan[2].y +32 && *y_ + 28 >= pbaizhuan[2].y ) )
										 && !(	(*x_ <= phongzhuan[0].x +32 && *x_ >= phongzhuan[0].x + 28 && *y_ <= phongzhuan[0].y +32 && *y_ + 28 >= phongzhuan[0].y )||
												(*x_ <= phongzhuan[1].x +32 && *x_ >= phongzhuan[1].x + 28 && *y_ <= phongzhuan[1].y +32 && *y_ + 28 >= phongzhuan[1].y ) )
												)
	{
		*x_ -= *ydsd;
		x[*z + 1][0][1] = -1;
		x[*z + 1][0][2] = 0;

	}
	if (GetAsyncKeyState('D') && *x_ + 28 < 640 && !(
														(*x_ + 28 >= pbaizhuan[0].x && *x_ + 28 <= pbaizhuan[0].x + 4 && *y_ <= pbaizhuan[0].y +32 && *y_ + 28 >= pbaizhuan[0].y )||
														(*x_ + 28 >= pbaizhuan[1].x && *x_ + 28 <= pbaizhuan[1].x + 4 && *y_ <= pbaizhuan[1].y +32 && *y_ + 28 >= pbaizhuan[1].y )||
														(*x_ + 28 >= pbaizhuan[2].x && *x_ + 28 <= pbaizhuan[2].x + 4 && *y_ <= pbaizhuan[2].y +32 && *y_ + 28 >= pbaizhuan[2].y ) )
												&& !(	(*x_ + 28 >= phongzhuan[0].x && *x_ + 28 <= phongzhuan[0].x + 4 && *y_ <= phongzhuan[0].y +32 && *y_ + 28 >= phongzhuan[0].y )||
														(*x_ + 28 >= phongzhuan[1].x && *x_ + 28 <= phongzhuan[1].x + 4 && *y_ <= phongzhuan[1].y +32 && *y_ + 28 >= phongzhuan[1].y ) )
														)
	{
		*x_ += *ydsd;
		x[*z + 1][0][1] = 1;
		x[*z + 1][0][2] = 0;

	}
	return ;
}

void DFangXiang(int (*x)[2][3], int * x_, int * y_,  int * z,int *r)
{
	int i;
	i = rand() % 10 ;//随机方向 ，也许下次循环在原地
	if( (*r) % 50 ==0)//不是每循环一次就有个动作
	{
		if ( i == 0 && *y_ > 0)
		{
			*y_ -= 13;	
			x[*z + 1][0][1] = 0;
			x[*z + 1][0][2] = -1;
	
		}
		if ((i == 1 || i==4 || i ==5 ) && *y_ + 28 < 480)//往下走概率变大
		{		
			*y_ += 13;
			x[*z + 1][0][1] = 0;
			x[*z + 1][0][2] = 1;
		
		}
		if (i == 2 && *x_ > 0)
		{
			*x_ -= 13;
			x[*z + 1][0][1] = -1;
			x[*z + 1][0][2] = 0;
		
		}
		if (i == 3 && *x_ + 28 < 640)
		{
			*x_ += 13;
			x[*z + 1][0][1] = 1;
			x[*z + 1][0][2] = 0;
		
		}
	}
	return ;
}

void BossFangXiang(int (*x)[2][3], int * x_, int * y_,  int * z, int *r, int *o)
{
	if( (*r) % 5 ==0)
		*o = rand() % 10;
	
	if ( *o == 0 && *y_ > 0)
	{
		*y_ -= 10;	
		x[*z + 1][0][1] = 0;
		x[*z + 1][0][2] = -1;

	}
	if ((*o == 1) && *y_ + 28 < 480)//往下走概率变大
	{		
		*y_ += 10;
		x[*z + 1][0][1] = 0;
		x[*z + 1][0][2] = 1;

	}
	if (*o == 2 && *x_ > 0)
	{
		*x_ -= 10;
		x[*z + 1][0][1] = -1;
		x[*z + 1][0][2] = 0;
	
	}
	if (*o == 3 && *x_ + 28 < 640)
	{
		*x_ += 10;
		x[*z + 1][0][1] = 1;
		x[*z + 1][0][2] = 0;
	}
	
	return ;
}

void FeiJiFangXiang(int * x_, int * y_,int *r,int *o)
{
	
	if( (*r) % 10 ==0)
		*o = rand() % 15;
	
	if (( *o == 0 || *o == 8 || *o == 9) && *y_ > 0)
		(*y_) -= 5;	
	
	if ((*o == 1) && *y_ + 65 < 280)		
		(*y_) += 5;
	
	if (*o == 2 && *x_ > 100)
		(*x_) -= 10;
	
	if (*o == 3 && *x_ + 65 < 540)
		(*x_) += 10;
	
	if (*o == 4 && *x_ + 65 < 540 && *y_ + 65 < 280)//
	{
		(*x_) += 10;
		(*y_) += 10;
	}
	
	if (*o == 5 && *x_ > 100 && *y_ + 65 < 280)// /
	{
		(*x_) -= 10;
		(*y_) += 10;
	}
	
	if (*o == 6 && *x_ > 100 && *y_ > 0)
	{
		(*x_) -= 10;
		(*y_) -= 10;
	}
	
	if (*o == 7 && *x_ + 65 < 540 && *y_ > 0)// /
	{
		(*x_) += 10;
		(*y_) -= 10;
	}	
	return ;
}