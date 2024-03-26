
// Image_GPS_viewerView.cpp: CImageGPSviewerView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Image_GPS_viewer.h"
#endif

#include "Image_GPS_viewerDoc.h"
#include "Image_GPS_viewerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageGPSviewerView

IMPLEMENT_DYNCREATE(CImageGPSviewerView, CView)

BEGIN_MESSAGE_MAP(CImageGPSviewerView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageGPSviewerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CImageGPSviewerView 생성/소멸

CImageGPSviewerView::CImageGPSviewerView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageGPSviewerView::~CImageGPSviewerView()
{
}

BOOL CImageGPSviewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CImageGPSviewerView 그리기

void CImageGPSviewerView::OnDraw(CDC* pDC)
{
	CImageGPSviewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	CImage img;
	//img.Create(640, 480, 8);
	
	CImageGPSviewerApp* pApp = static_cast<CImageGPSviewerApp*>(AfxGetApp());
	
	if (pApp == nullptr)
		return;

	HRESULT hr = img.Load(pApp->Cimg_path);
	
	if ( hr != S_OK || pApp->Cimg_path == "")
		return;

	//img.Create(img.GetWidth(), img.GetHeight(), 8);

	CClientDC dc(this);
	img.Draw(dc, 0, 0);
	//pApp->Cimg_path = "";
}


// CImageGPSviewerView 인쇄


void CImageGPSviewerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageGPSviewerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageGPSviewerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageGPSviewerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CImageGPSviewerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageGPSviewerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CImage img;
	img.Create(640, 480, 8);
	CClientDC dc(this);
	img.Draw(dc, 0, 0);
	CView::OnLButtonDown(nFlags, point);
}

void CImageGPSviewerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageGPSviewerView 진단

#ifdef _DEBUG
void CImageGPSviewerView::AssertValid() const
{
	CView::AssertValid();
}

void CImageGPSviewerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageGPSviewerDoc* CImageGPSviewerView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageGPSviewerDoc)));
	return (CImageGPSviewerDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageGPSviewerView 메시지 처리기
