/****************************************************/
/*	程 序 名: 坦克大战								*/
/*	作　　者: Sail丶Man <Email: 506629689@qq.com>	*/
/*	编译环境: vc++ 6.0 && EasyX库(附带graphics.h) 测试版 (2013-10-6 更新)		*/
/*  	最后修改: 2013-10-14							*/
/****************************************************/

#ifndef tankehaha_h
#define tankehaha_h

# include <graphics.h>
# include <stdio.h>
# include <time.h>
# pragma comment(lib,"Winmm.lib")
# pragma comment(lib, "msimg32.lib")

typedef struct TanKe
{
	int x;
	int y;
	int z;
	int color;
	bool live;
	int d[40][2][3];
	
}TanKe,*pTanKe;

typedef struct BaiZhuan
{
	int x;
	int y;
	bool exist;
}BaiZhuan,*pBaiZhuan;

typedef struct LvZhuan
{
	int x;
	int y;
}LvZhuan,*pLvZhuan;

typedef struct HongZhuan
{
	int x;
	int y;
	bool exist;
}HongZhuan,*pHongZhuan;

void start(void);
void start_(void);
void GongLue(void);
void MiJi(void);
void lost(bool *, int *,int *);
void GameOver(void);
void win(pHongZhuan phongzhuan,bool *, bool *, bool *, bool *, bool *, bool *, 
		 bool *, bool *,
		 bool *, bool *, bool *, bool *);
bool Quit(void);
void JShengMing(int *);
void DShengMing(int *, int *);
bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName);//音乐
void JFangXiang(int (*x)[2][3], int * , int * ,int *,pBaiZhuan pbaizhuan,pHongZhuan phongzhuan,int *);
void BossFangXiang(int (*x)[2][3], int * , int * ,int *,int *,int *);
void FeiJiFangXiang(int * x_, int * y_,int *r,int *o);
void DFangXiang(int (*x)[2][3], int * , int * ,int *,int *);
void JBox(int (*x)[2][3], int *,  int *, int * , int * , int *, int *, int *);
void DBox(int (*x)[2][3], int *,  int *, int * , int * , int *);
void DBoxBig(int (*x)[2][3], int *,  int *, int * , int * , int *);
void DBoxFeiJi(int (*x_9)[2][3],int (*x_10)[2][3],int (*x_11)[2][3],int * x_, int * y_, int * z, int *r);
bool DBoom(int (*x)[2][3], int *, int *, int *,int *);
bool QZBoom(int (*x)[2][3], int *, int *);//强制子弹消失，物体爆炸。
bool DBoomBig(int (*x)[2][3], int *, int *, int *);
bool DBossBoomBig(int (*x)[2][3], int *, int *, int *, int *);
bool DBossBoomSmall(int (*x)[2][3], int *, int *, int *, int *);
void LaoWang(int * tilex, int * tiley);
void tileHong(int *, int *);
void tileLv(int *, int *);
void tileBai(int *, int *);
void tileBlue(int *, int *);
bool LuoShui(int *, int *, int *, int *, int *, int *);
bool BossMiaoRen(int *, int *);
bool HuoWu(int *, int *, int *, int *, int *, int *);
void FaZhang(int *, int *);
void ShouQiang(int *, int *);
void ShangDian(int *, int *);
void YaoShui(int *, int *);
void DunPai(int *, int *);
void XieZi(int *, int *);
void Boss(int *, int *);
void BigBoss(int *, int *);
void music(void);
void Gold(int*);
//////////////主函数主循环浓缩///////////////
void ZhengTiLaoWang(pTanKe ptanke,int (*x_8)[2][3],int (*x_9)[2][3],int (*x_10)[2][3],int (*x_11)[2][3],
					bool *,bool *,int*,int*,int*,int*,int*,int*,int*,int*,bool*);
void ZhengTiFangXiang(pTanKe ptanke, pBaiZhuan pbaizhuan,pHongZhuan phongzhuan, int (*x_8)[2][3],
					  bool *,bool *,
					  int*,int*,int*,int*,int*,
					  int *,
					  int *,int *);
void ZhengTiHongSeZhangAiWu(pTanKe ptanke,int (*x_8)[2][3],int (*x_9)[2][3],
							int*,pHongZhuan phongzhuan);
void ZhengTiBaiSeZhangAiWu(pTanKe ptanke,int (*x_8)[2][3],int (*x_9)[2][3],int (*x_10)[2][3],int (*x_11)[2][3],
						   bool *,
						   int*,pBaiZhuan pbaizhuan);
void ZhengTiLanSeZhangAiWu(int *, int *,int *, int *);
void ZhengTiTanKeBaoZha(pTanKe ptanke,int (*x_8)[2][3],int (*x_9)[2][3],int (*x_10)[2][3],int (*x_11)[2][3],
						bool *,bool *,
						int*,int*,int*,int*,int*,
						int *,int *,
						int *,int*,int*,int*,int*,int *,
						int *,int *);
void ZhengTiLuoShui(pTanKe ptanke,int*,int*,int*,int*,
					int *,int *,int *);
void ZhengTiLvSeZhangAiWu(pLvZhuan plvzhuan);
void ZhengTiWuPin(pTanKe ptanke,int *, int*,
				  bool *,bool *,
				  int*,int *,
				  int *,int *,
				  int *,int *,
				  int *,int *,
				  int *,int *,
				  int *,int *,
				  int *,int *,
				  int *,int *,
				  bool *, bool *, bool *,bool *,bool *,bool *,bool *,bool *,
				  int *,int *,int *,int *,int *, int *, int *, int *);
void ZhengTiShengMing(pTanKe ptanke,pHongZhuan phongzhuan,
					  bool *, bool *,bool *,bool *,bool *,bool *,
					  int *,int *,int *,int *,int *);

#endif
