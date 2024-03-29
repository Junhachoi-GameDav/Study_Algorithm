
// ImageGPSviewerView.cpp: CImageGPSviewerView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageGPSviewer.h"
#endif

#include "ImageGPSviewerDoc.h"
#include "ImageGPSviewerView.h"
#include "FileView.h"

// opencv
#include <opencv2/opencv.hpp>

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
END_MESSAGE_MAP()

// CImageGPSviewerView 생성/소멸

CImageGPSviewerView::CImageGPSviewerView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
}

//CImageGPSviewerView::~CImageGPSviewerView()
//{
//}

//BOOL CImageGPSviewerView::PreCreateWindow(CREATESTRUCT& cs)
//{
//	// TODO: CREATESTRUCT cs를 수정하여 여기에서
//	//  Window 클래스 또는 스타일을 수정합니다.
//
//	return CView::PreCreateWindow(cs);
//}

// CImageGPSviewerView 그리기

void CImageGPSviewerView::OnDraw(CDC* pDC)
{
	CImageGPSviewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CString str_temp(pDoc->image_path);
	std::string str_img_path(CW2A(str_temp.GetString()));

	cv::Mat img = cv::imread(str_img_path);

	if (img.empty())
		return;

#pragma region 그리기
	CRect Rect;
	GetClientRect(&Rect);

	float Width = static_cast<float>(Rect.Width());
	float Height = static_cast<float>(Rect.Height());
	float Rate = Width / Height;
	float imgRate = static_cast<float>(img.cols) / img.rows;

	int targetWidth;
	int targetHeight;

	if (imgRate > Rate)
	{
		targetWidth = static_cast<int>(Width);
		targetHeight = static_cast<int>(targetWidth / imgRate);
	}
	else
	{
		targetHeight = static_cast<int>(Height);
		targetWidth = static_cast<int>(targetHeight * imgRate);
	}

	int x = (Rect.Width() - targetWidth) / 2;
	int y = (Rect.Height() - targetHeight) / 2;

	// 이미지 크기 조정
	cv::Mat resizedImg;
	cv::resize(img, resizedImg, cv::Size(targetWidth, targetHeight)); 

	// MFC 호환을 위해 색상 공간 변경
	cv::Mat imgBGR;
	cv::cvtColor(resizedImg, imgBGR, cv::COLOR_BGR2BGRA); 

	BITMAPINFO bitmapInfo;
	memset(&bitmapInfo, 0, sizeof(bitmapInfo));
	bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfo.bmiHeader.biWidth = imgBGR.cols;
	bitmapInfo.bmiHeader.biHeight = -imgBGR.rows; // 상단에서 하단으로 그리기
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biBitCount = 32;
	bitmapInfo.bmiHeader.biCompression = BI_RGB;

	// OpenCV 이미지를 MFC CDC에 그리기
	StretchDIBits(pDC->m_hDC, x, y, targetWidth, targetHeight, 0, 0, imgBGR.cols, imgBGR.rows,
		imgBGR.data, &bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
#pragma endregion

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	
	// 메타데이터 받기
	pDoc->meta_data = pDoc->read_meta_data(str_img_path);
	pDoc->img_meta = pDoc->meta_transform(pDoc->meta_data);
	pDoc->ground_meta = (cv::Mat_<double>(3, 1) << pDoc->img_meta[0], pDoc->img_meta[1], pDoc->img_meta[2]);


}


// CImageGPSviewerView 인쇄

//
//void CImageGPSviewerView::OnFilePrintPreview()
//{
//#ifndef SHARED_HANDLERS
//	AFXPrintPreview(this);
//#endif
//}
//
//BOOL CImageGPSviewerView::OnPreparePrinting(CPrintInfo* pInfo)
//{
//	// 기본적인 준비
//	return DoPreparePrinting(pInfo);
//}
//
//void CImageGPSviewerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
//{
//	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
//}
//
//void CImageGPSviewerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
//{
//	// TODO: 인쇄 후 정리 작업을 추가합니다.
//}

void CImageGPSviewerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
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
