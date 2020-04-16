# include "tanke.h"

/////////////////////////////////////////////////////主函数程序
void ZhengTiLaoWang(pTanKe ptanke,int (*x_8)[2][3],int (*x_9)[2][3],int (*x_10)[2][3],int (*x_11)[2][3],
					bool *exist_laowang,bool *exist1, int*gold, int*d,int*tilelaowang_x,int*tilelaowang_y,
					int *tileHong_x1,int *tileHong_y1,int *tileBai_x4,int *tileBai_y4,bool*live9)
{	
	if(*exist_laowang) LaoWang(&(*tilelaowang_x), &(*tilelaowang_y));//老王
	if(*exist_laowang) *exist_laowang = DBoomBig(ptanke[0].d, &(*tilelaowang_x), &(*tilelaowang_y), &(*d));//老王被打爆
	if(*exist_laowang) *exist_laowang = DBoomBig(ptanke[1].d, &(*tilelaowang_x), &(*tilelaowang_y), &(*d));//老王被打爆
	if(*exist_laowang) *exist_laowang = DBoomBig(ptanke[2].d, &(*tilelaowang_x), &(*tilelaowang_y), &(*d));//老王被打爆
	if(*exist_laowang) *exist_laowang = DBoomBig(ptanke[3].d, &(*tilelaowang_x), &(*tilelaowang_y), &(*d));//老王被打爆
	if(*exist_laowang) *exist_laowang = DBoomBig(ptanke[4].d, &(*tilelaowang_x), &(*tilelaowang_y), &(*d));//老王被打爆
	if(*exist_laowang) *exist_laowang = DBoomBig(ptanke[5].d, &(*tilelaowang_x), &(*tilelaowang_y), &(*d));//老王被打爆
	if(*exist_laowang) *exist_laowang = DBoomBig(ptanke[6].d, &(*tilelaowang_x), &(*tilelaowang_y), &(*d));//老王被打爆
	if(*exist_laowang) *exist_laowang = DBoomBig(x_8, &(*tilelaowang_x), &(*tilelaowang_y), &(*d));//老王被打爆
	
	if(*exist1) tileHong(&(*tileHong_x1), &(*tileHong_y1));//红色障碍物
	if(*exist1) *exist1 = DBoomBig(ptanke[0].d, &(*tileHong_x1), &(*tileHong_y1), &(*d));//红色障碍物被打爆
	if(*exist1) *exist1 = DBoomBig(ptanke[1].d, &(*tileHong_x1), &(*tileHong_y1), &(*d));//红色障碍物被打爆
	if(*exist1) *exist1 = DBoomBig(ptanke[2].d, &(*tileHong_x1), &(*tileHong_y1), &(*d));//红色障碍物被打爆
	if(*exist1) *exist1 = DBoomBig(ptanke[3].d, &(*tileHong_x1), &(*tileHong_y1), &(*d));//红色障碍物被打爆
	if(*exist1) *exist1 = DBoomBig(ptanke[4].d, &(*tileHong_x1), &(*tileHong_y1), &(*d));//红色障碍物被打爆
	if(*exist1) *exist1 = DBoomBig(ptanke[5].d, &(*tileHong_x1), &(*tileHong_y1), &(*d));//红色障碍物被打爆
	if(*exist1) *exist1 = DBoomBig(ptanke[6].d, &(*tileHong_x1), &(*tileHong_y1), &(*d));//红色障碍物被打爆
	if(*exist1) *exist1 = DBoomBig(x_8, &(*tileHong_x1), &(*tileHong_y1), &(*d));//红色障碍物被打爆
	
	if(*gold >100 && !(*live9))
	{
		*tileBai_x4 = 304;
		*tileBai_y4 = 416;
		tileBai(&*tileBai_x4, &*tileBai_y4);//！！
	}
	if (!*live9)QZBoom(ptanke[0].d, &(*tileBai_x4), &(*tileBai_y4));//白色障碍物被打
	if (!*live9)QZBoom(ptanke[1].d, &(*tileBai_x4), &(*tileBai_y4));//白色障碍物被打
	if (!*live9)QZBoom(ptanke[2].d, &(*tileBai_x4), &(*tileBai_y4));//白色障碍物被打
	if (!*live9)QZBoom(ptanke[3].d, &(*tileBai_x4), &(*tileBai_y4));//白色障碍物被打
	if (!*live9)QZBoom(ptanke[4].d, &(*tileBai_x4), &(*tileBai_y4));//白色障碍物被打
	if (!*live9)QZBoom(ptanke[5].d, &(*tileBai_x4), &(*tileBai_y4));//白色障碍物被打
	if (!*live9)QZBoom(ptanke[6].d, &(*tileBai_x4), &(*tileBai_y4));//白色障碍物被打
	if (!*live9)QZBoom(x_8, &(*tileBai_x4), &(*tileBai_y4));//白色障碍物被打
	if (!*live9)QZBoom(x_9, &(*tileBai_x4), &(*tileBai_y4));//白色障碍物被打
	if (!*live9)QZBoom(x_10, &(*tileBai_x4), &(*tileBai_y4));//白色障碍物被打
	if (!*live9)QZBoom(x_11, &(*tileBai_x4), &(*tileBai_y4));//白色障碍物被打
	
	return;
}

void ZhengTiFangXiang(pTanKe ptanke, pBaiZhuan pbaizhuan, pHongZhuan phongzhuan,int (*x_8)[2][3],
					  bool *live8,bool *live9,
					  int*r,int*x8,int*y8,int*x9,int*y9,
					  int *z8,
					  int *o,int *ydsd)
{
	(*r)++;
	if(ptanke[0].live) JFangXiang(ptanke[0].d, &ptanke[0].x,&ptanke[0].y, &ptanke[0].z,pbaizhuan,phongzhuan,&*ydsd);
	if(ptanke[1].live) DFangXiang(ptanke[1].d, &ptanke[1].x,&ptanke[1].y, &ptanke[1].z,&*r);
	if(ptanke[2].live) DFangXiang(ptanke[2].d, &ptanke[2].x,&ptanke[2].y, &ptanke[2].z,&*r);
	if(ptanke[3].live) DFangXiang(ptanke[3].d, &ptanke[3].x,&ptanke[3].y, &ptanke[3].z,&*r);
	if(ptanke[4].live) DFangXiang(ptanke[4].d, &ptanke[4].x,&ptanke[4].y, &ptanke[4].z,&*r);
	if(ptanke[5].live) DFangXiang(ptanke[5].d, &ptanke[5].x,&ptanke[5].y, &ptanke[5].z,&*r);
	if(ptanke[6].live) DFangXiang(ptanke[6].d, &ptanke[6].x,&ptanke[6].y, &ptanke[6].z,&*r);
	
	if(*live8) BossFangXiang(x_8, &*x8, &*y8, &*z8, &*r,&*o);
	if(*live9) FeiJiFangXiang(&*x9, &*y9, &*r,&*o);
	return;
}

void ZhengTiHongSeZhangAiWu(pTanKe ptanke,int (*x_8)[2][3],int (*x_9)[2][3],
							int*d,pHongZhuan phongzhuan)
{
	if(phongzhuan[0].exist) tileHong(&phongzhuan[0].x, &phongzhuan[0].y);//红色障碍物
	if(phongzhuan[0].exist) phongzhuan[0].exist = DBoomBig(ptanke[0].d, &phongzhuan[0].x, &phongzhuan[0].y, &*d);//红色障碍物被打爆
	if(phongzhuan[0].exist) phongzhuan[0].exist = DBoomBig(ptanke[1].d, &phongzhuan[0].x, &phongzhuan[0].y, &*d);//红色障碍物被打爆
	if(phongzhuan[0].exist) phongzhuan[0].exist = DBoomBig(ptanke[2].d, &phongzhuan[0].x, &phongzhuan[0].y, &*d);//红色障碍物被打爆
	if(phongzhuan[0].exist) phongzhuan[0].exist = DBoomBig(ptanke[3].d, &phongzhuan[0].x, &phongzhuan[0].y, &*d);//红色障碍物被打爆
	if(phongzhuan[0].exist) phongzhuan[0].exist = DBoomBig(ptanke[4].d, &phongzhuan[0].x, &phongzhuan[0].y, &*d);//红色障碍物被打爆
	if(phongzhuan[0].exist) phongzhuan[0].exist = DBoomBig(ptanke[5].d, &phongzhuan[0].x, &phongzhuan[0].y, &*d);//红色障碍物被打爆
	if(phongzhuan[0].exist) phongzhuan[0].exist = DBoomBig(ptanke[6].d, &phongzhuan[0].x, &phongzhuan[0].y, &*d);//红色障碍物被打爆
	if(phongzhuan[0].exist) phongzhuan[0].exist = DBoomBig(x_8, &phongzhuan[0].x, &phongzhuan[0].y, &*d);//红色障碍物被打爆
	if(phongzhuan[0].exist) phongzhuan[0].exist = DBoomBig(x_9, &phongzhuan[0].x, &phongzhuan[0].y, &*d);//红色障碍物被打爆
	
	if(phongzhuan[1].exist) tileHong(&phongzhuan[1].x, &phongzhuan[1].y);//红色障碍物
	if(phongzhuan[1].exist) phongzhuan[1].exist = DBoomBig(ptanke[0].d, &phongzhuan[1].x, &phongzhuan[1].y, &*d);//红色障碍物被打爆
	if(phongzhuan[1].exist) phongzhuan[1].exist = DBoomBig(ptanke[1].d, &phongzhuan[1].x, &phongzhuan[1].y, &*d);//红色障碍物被打爆
	if(phongzhuan[1].exist) phongzhuan[1].exist = DBoomBig(ptanke[2].d, &phongzhuan[1].x, &phongzhuan[1].y, &*d);//红色障碍物被打爆
	if(phongzhuan[1].exist) phongzhuan[1].exist = DBoomBig(ptanke[3].d, &phongzhuan[1].x, &phongzhuan[1].y, &*d);//红色障碍物被打爆
	if(phongzhuan[1].exist) phongzhuan[1].exist = DBoomBig(ptanke[4].d, &phongzhuan[1].x, &phongzhuan[1].y, &*d);//红色障碍物被打爆
	if(phongzhuan[1].exist) phongzhuan[1].exist = DBoomBig(ptanke[5].d, &phongzhuan[1].x, &phongzhuan[1].y, &*d);//红色障碍物被打爆
	if(phongzhuan[1].exist) phongzhuan[1].exist = DBoomBig(ptanke[6].d, &phongzhuan[1].x, &phongzhuan[1].y, &*d);//红色障碍物被打爆
	if(phongzhuan[1].exist) phongzhuan[1].exist = DBoomBig(x_8, &phongzhuan[1].x, &phongzhuan[1].y, &*d);//红色障碍物被打爆
	if(phongzhuan[1].exist) phongzhuan[1].exist = DBoomBig(x_9, &phongzhuan[1].x, &phongzhuan[1].y, &*d);//红色障碍物被打爆
		
	if(!(phongzhuan[0].exist)) {phongzhuan[0].x = -500;phongzhuan[0].y = -500;}
	if(!(phongzhuan[1].exist)) {phongzhuan[1].x = -500;phongzhuan[1].y = -500;}

	return;
}

void ZhengTiBaiSeZhangAiWu(pTanKe ptanke,int (*x_8)[2][3],int (*x_9)[2][3],int (*x_10)[2][3],int (*x_11)[2][3],
						   bool *wexist1,
						   int*d,pBaiZhuan pbaizhuan)
{
	if(*wexist1 || pbaizhuan[0].exist) tileBai(&pbaizhuan[0].x, &pbaizhuan[0].y);//白色砖块；
	if(*wexist1 || pbaizhuan[1].exist) tileBai(&pbaizhuan[1].x, &pbaizhuan[1].y);//白色砖块；
	if(*wexist1 || pbaizhuan[2].exist) tileBai(&pbaizhuan[2].x, &pbaizhuan[2].y);//白色砖块；
	if(pbaizhuan[0].exist)	pbaizhuan[0].exist = DBoomBig(ptanke[0].d, &pbaizhuan[0].x, &pbaizhuan[0].y, &*d);//白色障碍物被打
	DBoomBig(ptanke[1].d, &pbaizhuan[0].x, &pbaizhuan[0].y, &*d);
	DBoomBig(ptanke[2].d, &pbaizhuan[0].x, &pbaizhuan[0].y, &*d);
	DBoomBig(ptanke[3].d, &pbaizhuan[0].x, &pbaizhuan[0].y, &*d);
	DBoomBig(ptanke[4].d, &pbaizhuan[0].x, &pbaizhuan[0].y, &*d);
	DBoomBig(ptanke[5].d, &pbaizhuan[0].x, &pbaizhuan[0].y, &*d);
	DBoomBig(ptanke[6].d, &pbaizhuan[0].x, &pbaizhuan[0].y, &*d);
	DBoomBig(x_8, &pbaizhuan[0].x, &pbaizhuan[0].y, &*d);
	DBoomBig(x_9, &pbaizhuan[0].x, &pbaizhuan[0].y, &*d);
	DBoomBig(x_10, &pbaizhuan[0].x, &pbaizhuan[0].y, &*d);
	DBoomBig(x_11, &pbaizhuan[0].x, &pbaizhuan[0].y, &*d);	
	
	if(pbaizhuan[1].exist)	pbaizhuan[1].exist = DBoomBig(ptanke[0].d, &pbaizhuan[1].x, &pbaizhuan[1].y, &*d);//白色障碍物被打
	DBoomBig(ptanke[1].d, &pbaizhuan[1].x, &pbaizhuan[1].y, &*d);
	DBoomBig(ptanke[2].d, &pbaizhuan[1].x, &pbaizhuan[1].y, &*d);
	DBoomBig(ptanke[3].d, &pbaizhuan[1].x, &pbaizhuan[1].y, &*d);
	DBoomBig(ptanke[4].d, &pbaizhuan[1].x, &pbaizhuan[1].y, &*d);
	DBoomBig(ptanke[5].d, &pbaizhuan[1].x, &pbaizhuan[1].y, &*d);
	DBoomBig(ptanke[6].d, &pbaizhuan[1].x, &pbaizhuan[1].y, &*d);
	DBoomBig(x_8, &pbaizhuan[1].x, &pbaizhuan[1].y, &*d);
	DBoomBig(x_9, &pbaizhuan[1].x, &pbaizhuan[1].y, &*d);
	DBoomBig(x_10, &pbaizhuan[1].x, &pbaizhuan[1].y, &*d);
	DBoomBig(x_11, &pbaizhuan[1].x, &pbaizhuan[1].y, &*d);
	
	if(pbaizhuan[2].exist)	pbaizhuan[2].exist = DBoomBig(ptanke[0].d, &pbaizhuan[2].x, &pbaizhuan[2].y, &*d);//白色障碍物被打
	DBoomBig(ptanke[1].d, &pbaizhuan[2].x, &pbaizhuan[2].y, &*d);
	DBoomBig(ptanke[2].d, &pbaizhuan[2].x, &pbaizhuan[2].y, &*d);
	DBoomBig(ptanke[3].d, &pbaizhuan[2].x, &pbaizhuan[2].y, &*d);
	DBoomBig(ptanke[4].d, &pbaizhuan[2].x, &pbaizhuan[2].y, &*d);
	DBoomBig(ptanke[5].d, &pbaizhuan[2].x, &pbaizhuan[2].y, &*d);
	DBoomBig(ptanke[6].d, &pbaizhuan[2].x, &pbaizhuan[2].y, &*d);
	DBoomBig(x_8, &pbaizhuan[2].x, &pbaizhuan[2].y, &*d);
	DBoomBig(x_9, &pbaizhuan[2].x, &pbaizhuan[2].y, &*d);
	DBoomBig(x_10, &pbaizhuan[2].x, &pbaizhuan[2].y, &*d);
	DBoomBig(x_11, &pbaizhuan[2].x, &pbaizhuan[2].y, &*d);

	if( !(*wexist1 || pbaizhuan[0].exist) ) {pbaizhuan[0].x = -500;pbaizhuan[0].y= -500;}
	if( !(*wexist1 || pbaizhuan[1].exist) ) {pbaizhuan[1].x = -500;pbaizhuan[1].y= -500;}
	if( !(*wexist1 || pbaizhuan[2].exist) ) {pbaizhuan[2].x = -500;pbaizhuan[2].y= -500;}


	if(*wexist1){pbaizhuan[0].exist = true; pbaizhuan[1].exist = true; pbaizhuan[2].exist = true;}
	return;
	
}

void ZhengTiLanSeZhangAiWu(int *tileBlue_x1, int *tileBlue_y1,int *tileBlue_x2, int *tileBlue_y2)
{
	tileBlue(&*tileBlue_x1, &*tileBlue_y1);//蓝色砖块
	tileBlue(&*tileBlue_x2, &*tileBlue_y2);//蓝色砖块
	return;
}

void ZhengTiTanKeBaoZha(pTanKe ptanke,int (*x_8)[2][3],int (*x_9)[2][3],int (*x_10)[2][3],int (*x_11)[2][3],
						bool *live8,bool *live9,
						int*r,int*x8,int*y8,int*x9,int*y9,
						int *sd,int *color8,
						int *j,int*d,int*k,int*l,int *gold,int *zhidan,
						int *z8,int *z9)
{
	if(ptanke[0].live) JBox(ptanke[0].d, &ptanke[0].x, &ptanke[0].y, &ptanke[0].z, &*r, &*sd,&*zhidan,&ptanke[0].color);//装有坦克和子弹
	if(ptanke[1].live) DBox(ptanke[1].d, &ptanke[1].x, &ptanke[1].y, &ptanke[1].z, &*r, &ptanke[1].color);
	if(ptanke[2].live) DBox(ptanke[2].d, &ptanke[2].x, &ptanke[2].y, &ptanke[2].z, &*r, &ptanke[2].color);
	if(ptanke[3].live) DBox(ptanke[3].d, &ptanke[3].x, &ptanke[3].y, &ptanke[3].z, &*r, &ptanke[3].color);
	if(ptanke[4].live) DBox(ptanke[4].d, &ptanke[4].x, &ptanke[4].y, &ptanke[4].z, &*r, &ptanke[4].color);
	if(ptanke[5].live) DBoxBig(ptanke[5].d, &ptanke[5].x, &ptanke[5].y, &ptanke[5].z, &*r,& ptanke[5].color);
	if(ptanke[6].live) DBoxBig(ptanke[6].d, &ptanke[6].x, &ptanke[6].y, &ptanke[6].z, &*r,& ptanke[6].color);
	if(*live8) DBoxBig(x_8, &*x8, &*y8, &*z8, &*r, &*color8);
	if(*live9) DBoxFeiJi(x_9,x_10,x_11, &*x9, &*y9, &*z9, &*r);
	
	if((ptanke[0].live) && ptanke[1].live) ptanke[0].live = DBoom(ptanke[1].d, &ptanke[0].x, &ptanke[0].y, &*j,&*gold);//自己被打爆
	if((ptanke[0].live) && ptanke[2].live) ptanke[0].live = DBoom(ptanke[2].d, &ptanke[0].x, &ptanke[0].y, &*j,&*gold);
	if((ptanke[0].live) && ptanke[3].live) ptanke[0].live = DBoom(ptanke[3].d, &ptanke[0].x, &ptanke[0].y, &*j,&*gold);
	if((ptanke[0].live) && ptanke[4].live) ptanke[0].live = DBoom(ptanke[4].d, &ptanke[0].x, &ptanke[0].y, &*j,&*gold);
	if((ptanke[0].live) && ptanke[5].live) ptanke[0].live = DBoom(ptanke[5].d, &ptanke[0].x, &ptanke[0].y, &*j,&*gold);
	if((ptanke[0].live) && ptanke[6].live) ptanke[0].live = DBoom(ptanke[6].d, &ptanke[0].x, &ptanke[0].y, &*j,&*gold);
	if((ptanke[0].live) && *live8 )ptanke[0].live = DBoom(x_8, &ptanke[0].x, &ptanke[0].y, &*j,&*gold);
	if((ptanke[0].live) && *live9 )ptanke[0].live = DBoom(x_9, &ptanke[0].x, &ptanke[0].y, &*j,&*gold);
	if((ptanke[0].live) && *live9 )ptanke[0].live = DBoom(x_10, &ptanke[0].x, &ptanke[0].y, &*j,&*gold);
	if((ptanke[0].live) && *live9 )ptanke[0].live = DBoom(x_11, &ptanke[0].x, &ptanke[0].y, &*j,&*gold);
	
	if(ptanke[1].live) ptanke[1].live = DBoom(ptanke[0].d, &ptanke[1].x, &ptanke[1].y, &*d,&*gold);//敌方被打爆
	if(ptanke[2].live) ptanke[2].live = DBoom(ptanke[0].d, &ptanke[2].x, &ptanke[2].y, &*d,&*gold);
	if(ptanke[3].live) ptanke[3].live = DBoom(ptanke[0].d, &ptanke[3].x, &ptanke[3].y, &*d,&*gold);
	if(ptanke[4].live) ptanke[4].live = DBoom(ptanke[0].d, &ptanke[4].x, &ptanke[4].y, &*d,&*gold);
	if(ptanke[5].live) ptanke[5].live = DBoom(ptanke[0].d, &ptanke[5].x, &ptanke[5].y, &*d,&*gold);
	if(ptanke[6].live) ptanke[6].live = DBoom(ptanke[0].d, &ptanke[6].x, &ptanke[6].y, &*d,&*gold);
	if(*live8) *live8 = DBossBoomSmall(ptanke[0].d, &*x8, &*y8, &*l,&*sd);
	if(*live9) *live9 = DBossBoomBig(ptanke[0].d, &*x9, &*y9, &*k,&*zhidan);//飞机被打爆
	
	return;
}

void ZhengTiLuoShui(pTanKe ptanke,int*tileBlue_x1,int*tileBlue_y1,int*tileBlue_x2,int*tileBlue_y2,
					int *j,int *gold,int *y9)
{
	if(ptanke[0].live) ptanke[0].live = LuoShui(&ptanke[0].x, &ptanke[0].y, &*tileBlue_x1, &*tileBlue_y1, &*j,&*gold);//落水
	if(ptanke[0].live) ptanke[0].live = LuoShui(&ptanke[0].x, &ptanke[0].y, &*tileBlue_x2, &*tileBlue_y2, &*j,&*gold);
	
	if(ptanke[0].live) ptanke[0].live = BossMiaoRen(&ptanke[0].y,&*y9);
	return;
}
void ZhengTiLvSeZhangAiWu(pLvZhuan plvzhuan)
{
	tileLv(&plvzhuan[0].x, &plvzhuan[0].y);//绿色砖块；
	tileLv(&plvzhuan[1].x, &plvzhuan[1].y);//绿色砖块；
	tileLv(&plvzhuan[2].x, &plvzhuan[2].y);//绿色砖块；
	tileLv(&plvzhuan[3].x, &plvzhuan[3].y);//绿色砖块；
	tileLv(&plvzhuan[4].x, &plvzhuan[4].y);//绿色砖块；
	tileLv(&plvzhuan[5].x, &plvzhuan[5].y);//绿色砖块；
	tileLv(&plvzhuan[6].x, &plvzhuan[6].y);//绿色砖块；
	tileLv(&plvzhuan[7].x, &plvzhuan[7].y);//绿色砖块；
	tileLv(&plvzhuan[8].x, &plvzhuan[8].y);//绿色砖块；
	tileLv(&plvzhuan[9].x, &plvzhuan[9].y);//绿色砖块；
	tileLv(&plvzhuan[10].x, &plvzhuan[10].y);//绿色砖块；
	tileLv(&plvzhuan[11].x, &plvzhuan[11].y);//绿色砖块；
	return;
}

void ZhengTiWuPin(pTanKe ptanke,int *x8, int*y8,
				  bool *live8,bool *live9,
				  int*fazhang_x1,int *fazhang_y1,
				  int*shouqiang_x1,int *shouqiang_y1,
				  int*shangdian_x1,int *shangdian_y1,
				  int*yaoshui_x1,int *yaoshui_y1,
				  int*dunpai_x1,int *dunpai_y1,
				  int*xiezi_x1,int *xiezi_y1,
				  int*boss_x1,int *boss_y1,
				  int*bigboss_x1,int *bigboss_y1,
				  bool *wexist1, bool *wexist2,bool *wexist3,bool *wexist4,bool *wexist5,bool *wexist6,bool *wexist7,bool *wexist8,
				  int *sd,int *HWsd,int *ydsd,int *d,int *j, int *gold, int *zhidan,int *relive)
{
	if(*wexist1) FaZhang(&*fazhang_x1, &*fazhang_y1);//物品—法杖
	if(*wexist1) *wexist1 = HuoWu(&ptanke[0].x, &ptanke[0].y, &*fazhang_x1, &*fazhang_y1, &*d,&*HWsd);
	//////
	if(*wexist2) ShouQiang(&*shouqiang_x1, &*shouqiang_y1);//物品—枪
	if(*wexist2) *wexist2 = HuoWu(&ptanke[0].x, &ptanke[0].y, &*shouqiang_x1, &*shouqiang_y1, &*d,&*HWsd);
	if(!(*wexist2)) *sd = 1; else *sd = 2;
	//////
	if(*wexist8) XieZi(&*xiezi_x1, &*xiezi_y1);//物品—鞋子
	if(*wexist8) *wexist8 = HuoWu(&ptanke[0].x, &ptanke[0].y, &*xiezi_x1, &*xiezi_y1, &*d,&*HWsd);
	if(!(*wexist8)) *ydsd = 4; else *ydsd = 2;
	//////
	if(*wexist3 || *gold < 600) ShangDian(&*shangdian_x1, &*shangdian_y1);//物品—商店
	if(*wexist3) *wexist3 = HuoWu(&ptanke[0].x, &ptanke[0].y, &*shangdian_x1, &*shangdian_y1, &*d,&*HWsd);
	if(!(*wexist3)) 
	{
		if (*gold >= 600)
		{
			*zhidan = 15;
			ptanke[0].color = 4;
			*sd = 1;
		}
		if (*gold < 600)
		{
			setcolor(GREEN);
			settextstyle(0, 0, ("宋体"));
			char c2[20] = "抱歉，金币不足600";
			outtextxy(*shangdian_x1 - 32, *shangdian_y1 - 20, c2);
			*HWsd = 0;
			*wexist3 = HuoWu(&ptanke[0].x, &ptanke[0].y, &*shangdian_x1, &*shangdian_y1, &*d,&*HWsd);	
			*HWsd = 40;
		}	
	}
	else
	{
		*zhidan = 5;
		ptanke[0].color = 0;
	}
	//////
	if(*wexist4) YaoShui(&*yaoshui_x1, &*yaoshui_y1);//物品—药水
	if(*wexist4) *wexist4 = HuoWu(&ptanke[0].x, &ptanke[0].y, &*yaoshui_x1, &*yaoshui_y1, &*d,&*HWsd);
	if(!(*wexist4))
	{
		*j -= 3;
		*gold -= 1;
		*wexist4 = true;
		if (*gold % 5 == 0)
		{	
			*yaoshui_x1 = 32 + rand() % 576; //物品—药水；
			*yaoshui_y1 = 32 + rand() % 416;
		}
	}
	/////
	if(*wexist5 || *gold < 100) DunPai(&*dunpai_x1, &*dunpai_y1);//物品—盾牌
	if(*wexist5) *wexist5 = HuoWu(&ptanke[0].x, &ptanke[0].y, &*dunpai_x1, &*dunpai_y1, &*d,&*HWsd);
	if(!(*wexist5)) 
	{
		if (*gold >= 100)
		{
			ptanke[0].color = 6;
			*HWsd = 60;
			if(ptanke[1].live) ptanke[1].live = HuoWu(&ptanke[0].x, &ptanke[0].y, &ptanke[1].x, &ptanke[1].y, &*d,&*HWsd);
			if(ptanke[2].live) ptanke[2].live = HuoWu(&ptanke[0].x, &ptanke[0].y, &ptanke[2].x, &ptanke[2].y, &*d,&*HWsd);
			if(ptanke[3].live) ptanke[3].live = HuoWu(&ptanke[0].x, &ptanke[0].y, &ptanke[3].x, &ptanke[3].y, &*d,&*HWsd);
			if(ptanke[4].live) ptanke[4].live = HuoWu(&ptanke[0].x, &ptanke[0].y, &ptanke[4].x, &ptanke[4].y, &*d,&*HWsd);
			if(ptanke[5].live) ptanke[5].live = HuoWu(&ptanke[0].x, &ptanke[0].y, &ptanke[5].x, &ptanke[5].y, &*d,&*HWsd);
			if(ptanke[6].live) ptanke[6].live = HuoWu(&ptanke[0].x, &ptanke[0].y, &ptanke[6].x, &ptanke[6].y, &*d,&*HWsd);
			if(*live8) *live8 = HuoWu(&ptanke[0].x, &ptanke[0].y, &*x8, &*y8, &*d,&*HWsd);
			
			*HWsd = 40;
		}
		if (*gold < 100)
		{
			setcolor(GREEN);
			settextstyle(0, 0, ("宋体"));
			char c2[20] = "抱歉，金币不足100";
			outtextxy(*dunpai_x1 - 32, *dunpai_y1 - 20, c2);
			*HWsd = 0;
			*wexist5 = HuoWu(&ptanke[0].x,& ptanke[0].y, &*dunpai_x1, &*dunpai_y1, &*d,&*HWsd);	
			*HWsd = 40;
		}
		
	}
	else
	{
		ptanke[0].color = 0;
	}
	////////////
	if(*wexist6 || *gold != 450) Boss(&*boss_x1, &*boss_y1);//物品—boss
	if(*wexist6) *wexist6 = HuoWu(&ptanke[0].x, &ptanke[0].y, &*boss_x1, &*boss_y1, &*d,&*HWsd);
	if(!(*wexist6)) 
	{
		if (*gold == 250)
		{
			*live8 = true;
			*gold += 200;
			*relive -= 5;
		}
		if (*gold != 450)
		{
			setcolor(GREEN);
			settextstyle(0, 0, ("宋体"));
			char c2[30] = "仅当金币等于“250”释放";
			outtextxy(*boss_x1 - 32, *boss_y1 - 20, c2);
			char c3[50] = "被封印的Boss,杀掉+复活+钱";
			outtextxy(*boss_x1 - 27, *boss_y1 - 60, c3);
			char c4[50] = "钱>100时基地防御升级";
			outtextxy(*boss_x1 - 27, *boss_y1 - 40, c4);
			*HWsd = 0;
			*wexist6 = HuoWu(&ptanke[0].x, &ptanke[0].y, &*boss_x1, &*boss_y1, &*d,&*HWsd);	
			*HWsd = 40;
		}		
	}	
	///////////////////bigboss
	if(*wexist7 || *gold != 2000) BigBoss(&*bigboss_x1, &*bigboss_y1);//物品—boss
	if(*wexist7) *wexist7 = HuoWu(&ptanke[0].x, &ptanke[0].y, &*bigboss_x1, &*bigboss_y1, &*d,&*HWsd);
	if(!(*wexist7)) 
	{
		if (*gold == 1000)
		{
			*live9 = true;
			*gold += 1000;
		}
		if (*gold != 2000)
		{
			setcolor(GREEN);
			settextstyle(0, 0, ("宋体"));
			char c2[30] = "仅当金币等于“1000”释放";
			outtextxy(*bigboss_x1 - 32, *bigboss_y1 - 20, c2);
			char c3[30] = "终极Boss：你敢动我？";
			outtextxy(*bigboss_x1 - 32, *bigboss_y1 - 60, c3);
			char c4[30] = "提示：最好别靠近它";
			outtextxy(*bigboss_x1 - 32, *bigboss_y1 - 40, c4);
			*HWsd = 0;
			*wexist7 = HuoWu(&ptanke[0].x, &ptanke[0].y, &*bigboss_x1, &*bigboss_y1, &*d,&*HWsd);	
			*HWsd = 40;
		}		
	}	
	return;
}

void ZhengTiShengMing(pTanKe ptanke,pHongZhuan phongzhuan,
					  bool *exist_laowang, bool *exist1,bool *wexist1, bool *wexist2,bool *wexist3,bool *wexist8,
					  int *relive,int *j,int *d,int *gold,int *k)
{
	if(!(ptanke[0].live))
		lost(&ptanke[0].live, &*relive,&*gold);
	if(!(ptanke[1].live) && !(ptanke[2].live) && !(ptanke[3].live) && !(ptanke[4].live) && !(ptanke[5].live) && !(ptanke[6].live))
		win(phongzhuan,&ptanke[1].live, &ptanke[2].live, &ptanke[3].live, &ptanke[4].live,&ptanke[5].live,&ptanke[6].live,
		&*exist_laowang, &*exist1, 
		 &*wexist1, &*wexist2, &*wexist3, &*wexist8);
	if(!(*exist_laowang))
		GameOver();			
	
	JShengMing(&*j);
	DShengMing(&*d,&*k);
	
	Gold(&*gold);
	return;
}