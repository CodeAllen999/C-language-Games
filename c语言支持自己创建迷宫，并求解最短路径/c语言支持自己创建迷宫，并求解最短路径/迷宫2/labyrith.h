/********************************************
 * ������			:           �Թ�	    *
 * ���� : Redman <huangxionging@163.com>    *
 * ���뻷�� : vc++ 6.0 && EasyX Ver20120603 *
 * ����޸� :     2012-10-22			    *
 ********************************************/

#ifndef labyrith_h
#define labyrith_h

#include <iostream>
#include <graphics.h>
#include<windows.h>
#include <conio.h>

#pragma comment(lib, "WINMM.LIB") 

using namespace std;

int const QueueMaxLength = 1000;	// ��ջ��󳤶�

struct Node							// ����һ���ڵ�
{
	int x;							// ������ε� x ����
	int y;							// ������ε� y ����
	Node *pre;						// ��������ڵ�
};

class FrameWindow					// ����һ�����ڿ��
{
private:
	IMAGE img;						// ǽ��ͼƬ
	int direct;						// �������ⰴ��ʱ���������Թ�
	int control;					// ��ǳ�����ƿ���Ȩ
	MOUSEMSG msg;					// �����Ϣ
public:
	FrameWindow();					// Ĭ�Ϲ��캯��
	void NewBackground();			// �����±���
	void DrawSome();				// ����Щʲô
	void Run();						// ���п���
	void StartDrawLabyrith();		// ��ʼ�����Թ�
	void SetLabyrith();				// �����Թ�
	void Demo();					// Ѱ��·��, ����ʾ
};


class Queue							// ���������
{
private:
	Node *data;						// ������
	int front;						// ��ͷ
	int rear;						// ��β
public:
	Queue();						// ����Ĭ�Ϲ��캯��
	~Queue();						// ��������
	void Pop();						// ���Ӳ���
	void Push(Node node);			// ��Ӳ���
	void ResetPre();				// ���ýڵ�ǰ��
	Node visit(int i);				// ���ʽڵ�
	inline int GetFront();			// ��ȡ��ͷ
	inline int GetRear();			// ��ȡ��β
	void PrintRoute();				// ��ӡ·��
};

void PrintGrid(int x, int y);		// ���û�ȡ������ĳ����Ϊǽ��֮��, ���»��Ƹ���

extern int Wall[22][22];			// ǽ�ڱ������
extern int entranceX;				// ���
extern int entranceY;
extern int exitX;					// ����
extern int exitY;

#endif
