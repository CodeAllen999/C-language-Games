/* ����ѧȥ����վ�ռ� http://www.zixue7.com */
#include <afxwin.h>
// ������
class CPlate
{
	int m_ndx;		// ���̸��
	int m_ndy;		// ���̸��
	int m_nLeft;		// ����λ��
	int m_nTop;
	int m_nRight;
	int m_nBottom;
public:
			CPlate();
	void		ShowPlate(CDC *pDC);
	void		DrawConer(CDC *pDC, int row, int col, int type);
	CPoint	GetPosition(int col, int row);
};
// ������ĳ�Ա����
// ���캯��: ��ʼ��
CPlate::CPlate()
{
	m_ndx		= 50;
	m_ndy		= 45;
	m_nLeft		= 198;
	m_nTop		= 30;
	m_nRight		= m_nLeft+m_ndx*8;
	m_nBottom	= m_nTop+m_ndy*9;
}
// ��ʾ����
void CPlate::ShowPlate(CDC *pDC)
{
	// �����̷���
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
	// ������б��
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
	// ����, ��λ���
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
// ���Ʊ�, ��λ��־
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
// ȡ�����ϸ�����������
CPoint CPlate::GetPosition(int col, int row)
{
	CPoint point;
	point.x = m_nLeft+col*m_ndx;
	point.y = m_nTop+row*m_ndy;
	return point;
}
// ������
// ������������
#define		BING		1
#define		PAO		2
#define		JU		3
#define		MA		4
#define		XIANG		5
#define		SHI		6
#define		JIANG		7
class CStone	
{
	BOOL		m_bRed;			// �Ƿ�췽
	BOOL		m_bSelected;	// �Ƿ�ѡ��
	int			m_nCol;			// ·
	int			m_nRow;			// ��
	CRect		m_rectStone;	// ���Ӱ�������
	BOOL		m_bShow;		// �Ƿ���ʾ
	CString		m_sName;		// ��������
	int			m_nR;			// ���Ӱ뾶
	int			m_nType;		// ��������
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
// ������ĳ�Ա����
// ������Ĺ��캯������ʼ������
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
// ��ʾ����
void CStone::ShowStone(CDC *pDC)
{
	if(m_bShow)	// ֻ��δ���Ե������Ӳ���ʾ
	{
		// ׼�������ӵĻ��ʺͻ�ˢ
		CPen *pOldPen, penNormal(PS_SOLID, 3, RGB(120, 120, 120));
		CBrush *pOldBrush, brushNormal, brushSelected;
		brushNormal.CreateSolidBrush(RGB(255, 255, 0));
		brushSelected.CreateSolidBrush(RGB(127, 127, 0));
		pOldPen = pDC->SelectObject(&penNormal);
		// ��ѡ�е�������ɫ��ͬ
		if(m_bSelected)
			pOldBrush = pDC->SelectObject(&brushSelected);
		else
			pOldBrush = pDC->SelectObject(&brushNormal);
		// ��ʾ����
		CRect r(m_rectStone);
		r.left	++;
		r.top	++;
		r.right	--;
		r.bottom--;
		pDC->Ellipse(r);
		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);
		// ׼����ʾ�������Ƶ�����
		CFont *pOldFont, fontStone;
		fontStone.CreateFont(40, 0, 0, 0, 400, FALSE, FALSE,
							 0, OEM_CHARSET, OUT_DEFAULT_PRECIS,
							 CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
							 DEFAULT_PITCH, "����");
		pOldFont = pDC->SelectObject(&fontStone);
		int tx = m_rectStone.left+6;
		int ty = m_rectStone.top+6;
		pDC->SetBkMode(TRANSPARENT);
		// ���ӱ�����Ϊ��ɫ���ַֺ졢����ɫ
		pDC->SetTextColor(RGB(m_bRed?255:0, 0, 0));
		pDC->TextOut(tx, ty, m_sName);
		pDC->SelectObject(pOldFont);
	}
}
// �����ӷŵ�ָ��λ��
void CStone::MoveTo(int col, int row, CPlate &plate)
{
	m_bSelected = FALSE;
	m_nCol		= col;
	m_nRow		= row;
	CPoint pos	= plate.GetPosition(col, row);
	m_rectStone = CRect(pos.x-m_nR, pos.y-m_nR, pos.x+m_nR, pos.y+m_nR);
}
// ��ܴ�����
class CMyWnd: public CFrameWnd
{
	CPlate	m_Plate;				// ����
	CStone	m_StoneList[32];		// ��������
	BOOL		m_bRedTurn;			// �ֺ췽��
	BOOL		m_bSelectOne;		// ��ѡ��һ����
	int		m_nWhichStone;		// ��ѡ�����ӵı��
	CRect	m_rectInfo;			// ��Ϣ��ʾλ��
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
// ��Ϣӳ��
BEGIN_MESSAGE_MAP(CMyWnd,CFrameWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()
// ��ܴ�����ĳ�Ա����
// ��ʼ�����
void CMyWnd::InitGame()
{
	m_bRedTurn		= TRUE;
	m_bSelectOne		= FALSE;
	m_rectInfo		= CRect(315, 480, 515, 550);
	m_StoneList[ 0] = CStone(TRUE, 0, 0, "��", 3, m_Plate);
	m_StoneList[ 1] = CStone(TRUE, 1, 0, "��", 4, m_Plate);
	m_StoneList[ 2] = CStone(TRUE, 2, 0, "��", 5, m_Plate);
	m_StoneList[ 3] = CStone(TRUE, 3, 0, "ʿ", 6, m_Plate);
	m_StoneList[ 4] = CStone(TRUE, 4, 0, "��", 7, m_Plate);
	m_StoneList[ 5] = CStone(TRUE, 5, 0, "ʿ", 6, m_Plate);
	m_StoneList[ 6] = CStone(TRUE, 6, 0, "��", 5, m_Plate);
	m_StoneList[ 7] = CStone(TRUE, 7, 0, "��", 4, m_Plate);
	m_StoneList[ 8] = CStone(TRUE, 8, 0, "��", 3, m_Plate);
	m_StoneList[ 9] = CStone(TRUE, 1, 2, "��", 2, m_Plate);
	m_StoneList[10] = CStone(TRUE, 7, 2, "��", 2, m_Plate);
	m_StoneList[11] = CStone(TRUE, 0, 3, "��", 1, m_Plate);
	m_StoneList[12] = CStone(TRUE, 2, 3, "��", 1, m_Plate);
	m_StoneList[13] = CStone(TRUE, 4, 3, "��", 1, m_Plate);
	m_StoneList[14] = CStone(TRUE, 6, 3, "��", 1, m_Plate);
	m_StoneList[15] = CStone(TRUE, 8, 3, "��", 1, m_Plate);
	m_StoneList[16] = CStone(FALSE, 0, 9, "��", 3, m_Plate);
	m_StoneList[17] = CStone(FALSE, 1, 9, "��", 4, m_Plate);
	m_StoneList[18] = CStone(FALSE, 2, 9, "��", 5, m_Plate);
	m_StoneList[19] = CStone(FALSE, 3, 9, "��", 6, m_Plate);
	m_StoneList[20] = CStone(FALSE, 4, 9, "˧", 7, m_Plate);
	m_StoneList[21] = CStone(FALSE, 5, 9, "��", 6, m_Plate);
	m_StoneList[22] = CStone(FALSE, 6, 9, "��", 5, m_Plate);
	m_StoneList[23] = CStone(FALSE, 7, 9, "��", 4, m_Plate);
	m_StoneList[24] = CStone(FALSE, 8, 9, "��", 3, m_Plate);
	m_StoneList[25] = CStone(FALSE, 1, 7, "��", 2, m_Plate);
	m_StoneList[26] = CStone(FALSE, 7, 7, "��", 2, m_Plate);
	m_StoneList[27] = CStone(FALSE, 0, 6, "��", 1, m_Plate);
	m_StoneList[28] = CStone(FALSE, 2, 6, "��", 1, m_Plate);
	m_StoneList[29] = CStone(FALSE, 4, 6, "��", 1, m_Plate);
	m_StoneList[30] = CStone(FALSE, 6, 6, "��", 1, m_Plate);
	m_StoneList[31] = CStone(FALSE, 8, 6, "��", 1, m_Plate);
}
// ���� WM_ONPAINT ��Ϣ, ���ƴ��ڿͻ��� (��������, ���ӵ�)
void CMyWnd::OnPaint()
{
	CPaintDC dc(this);
	m_Plate.ShowPlate(&dc);					// ��ʾ����
	for(int i=0; i<32; i++)					// ��ʾ��������
		m_StoneList[i].ShowStone(&dc);		
	ShowInfo(&dc);							// ��ʾ��˭����
}
// ���� WM_ONLBUTTONDOWN ��Ϣ, �ƶ�����
void CMyWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_bSelectOne) // ��ѡ����Ҫ�ƶ�������
		MoveStone(point);
	else				// ��δѡ��Ҫ�ƶ�������
		SelectStone(point);
}
// �ƶ�����
void CMyWnd::MoveStone(CPoint point)
{
	// ���ѡ��ԭ��������, ����ԭ����ѡ��
	if(m_StoneList[m_nWhichStone].MouseOnStone(point))
	{
		m_StoneList[m_nWhichStone].SelectStone();
		m_bSelectOne = FALSE;
		InvalidateRect(m_StoneList[m_nWhichStone].GetRect(), FALSE);
	}
	else // ����������λ������
		Go(point);
}
// ��������
void CMyWnd::Go(CPoint point)
{
	for(int col=0; col<9; col++)	// �������Ƿ�ָ��ĳ�����̽����
		for(int row=0; row<10; row++)
		{
			CPoint p = m_Plate.GetPosition(col, row);
			CRect  r(p.x-23, p.y-23, p.x+23, p.y+23);
			if(r.PtInRect(point)) // ���ָ��ý����
			{
				if(KillSelfStone(col, row, m_bRedTurn))
					MessageBox("����Ȼ����Լ���?!");
				else
					m_bRedTurn = MoveTo(col, row);
			}
		}
}
// �Ƶ�ָ��λ�û����
BOOL CMyWnd::MoveTo(int col, int row)
{
	// ���´��ڿͻ���ԭ��������λ��
	InvalidateRect(m_StoneList[m_nWhichStone].GetRect());
	// ����������λ��
	m_StoneList[m_nWhichStone].MoveTo(col, row, m_Plate);
	// ���´��ڿͻ����µ�����λ��
	InvalidateRect(m_StoneList[m_nWhichStone].GetRect());
	// ��ԭѡ�����ӱ�־
	m_bSelectOne = FALSE;
	// ����Ƿ���˶Է�������
	int i = KillEnemy(col, row, m_bRedTurn);
	if(i>=0)	// ȷʵ���˶Է�����
	{
		m_StoneList[i].KillIt();
		if(m_StoneList[i].GetType() == JIANG)
		{
			if(m_bRedTurn)
				MessageBox(m_bRedTurn?"�췽ʤ!":"�ڷ�ʤ!");
			InitGame();
			Invalidate();
			return TRUE;
		}
	}
	// ���´��ڿͻ�����ʾ��Ϣλ��
	InvalidateRect(m_rectInfo);
	return !m_bRedTurn;
}
// ѡ������
void CMyWnd::SelectStone(CPoint point)
{
	int nwhich = m_bRedTurn?0:16;
	// ����鿴���������Ƿ�ѡ��
	for(int i=nwhich; i<nwhich+16; i++)
		if(m_StoneList[i].MouseOnStone(point))
		{
			m_StoneList[i].SelectStone();
			// ���´��ڿͻ�����ѡ�����ӵ�λ��(������Ҫ��ɫ)
			InvalidateRect(m_StoneList[i].GetRect(), FALSE);
			m_nWhichStone	= i;
			m_bSelectOne	= TRUE;
			break;
		}
}
// ��ʾ��˭����
void CMyWnd::ShowInfo(CDC *pDC)
{
	CFont *pOldFont, fontInfo;
	fontInfo.CreateFont(50, 0, 0, 0, 400, FALSE, FALSE,
					 0, OEM_CHARSET, OUT_DEFAULT_PRECIS,
					 CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
					 DEFAULT_PITCH, "����");
	pOldFont = pDC->SelectObject(&fontInfo);
	pDC->SetTextColor(RGB(m_bRedTurn?255:0, 0, 0));
	pDC->TextOut(m_rectInfo.left, m_rectInfo.top,
				 m_bRedTurn?"�췽����": "�ڷ�����");
	pDC->SelectObject(pOldFont);
}
// ����Ƿ���ɱ��������
BOOL CMyWnd::KillSelfStone(int col, int row, BOOL red)
{
	int from = red?0:16;
	// �����鼺�������Ƿ���ɱ
	for(int i=from; i<from+16; i++)
		if( m_StoneList[i].BeKilled(col, row))
			return TRUE;
	return FALSE;
}
// ����Ƿ�ԶԷ�����
int CMyWnd::KillEnemy(int col, int row, BOOL red)
{
	int from = red?16:0;
	// ������Է������Ƿ񱻳�
	for(int i=from; i<from+16; i++)
		if( m_StoneList[i].BeKilled(col, row))
			return i;
	return -1;
}
// Ӧ�ó�����
class CMyApp: public CWinApp
{
public:
	BOOL	InitInstance();
};
// Ӧ�ó������ʵ����ʼ������
BOOL CMyApp::InitInstance()
{
	CMyWnd *pFrame = new CMyWnd;
	pFrame->Create(0,_T("�й��������"));
	pFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pFrame->UpdateWindow(); 
	this->m_pMainWnd = pFrame;
	return TRUE;
}
// Ӧ�ó������ȫ�ֶ���
CMyApp ThisApp;