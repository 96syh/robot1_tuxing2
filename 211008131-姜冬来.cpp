
// MFCApplicationView.cpp: CMFCApplicationView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication.h"
#endif

#include "MFCApplicationDoc.h"
#include "MFCApplicationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplicationView

IMPLEMENT_DYNCREATE(CMFCApplicationView, CView)

BEGIN_MESSAGE_MAP(CMFCApplicationView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApplicationView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CMFCApplicationView 构造/析构

CMFCApplicationView::CMFCApplicationView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMFCApplicationView::~CMFCApplicationView()
{
}

BOOL CMFCApplicationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCApplicationView 绘图

void CMFCApplicationView::OnDraw(CDC* /*pDC*/)
{
	CMFCApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCApplicationView 打印


void CMFCApplicationView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApplicationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCApplicationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCApplicationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMFCApplicationView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApplicationView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplicationView 诊断

#ifdef _DEBUG
void CMFCApplicationView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplicationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplicationDoc* CMFCApplicationView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplicationDoc)));
	return (CMFCApplicationDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplicationView 消息处理程序


void CMFCApplicationView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	P0 = point;
	CView::OnLButtonDown(nFlags, point);
}


void CMFCApplicationView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	P0 = point;
	CClientDC du(this);  //获得一个指向当前画板的句柄（可以理解为笔杆子）du为自定义变量。
	//du.SetPixel(point,RGB(255,0,0));  //这句已经被注释掉
	   //du.MoveTo(m_point1);   //画笔先移动到了鼠标点击下去的点。这是线的起点。
	   //du.LineTo(m_point2);  //以鼠标释放的点为终点，画出一条直线。
	du.Rectangle(P0.x, P0.y, P1.x, P1.y);//这里变量后的.x表示点的x轴坐标， .y表示点的y轴坐标。
	CBrush brush0(RGB(0, 0, 0));      //新建一个画刷，利用RGB设置颜色，这里是黑色。
	du.SelectObject(&brush0);		//选入画刷，表示使用这个画刷。


	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int Ox = 200;			//棋盘左上角的x轴起点
	int Oy = 100;      //棋盘左上角的y轴起点
	int numx = 11;		//直线列数
	int numy = 11;		//直线行数
	int bulk = 50;		//棋盘每个格子大小，设置变量是为了后续的交互式改变大小
	for (int i = 0; i < numx; i++)//画列线
	{
		du.MoveTo(Ox + bulk * i, Oy);
		du.LineTo(Ox + bulk * i, bulk * 10 + Oy);
	}
	for (int j = 0; j < numy; j++)//画行线
	{
		du.MoveTo(Ox, Oy + bulk * j);
		du.LineTo(Ox + bulk * 10, Oy + bulk * j);
	}
	CString str;
	for (int i = 10; i > 0; i--)
	{
		str.Format(_T("%d"), i);
		du.TextOut(Ox - 30, bulk * 10 + 100 - bulk / 2 - (bulk * (i - 1)), str);
	}
	char b[] = { 'A','B','C','D','E','F','G','H','I','J' };
	for (int j = 1; j < 11; j++)
	{
		str.Format(_T("%c"), b[j - 1]);
		du.TextOut(Ox + bulk / 2 + bulk * (j - 1), Oy - 30, str);
	}
	for (int n = 0; n < 10; n = n + 1)
	{

		for (int m = 0; m < 10; m = m + 2)
		{
			CRect rc(Ox + bulk * m, Oy + n * bulk, Ox + bulk * m + bulk, Oy + n * bulk + bulk);      //分别是起点的x轴坐标，y轴坐标终点的x轴坐标，y轴坐标。
			if (n % 2 == 0)
			{
				du.FillRect(rc, &brush0);							//表示填充颜色。rc表示填充的区域。brush0表示填充区域所用的画刷。
			}
		}
	}

	for (int n = 1; n < 11; n = n + 1)
	{

		for (int m = 1; m < 11; m = m + 2)
		{

			if (n % 2 != 0)
			{
				CRect rc(Ox + bulk * m, Oy + n * bulk, Ox + bulk * m + bulk, Oy + n * bulk + bulk);      //同上方。
				du.FillRect(rc, &brush0);
			}

		}
	}

}
