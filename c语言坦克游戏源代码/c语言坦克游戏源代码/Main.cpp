/* ����ѧȥ����վ�ռ� http://www.zixue7.com */
# include "tanke.h"

int main(void)
{		
	start();//��ʼ˵��
	
	int r = 0;//���ٵ�
	int relive = 0;//�������
	int sd = 2;//�ӵ��ٶ�
	int HWsd = 40;
	int gold = 0;//���
	int zhidan = 5;//����̹���ӵ���С
	int o = 0; //boss���򴢴�
	int ydsd = 2;//�ƶ��ٶ�
	
	int j = 0;//��ըͼƬ���,��������ֵ
	int d = 0;//��ըͼƬ���
	int k = 0;//boss����ֵ
	int l = 0;//Сboss����ֵ
	int m = 0;//��Ʒ����ֵ
	
	
	TanKe tanke[7] = {	{0,0, 0, 0,   true, {0}},
						{0,0, 0, 0,   true, {0}},
						{0,0, 0, 56,  true, {0}},
						{0,0, 0, 112, true, {0}},
						{0,0, 0, 168, true, {0}},
						{0,0, 0, 112, true, {0}},
						{0,0, 0, 168, true, {0}}};
	
	pTanKe ptanke = NULL;

	BaiZhuan baizhuan[3] = { {0,0,true},{0,0,true},{0,0,true}};

	pBaiZhuan pbaizhuan = NULL;

	LvZhuan lvzhuan[12];
	pLvZhuan plvzhuan = NULL;

	HongZhuan hongzhuan[2] ={ {0,0,true},{0,0,true}};
	pHongZhuan phongzhuan = NULL;

	
	tanke[0].d[1][0][1] = 0;//��ʼ��������һ���ӵ�������
	tanke[0].d[1][0][2] = -1;
	
	tanke[1].d[1][0][1] = 0;//��ʼ��������һ���ӵ�������
	tanke[1].d[1][0][2] = -1;
	
	tanke[2].d[1][0][1] = 0;//��ʼ��������һ���ӵ�������
	tanke[2].d[1][0][2] = -1;
	
	tanke[3].d[1][0][1] = 0;//��ʼ��������һ���ӵ�������
	tanke[3].d[1][0][2] = -1;
	
	tanke[4].d[1][0][1] = 0;//��ʼ��������һ���ӵ�������
	tanke[4].d[1][0][2] = -1;
	
	tanke[5].d[1][0][1] = 0;//��ʼ��������һ���ӵ�������
	tanke[5].d[1][0][2] = -1;
	
	tanke[6].d[1][0][1] = 0;//��ʼ��������һ���ӵ�������
	tanke[6].d[1][0][2] = -1;
	
	
	int z8 = 0;//��̹��
	int z9 = 0;//�ɻ�
	
	
	int color8 = 0;//��boss
	
	int x_8[40][2][3] = {0};//��̹���ӵ�
	int x_9[40][2][3] = {0};
	int x_10[40][2][3] = {0};//�ɻ��ӵ�
	int x_11[40][2][3] = {0};//�ɻ��ӵ�
	
	x_8[1][0][1] = 0;//��ʼ��������һ���ӵ�������
	x_8[1][0][2] = -1;
	
	start_();
	
	bool live8 = false;//��̹��
	bool live9 = false;//�ɻ�
	
	bool exist_laowang  = true;
	bool exist1 = true;	//boss��ש
	
	bool wexist1 = true;//����
	bool wexist2 = true;//ǹ
	bool wexist3 = true;//�̵�
	bool wexist4 = true;//ҩˮ
	bool wexist5 = true;//����
	bool wexist8 = true;//Ь��
	bool wexist6 = true;//��Ʒ��boss
	bool wexist7 = true;//��Ʒ��bigboss
	
	int tilelaowang_x = 304;//����
	int tilelaowang_y = 448;
	int tileHong_x1 = 304;//����ǰ�ϰ���
	int tileHong_y1 = 416;
	
	while(true)
	{
		tanke[0].x = 28 + rand() % 584, tanke[0].y = 400 + rand() % 52;//�������飬
		tanke[1].x = 28 + rand() % 584, tanke[1].y = 28 + rand() % 124;//�з����飬��ͬ��
		tanke[2].x = 28 + rand() % 584, tanke[2].y = 28 + rand() % 124;
		tanke[3].x = 28 + rand() % 584, tanke[3].y = 28 + rand() % 124;
		tanke[4].x = 28 + rand() % 584, tanke[4].y = 28 + rand() % 124;
		tanke[5].x = 28 + rand() % 584, tanke[5].y = 28 + rand() % 124;
		tanke[6].x = 28 + rand() % 584, tanke[6].y = 28 + rand() % 124;
		//int x8 = 28 + rand() % 584, y8 = 28 + rand() % 124;//���������
		int x9 = 320, y9 = -80;//��boss
		
		hongzhuan[0].x = 100 + rand() % 376;//��ɫש��
		hongzhuan[0].y = 200 + rand() % 216;
		hongzhuan[1].x = 32 + rand() % 576;//��ɫש��
		hongzhuan[1].y = 32 + rand() % 416;
		baizhuan[0].x = 32 + rand() % 576; //��ɫש��
		baizhuan[0].y = 32 + rand() % 416;
		baizhuan[1].x = 32 + rand() % 576; //��ɫש��
		baizhuan[1].y = 32 + rand() % 416;
		baizhuan[2].x = 32 + rand() % 576; //��ɫש��
		baizhuan[2].y = 32 + rand() % 416;
		int tileBai_x4 = -20; //����ǰ��ɫש����Ĵ��ã�
		int tileBai_y4 = -20;
		
		lvzhuan[0].x = 32 + rand() % 576; //��ɫש��
		lvzhuan[0].y = 32 + rand() % 416; 
		lvzhuan[1].x = 32 + rand() % 576; 
		lvzhuan[1].y = 32 + rand() % 416; 
		lvzhuan[2].x = 32 + rand() % 576; 
		lvzhuan[2].y = 32 + rand() % 416;
		lvzhuan[3].x = 32 + rand() % 576; 
		lvzhuan[3].y = 32 + rand() % 416;
		lvzhuan[4].x = 32 + rand() % 576; 
		lvzhuan[4].y = 32 + rand() % 416;
		lvzhuan[5].x = 32 + rand() % 576; 
		lvzhuan[5].y = 32 + rand() % 416;
		lvzhuan[6].x = 32 + rand() % 576; //��ɫש��
		lvzhuan[6].y = 32 + rand() % 416; 
		lvzhuan[7].x = 32 + rand() % 576; 
		lvzhuan[7].y = 32 + rand() % 416; 
		lvzhuan[8].x = 32 + rand() % 576; 
		lvzhuan[8].y = 32 + rand() % 416;
		lvzhuan[9].x = 32 + rand() % 576; 
		lvzhuan[9].y = 32 + rand() % 416;
		lvzhuan[10].x = 32 + rand() % 576; 
		lvzhuan[10].y = 32 + rand() % 416;
		lvzhuan[11].x = 32 + rand() % 576; 
		lvzhuan[11].y = 32 + rand() % 416;
		int tileBlue_x1 = 32 + rand() % 576; //��ɫש��
		int tileBlue_y1 = 32 + rand() % 416; 
		int tileBlue_x2 = 32 + rand() % 576; //��ɫש��
		int tileBlue_y2 = 32 + rand() % 416;
		
		int fazhang_x1 = 32 + rand() % 576; //��Ʒ�����ȣ�
		int fazhang_y1 = 32 + rand() % 416;
		
		int shouqiang_x1 = 32 + rand() % 576; //��Ʒ��ǹ��
		int shouqiang_y1 = 32 + rand() % 416;
		
		int shangdian_x1 = 32 + rand() % 576; //��Ʒ���̵ꣻ
		int shangdian_y1 = 200 + rand() % 216;
		
		int yaoshui_x1 = 32 + rand() % 576; //��Ʒ��ҩˮ��
		int yaoshui_y1 = 32 + rand() % 416;
		
		int dunpai_x1 = 32 + rand() % 576; //��Ʒ�����ƣ�
		int dunpai_y1 = 32 + rand() % 116;

		int xiezi_x1 = 32 + rand() % 576; //��Ʒ��Ь�ӣ�
		int xiezi_y1 = 32 + rand() % 116;
		
		int boss_x1 = 100 + rand() % 376; //��Ʒ��Boss��
		int boss_y1 = 100 + rand() % 216;
		int x8 = boss_x1 , y8 = boss_y1;
		
		int bigboss_x1 = hongzhuan[0].x ; //��Ʒ��bigBoss��
		int bigboss_y1 = hongzhuan[0].y ;
		
		
		while (true)
		{	
			ZhengTiFangXiang(tanke,baizhuan,hongzhuan,x_8,
				&live8,&live9,
				&r,&x8,&y8,&x9,&y9,
				&z8,
				&o,&ydsd);//����
			
			cleardevice();//����
			
			ZhengTiLaoWang(tanke,x_8,x_9,x_10,x_11,
				&exist_laowang,&exist1,&gold,&d,
				&tilelaowang_x,&tilelaowang_y,&tileHong_x1,&tileHong_y1,&tileBai_x4,&tileBai_y4,&live9);//����
			
			ZhengTiBaiSeZhangAiWu(tanke,x_8,x_9,x_10,x_11,
				&wexist1,
				&d,baizhuan);//��ש
			
			ZhengTiLanSeZhangAiWu(&tileBlue_x1,&tileBlue_y1,&tileBlue_x2,&tileBlue_y2);//��ש
			
			ZhengTiTanKeBaoZha(tanke,x_8,x_9,x_10,x_11,
				&live8,&live9,
				&r,&x8,&y8,&x9,&y9,
				&sd,&color8,
				&j,&d,&k,&l,&gold,&zhidan,
				&z8,&z9);//̹�� �� ��ը
			
			ZhengTiLuoShui(tanke,&tileBlue_x1,&tileBlue_y1,&tileBlue_x2,&tileBlue_y2,
				&j,&gold,&y9);//��ˮ.boss����
			
			ZhengTiLvSeZhangAiWu(lvzhuan);//��ש
			
			ZhengTiWuPin(tanke,&x8,&y8,
				&live8,&live9,
				&fazhang_x1,&fazhang_y1,
				&shouqiang_x1,&shouqiang_y1,
				&shangdian_x1,&shangdian_y1,
				&yaoshui_x1,&yaoshui_y1,
				&dunpai_x1,&dunpai_y1,
				&xiezi_x1,&xiezi_y1,
				&boss_x1,&boss_y1,
				&bigboss_x1,&bigboss_y1,
				&wexist1, &wexist2,&wexist3,&wexist4,&wexist5,&wexist6,&wexist7,&wexist8,
				&sd,&HWsd,&ydsd, &d,&j,&gold,&zhidan,&relive);//��Ʒ

			ZhengTiHongSeZhangAiWu(tanke,x_8,x_9,
				&d,hongzhuan);//��ש ���boss
			
			ZhengTiShengMing(tanke,hongzhuan,
				&exist_laowang,&exist1,&wexist1,&wexist2,&wexist3,&wexist8,
				&relive,&j,&d,&gold,&k);//����
			
			FlushBatchDraw();
			
			if (GetAsyncKeyState('Y'))
			{break;}
			
			if (Quit())
			{exit(0);}

			if (gold == 2200)
			{
				MiJi();
			}

		}
	}
	EndBatchDraw(); 
	return 0;
}
