/* 【自学去】网站收集 http://www.zixue7.com */
#include <afxwin.h>
// 棋盘类
class CPlate
{
	int m_ndx;		// 棋盘格宽
	int m_ndy;		// 棋盘格高
	int m_nLeft;		// 棋盘位置
	int m_nTop;
	int m_nRight;
	int m_nBottom;
public:
			CPlate();
	void		ShowPlate(CDC *pDC);
	void		DrawConer(CDC *pDC, int row, int col, int type);
	CPoint	GetPosition(int col, int row);
};
// 棋盘类的成员函数
// 构造函数: 初始化
CPlate::CPlate()
{
	m_ndx		= 50;
	m_ndy		= 45;
	m_nLeft		= 198;
	m_nTop		= 30;
	m_nRight		= m_nLeft+m_ndx*8;
	m_nBottom	= m_nTop+m_ndy*9;
}
// 显示棋盘
void CPlate::ShowPlate(CDC *pDC)
{
	// 画棋盘方格
	CPen penRed2(PS_SOLID,2,RGB(255,0,0));
	CPen *pOldPen = pDC->SelectObject(&penRed2);
	for(int i=0; i<10; i++)
	{
		pDC->MoveTo(m_nLeft, m_nTop+i*m_ndy);
		pDC->LineTo(m_nRight, m_nTop+i*m_ndy);
	}
	for(i=0; i<9; i++)
	{
		if(i==0 || i==8)
		{
			pDC->MoveTo(m_nLeft+i*m_ndx, m_nTop);
			pDC->LineTo(m_nLeft+i*m_ndx, m_nBottom);
		}
		else{
			pDC->MoveTo(m_nLeft+i*m_ndx, m_nTop);
			pDC->LineTo(m_nLeft+i*m_ndx, m_nTop+4*m_ndy);
			pDC->MoveTo(m_nLeft+i*m_ndx, m_nTop+5*m_ndy);
			pDC->LineTo(m_nLeft+i*m_ndx, m_nBottom);
		}
	}
	// 画棋盘斜线
	pDC->SelectObject(pOldPen);
	CPen penRed1(PS_SOLID,1,RGB(255,0,0));
	pOldPen = pDC->SelectObject(&penRed1);
	pDC->MoveTo(m_nLeft+3*m_ndx, m_nTop);
	pDC->LineTo(m_nLeft+5*m_ndx, m_nTop+2*m_ndy);
	pDC->MoveTo(m_nLeft+3*m_ndx, m_nTop+2*m_ndy);
	pDC->LineTo(m_nLeft+5*m_ndx, m_nTop);
	pDC->MoveTo(m_nLeft+3*m_ndx, m_nBottom);
	pDC->LineTo(m_nLeft+5*m_ndx, m_nBottom-2*m_ndy);
	pDC->MoveTo(m_nLeft+3*m_ndx, m_nBottom-2*m_ndy);
	pDC->LineTo(m_nLeft+5*m_ndx, m_nBottom);
	pDC->SelectObject(pOldPen);
	// 画兵, 炮位标记
	DrawConer(pDC, 2, 1, 0);
	DrawConer(pDC, 2, 7, 0);
	DrawConer(pDC, 3, 0, 1);
	DrawConer(pDC, 3, 2, 0);
	DrawConer(pDC, 3, 4, 0);
	DrawConer(pDC, 3, 6, 0);
	DrawConer(pDC, 3, 8, 2);
	DrawConer(pDC, 7, 1, 0);
	DrawConer(pDC, 7, 7, 0);
	DrawConer(pDC, 6, 0, 1);
	DrawConer(pDC, 6, 2, 0);
	DrawConer(pDC, 6, 4, 0);
	DrawConer(pDC, 6, 6, 0);
	DrawConer(pDC, 6, 8, 2);
}
// 绘制兵, 炮位标志
void CPlate::DrawConer(CDC *pDC, int row, int col, int type)
{
	CPen penRed1(PS_SOLID,1,RGB(255,0,0));
	CPen *pOldPen = pDC->SelectObject(&penRed1);
	if(type == 0 || type == 1)
	{
		pDC->MoveTo(m_nLeft+col*m_ndx+ 3, m_nTop+row*m_ndy-10);
		pDC->LineTo(m_nLeft+col*m_ndx+ 3, m_nTop+row*m_ndy-3);
		pDC->LineTo(m_nLeft+col*m_ndx+10, m_nTop+row*m_ndy-3);
		pDC->MoveTo(m_nLeft+col*m_ndx+ 3, m_nTop+row*m_ndy+10);
		pDC->LineTo(m_nLeft+col*m_ndx+ 3, m_nTop+row*m_ndy+3);
		pDC->LineTo(m_nLeft+col*m_ndx+10, m_nTop+row*m_ndy+3);
	}
	if(type == 0 || type == 2)
	{
		pDC->MoveTo(m_nLeft+col*m_ndx- 3, m_nTop+row*m_ndy-10);
		pDC->LineTo(m_nLeft+col*m_ndx- 3, m_nTop+row*m_ndy-3);
		pDC->LineTo(m_nLeft+col*m_ndx-10, m_nTop+row*m_ndy-3);
		pDC->MoveTo(m_nLeft+col*m_ndx- 3, m_nTop+row*m_ndy+10);
		pDC->LineTo(m_nLeft+col*m_ndx- 3, m_nTop+row*m_ndy+3);
		pDC->LineTo(m_nLeft+col*m_ndx-10, m_nTop+row*m_ndy+3);
	}
	pDC->SelectObject(pOldPen);
}
// 取棋盘上各交叉点的坐标
CPoint CPlate::GetPosition(int col, int row)
{
	CPoint point;
	point.x = m_nLeft+col*m_ndx;
	point.y = m_nTop+row*m_ndy;
	return point;
}
// 棋子类
// 定义棋子名称
#define		BING		1
#define		PAO		2
#define		JU		3
#define		MA		4
#define		XIANG		5
#define		SHI		6
#define		JIANG		7
class CStone	
{
	BOOL		m_bRed;			// 是否红方
	BOOL		m_bSelected;	// 是否被选择
	int			m_nCol;			// 路
	int			m_nRow;			// 行
	CRect		m_rectStone;	// 棋子包含矩形
	BOOL		m_bShow;		// 是否显示
	CString		m_sName;		// 棋子名称
	int			m_nR;			// 棋子半径
	int			m_nType;		// 棋子类型
public:
	CStone	(){}
	CStone	(BOOL red, int col, int row, LPCSTR name, int type, CPlate &plate);
	void		ShowStone(CDC *pDC);
	void		MoveTo(int col, int row, CPlate &plate);
	CRect	GetRect(){return m_rectStone;}
	int		GetType(){return m_nType;}
	BOOL		BeKilled(int col, int row)
{return m_bShow && m_nCol==col && m_nRow == row;}
	BOOL	MouseOnStone(CPoint point)
{return m_rectStone.PtInRect(point) && m_bShow;}
	void	KillIt(){m_bShow = FALSE;}
	void	SelectStone(){m_bSelected = !m_bSelected;}
};
// 棋子类的成员函数
// 棋子类的构造函数：初始化棋子
CStone::CStone(BOOL red, int col, int row, LPCSTR name, int type, CPlate &plate)
{
	m_bShow		= TRUE;
	m_bSelected = FALSE;
	m_bRed		= red;
	m_nCol		= col;
	m_nRow		= row;
	m_sName		= name;
	m_nType		= type;
	m_nR		= 23;
	CPoint pos = plate.GetPosition(col, row);
	m_rectStone = CRect(pos.x-m_nR, pos.y-m_nR, pos.x+m_nR, pos.y+m_nR);
}
// 显示棋子
void CStone::ShowStone(CDC *pDC)
{
	if(m_bShow)	// 只有未被吃掉的棋子才显示
	{
		// 准备画棋子的画笔和画刷
		CPen *pOldPen, penNormal(PS_SOLID, 3, RGB(120, 120, 120));
		CBrush *pOldBrush, brushNormal, brushSelected;
		brushNormal.CreateSolidBrush(RGB(255, 255, 0));
		brushSelected.CreateSolidBrush(RGB(127, 127, 0));
		pOldPen = pDC->SelectObject(&penNormal);
		// 被选中的棋子颜色不同
		if(m_bSelected)
			pOldBrush = pDC->SelectObject(&brushSelected);
		else
			pOldBrush = pDC->SelectObject(&brushNormal);
		// 显示棋子
		CRect r(m_rectStone);
		r.left	++;
		r.top	++;
		r.right	--;
		r.bottom--;
		pDC->Ellipse(r);
		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);
		// 准备显示棋子名称的字体
		CFont *pOldFont, fontStone;
		fontStone.CreateFont(40, 0, 0, 0, 400, FALSE, FALSE,
							 0, OEM_CHARSET, OUT_DEFAULT_PRECIS,
							 CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
							 DEFAULT_PITCH, "楷体");
		pOldFont = pDC->SelectObject(&fontStone);
		int tx = m_rectStone.left+6;
		int ty = m_rectStone.top+6;
		pDC->SetBkMode(TRANSPARENT);
		// 棋子背景均为黄色，字分红、黑两色
		pDC->SetTextColor(RGB(m_bRed?255:0, 0, 0));
		pDC->TextOut(tx, ty, m_sName);
		pDC->SelectObject(pOldFont);
	}
}
// 将棋子放到指定位置
void CStone::MoveTo(int col, int row, CPlate &plate)
{
	m_bSelected = FALSE;
	m_nCol		= col;
	m_nRow		= row;
	CPoint pos	= plate.GetPosition(col, row);
	m_rectStone = CRect(pos.x-m_nR, pos.y-m_nR, pos.x+m_nR, pos.y+m_nR);
}
// 框架窗口类
class CMyWnd: public CFrameWnd
{
	CPlate	m_Plate;				// 棋盘
	CStone	m_StoneList[32];		// 棋子数组
	BOOL		m_bRedTurn;			// 轮红方下
	BOOL		m_bSelectOne;		// 已选择一棋子
	int		m_nWhichStone;		// 被选择棋子的编号
	CRect	m_rectInfo;			// 信息显示位置
public:
	CMyWnd(){InitGame();}
	void InitGame();
	void ShowInfo(CDC *pDC);
	BOOL KillSelfStone(int col, int row, BOOL red);
	int  KillEnemy(int col, int row, BOOL red);
	void MoveStone(CPoint point);
	void SelectStone(CPoint point);
	void Go(CPoint);
	BOOL MoveTo(int, int);
protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};
// 消息映射
BEGIN_MESSAGE_MAP(CMyWnd,CFrameWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()
// 框架窗口类的成员函数
// 初始化棋局
void CMyWnd::InitGame()
{
	m_bRedTurn		= TRUE;
	m_bSelectOne		= FALSE;
	m_rectInfo		= CRect(315, 480, 515, 550);
	m_StoneList[ 0] = CStone(TRUE, 0, 0, "车", 3, m_Plate);
	m_StoneList[ 1] = CStone(TRUE, 1, 0, "马", 4, m_Plate);
	m_StoneList[ 2] = CStone(TRUE, 2, 0, "象", 5, m_Plate);
	m_StoneList[ 3] = CStone(TRUE, 3, 0, "士", 6, m_Plate);
	m_StoneList[ 4] = CStone(TRUE, 4, 0, "将", 7, m_Plate);
	m_StoneList[ 5] = CStone(TRUE, 5, 0, "士", 6, m_Plate);
	m_StoneList[ 6] = CStone(TRUE, 6, 0, "象", 5, m_Plate);
	m_StoneList[ 7] = CStone(TRUE, 7, 0, "马", 4, m_Plate);
	m_StoneList[ 8] = CStone(TRUE, 8, 0, "车", 3, m_Plate);
	m_StoneList[ 9] = CStone(TRUE, 1, 2, "炮", 2, m_Plate);
	m_StoneList[10] = CStone(TRUE, 7, 2, "炮", 2, m_Plate);
	m_StoneList[11] = CStone(TRUE, 0, 3, "兵", 1, m_Plate);
	m_StoneList[12] = CStone(TRUE, 2, 3, "兵", 1, m_Plate);
	m_StoneList[13] = CStone(TRUE, 4, 3, "兵", 1, m_Plate);
	m_StoneList[14] = CStone(TRUE, 6, 3, "兵", 1, m_Plate);
	m_StoneList[15] = CStone(TRUE, 8, 3, "兵", 1, m_Plate);
	m_StoneList[16] = CStone(FALSE, 0, 9, "车", 3, m_Plate);
	m_StoneList[17] = CStone(FALSE, 1, 9, "马", 4, m_Plate);
	m_StoneList[18] = CStone(FALSE, 2, 9, "相", 5, m_Plate);
	m_StoneList[19] = CStone(FALSE, 3, 9, "仕", 6, m_Plate);
	m_StoneList[20] = CStone(FALSE, 4, 9, "帅", 7, m_Plate);
	m_StoneList[21] = CStone(FALSE, 5, 9, "仕", 6, m_Plate);
	m_StoneList[22] = CStone(FALSE, 6, 9, "相", 5, m_Plate);
	m_StoneList[23] = CStone(FALSE, 7, 9, "马", 4, m_Plate);
	m_StoneList[24] = CStone(FALSE, 8, 9, "车", 3, m_Plate);
	m_StoneList[25] = CStone(FALSE, 1, 7, "炮", 2, m_Plate);
	m_StoneList[26] = CStone(FALSE, 7, 7, "炮", 2, m_Plate);
	m_StoneList[27] = CStone(FALSE, 0, 6, "卒", 1, m_Plate);
	m_StoneList[28] = CStone(FALSE, 2, 6, "卒", 1, m_Plate);
	m_StoneList[29] = CStone(FALSE, 4, 6, "卒", 1, m_Plate);
	m_StoneList[30] = CStone(FALSE, 6, 6, "卒", 1, m_Plate);
	m_StoneList[31] = CStone(FALSE, 8, 6, "卒", 1, m_Plate);
}
// 处理 WM_ONPAINT 消息, 绘制窗口客户区 (绘制棋盘, 棋子等)
void CMyWnd::OnPaint()
{
	CPaintDC dc(this);
	m_Plate.ShowPlate(&dc);					// 显示棋盘
	for(int i=0; i<32; i++)					// 显示所有棋子
		m_StoneList[i].ShowStone(&dc);		
	ShowInfo(&dc);							// 显示轮谁行棋
}
// 处理 WM_ONLBUTTONDOWN 消息, 移动棋子
void CMyWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_bSelectOne) // 已选择了要移动的棋子
		MoveStone(point);
	else				// 尚未选择要移动的棋子
		SelectStone(point);
}
// 移动棋子
void CMyWnd::MoveStone(CPoint point)
{
	// 如果选择原来的棋子, 作废原来的选择
	if(m_StoneList[m_nWhichStone].MouseOnStone(point))
	{
		m_StoneList[m_nWhichStone].SelectStone();
		m_bSelectOne = FALSE;
		InvalidateRect(m_StoneList[m_nWhichStone].GetRect(), FALSE);
	}
	else // 在棋盘其他位置行棋
		Go(point);
}
// 走棋或吃棋
void CMyWnd::Go(CPoint point)
{
	for(int col=0; col<9; col++)	// 检查鼠标是否指向某个棋盘交叉点
		for(int row=0; row<10; row++)
		{
			CPoint p = m_Plate.GetPosition(col, row);
			CRect  r(p.x-23, p.y-23, p.x+23, p.y+23);
			if(r.PtInRect(point)) // 鼠标指向该交叉点
			{
				if(KillSelfStone(col, row, m_bRedTurn))
					MessageBox("您竟然想吃自己人?!");
				else
					m_bRedTurn = MoveTo(col, row);
			}
		}
}
// 移到指定位置或吃子
BOOL CMyWnd::MoveTo(int col, int row)
{
	// 更新窗口客户区原来的棋子位置
	InvalidateRect(m_StoneList[m_nWhichStone].GetRect());
	// 棋子移向新位置
	m_StoneList[m_nWhichStone].MoveTo(col, row, m_Plate);
	// 更新窗口客户区新的棋子位置
	InvalidateRect(m_StoneList[m_nWhichStone].GetRect());
	// 还原选择棋子标志
	m_bSelectOne = FALSE;
	// 检查是否吃了对方的棋子
	int i = KillEnemy(col, row, m_bRedTurn);
	if(i>=0)	// 确实吃了对方棋子
	{
		m_StoneList[i].KillIt();
		if(m_StoneList[i].GetType() == JIANG)
		{
			if(m_bRedTurn)
				MessageBox(m_bRedTurn?"红方胜!":"黑方胜!");
			InitGame();
			Invalidate();
			return TRUE;
		}
	}
	// 更新窗口客户区提示信息位置
	InvalidateRect(m_rectInfo);
	return !m_bRedTurn;
}
// 选择棋子
void CMyWnd::SelectStone(CPoint point)
{
	int nwhich = m_bRedTurn?0:16;
	// 逐个查看己方棋子是否被选中
	for(int i=nwhich; i<nwhich+16; i++)
		if(m_StoneList[i].MouseOnStone(point))
		{
			m_StoneList[i].SelectStone();
			// 更新窗口客户区被选中棋子的位置(该棋子要变色)
			InvalidateRect(m_StoneList[i].GetRect(), FALSE);
			m_nWhichStone	= i;
			m_bSelectOne	= TRUE;
			break;
		}
}
// 显示轮谁行棋
void CMyWnd::ShowInfo(CDC *pDC)
{
	CFont *pOldFont, fontInfo;
	fontInfo.CreateFont(50, 0, 0, 0, 400, FALSE, FALSE,
					 0, OEM_CHARSET, OUT_DEFAULT_PRECIS,
					 CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
					 DEFAULT_PITCH, "楷体");
	pOldFont = pDC->SelectObject(&fontInfo);
	pDC->SetTextColor(RGB(m_bRedTurn?255:0, 0, 0));
	pDC->TextOut(m_rectInfo.left, m_rectInfo.top,
				 m_bRedTurn?"红方行棋": "黑方行棋");
	pDC->SelectObject(pOldFont);
}
// 检查是否误杀己方棋子
BOOL CMyWnd::KillSelfStone(int col, int row, BOOL red)
{
	int from = red?0:16;
	// 逐个检查己方棋子是否被误杀
	for(int i=from; i<from+16; i++)
		if( m_StoneList[i].BeKilled(col, row))
			return TRUE;
	return FALSE;
}
// 检查是否吃对方棋子
int CMyWnd::KillEnemy(int col, int row, BOOL red)
{
	int from = red?16:0;
	// 逐个检查对方棋子是否被吃
	for(int i=from; i<from+16; i++)
		if( m_StoneList[i].BeKilled(col, row))
			return i;
	return -1;
}
// 应用程序类
class CMyApp: public CWinApp
{
public:
	BOOL	InitInstance();
};
// 应用程序类的实例初始化函数
BOOL CMyApp::InitInstance()
{
	CMyWnd *pFrame = new CMyWnd;
	pFrame->Create(0,_T("中国象棋程序"));
	pFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pFrame->UpdateWindow(); 
	this->m_pMainWnd = pFrame;
	return TRUE;
}
// 应用程序类的全局对象
CMyApp ThisApp;