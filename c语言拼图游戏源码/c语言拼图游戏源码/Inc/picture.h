/****************************************************/
/*	�� �� ��: ƴͼ2_0								*/
/*	��������: Redman <Email: huangxionging@163.com>	*/
/*	���뻷��: vc++ 6.0 && EasyX_v20130610(beta)		*/
/*  ����޸�: 2013-06-23							*/
/****************************************************/

#ifndef picture_h
#define picture_h

// ����ͷ�ļ�
#include <easyx.h>
#include <conio.h>
   #include <string>
#include <ctime>

using namespace std;

// ������Ϸ�ı�����ɫ
#define BgColor   LIGHTGREEN

#pragma comment(lib,"winmm.lib")                                        //���ؿ��ļ�

// ��Ϸ�Ĺ���
const int PassCount = 8;

// ��Ϸ�߿�Ĵ�С
const int xLength = 953;
const int yLength = 453;
const int Width = 600;
const int Height = 450;

// ͼƬ, �ṹ��, ����ͼ��
struct Image
{
    IMAGE image;                                                        // ����ͼ��
    int x;                                                              // ����ͼ��� x ����
    int y;                                                              // ����ͼ��� y ����
};

// ��Ϸ�Ŀ����
class GameFrame
{
    public:
        GameFrame();                                                    // Ĭ�Ϲ��캯��
        void DrawBackground();                                          // ���Ʊ���ͼ��
        void StartMenu();                                               // ��ʼ����, ѡ����Ϸ�Ѷ�
};

// ͼ����
class Picture
{
	private:
		IMAGE img;														// ��������ͼ��
		Image **image;                                                  // �����и�ͼ��
        int Control;                                                    // ����ֵ
        int Diffcult;                                                   // �Ѷ�ֵ
        int Pass;                                                       // ��¼��ǰ�Ĺ���
		int LocalX;														// ��¼����λ����Ϣ
		int LocalY;
        string String;													// ����ͼƬ·��
		MOUSEMSG MouseMessage;											// �����Ϣ
		int singleWidth;												// ����ͼ��Ŀ��
		int singleHeight;												// ����ͼ��ĸ߶�
		int **Query;													// ��ѯ����, ���ٶ�λͼƬ
    public:
		Picture()														// Ĭ�Ϲ��캯��
		{
            Control = 0;
            Diffcult = 0;
            Pass = 0;
            String = "Res\\00.jpg";
			LocalX = 0;
			LocalY = 0;
			singleWidth = 0;
			singleHeight = 0;
		}
		void Run();														// ���ƺ���
		void SetGameDifficult();										// ������Ϸ���Ѷ�
        void SetPicture();                                              // ����ͼƬ
		void SetLocal();												// ����λ��
		void DrawRect();												// ��������
		void PrintPicture();											// ��ͼ���������Ļ
        void ProcessMouse();                                            // ���������Ϣ, ʵ���ƶ��Ĺؼ��㷨
		void ProcessPicture();											// ����ͼ��
		void IsPass();                                                  // �ж��Ƿ�ͨ��
};

#endif
