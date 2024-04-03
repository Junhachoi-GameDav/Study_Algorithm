
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
#include "PropertiesWnd.h"
#include "MainFrm.h"

// opencv
#include <opencv2/opencv.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageGPSviewerView

IMPLEMENT_DYNCREATE(CImageGPSviewerView, CView)

BEGIN_MESSAGE_MAP(CImageGPSviewerView, CView)
	// 표준 인쇄 명령입니다.
	//ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	//ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	//ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageGPSviewerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
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

	img = cv::imread(str_img_path);

	if (img.empty())
		return;

#pragma region 그리기
	CRect Rect;
	GetClientRect(&Rect);

	float Width = static_cast<float>(Rect.Width());
	float Height = static_cast<float>(Rect.Height());
	float Rate = Width / Height;
	float imgRate = static_cast<float>(img.cols) / img.rows;

	targetWidth;
	targetHeight;

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

	result_x = (Rect.Width() - targetWidth) / 2;
	result_y = (Rect.Height() - targetHeight) / 2;

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
	StretchDIBits(pDC->m_hDC, result_x, result_y, targetWidth, targetHeight, 0, 0, imgBGR.cols, imgBGR.rows,
		imgBGR.data, &bitmapInfo, DIB_RGB_COLORS, SRCCOPY);

#pragma endregion
	
	// 메타데이터 받기
	pDoc->meta_data = pDoc->read_meta_data(str_img_path);
	pDoc->img_meta = pDoc->meta_transform(pDoc->meta_data);
	pDoc->ground_meta = (cv::Mat_<double>(3, 1) << pDoc->img_meta[0], pDoc->img_meta[1], pDoc->img_meta[2]);
	pDoc->img_width = img.cols;
	pDoc->img_height = img.rows;

	CMainFrame* pMainFrame = static_cast<CMainFrame*>(AfxGetMainWnd());
	if (pMainFrame == nullptr)
		return;

	pMainFrame->m_wndProperties.is_view_changed = false;
}

void CImageGPSviewerView::OnMouseMove(UINT nFlags, CPoint point)
{
	CMainFrame* pMainFrame = static_cast<CMainFrame*>(AfxGetMainWnd());
	if (pMainFrame == nullptr)
		return;

	CImageGPSviewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// 마우스 이벤트 추적
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = TME_LEAVE;
	tme.hwndTrack = this->m_hWnd;
	TrackMouseEvent(&tme);

#pragma region 마우스 좌표(영상)
	// 마우스 좌표(영상)
	long& mouse_video_x = pMainFrame->m_wndProperties.mouse_video_pos_x;
	long& mouse_video_y = pMainFrame->m_wndProperties.mouse_video_pos_y;
	
	if (!(point.x >= result_x && point.x <= result_x + targetWidth))
		mouse_video_x = 0;
	
	mouse_video_x = static_cast<long>((point.x - result_x) * (img.cols / static_cast<float>(targetWidth))); //point.x;
	
	if (!(point.y >= result_y && point.y <= result_y + targetHeight))
		mouse_video_y = 0;

	mouse_video_y = static_cast<long>((point.y - result_y) * (img.rows / static_cast<float>(targetHeight))); //point.y;

#pragma endregion

#pragma region 마우스 좌표(사진)
	// 마우스 좌표(사진)
	constexpr double focal_length = 4.8;
	constexpr double pixel_size = 0.0007;
	double f_length = pMainFrame->m_wndProperties.focal_length;
	double p_size = pMainFrame->m_wndProperties.pixel_size;
	const double focal_length_in_pixel = f_length / p_size;
	//const double focal_length_in_pixel = focal_length / pixel_size;

	long& mouse_img_x = pMainFrame->m_wndProperties.mouse_img_pos_x;
	long& mouse_img_y = pMainFrame->m_wndProperties.mouse_img_pos_y;
	
	const cv::Mat vision_to_photo = (cv::Mat_<double>(3, 3) <<
		1.0, 0.0, -(img.cols / 2),
		0.0, -1.0, (img.rows / 2),
		0.0, 0.0, -focal_length_in_pixel);

	cv::Mat_<double> pos = (cv::Mat_<double>(3, 1) <<
		static_cast<double>(mouse_video_x),
		static_cast<double>(mouse_video_y),
		1.0);

	const cv::Mat photo_points = vision_to_photo * pos;

	mouse_img_x = static_cast<long>(photo_points.at<double>(0, 0));
	mouse_img_y = static_cast<long>(photo_points.at<double>(1, 0));

#pragma endregion

#pragma region 마우스 좌표(지상)
	// 마우스 좌표(지상)
	double& mouse_real_x = pMainFrame->m_wndProperties.mouse_real_pos_x;
	double& mouse_real_y = pMainFrame->m_wndProperties.mouse_real_pos_y;
	double& mouse_real_z = pMainFrame->m_wndProperties.mouse_real_pos_z;
	
	// 람다
	double& Altitude = pMainFrame->m_wndProperties.set_altitude;
	//constexpr double Altitude = 20;
	double lambda = photo_points.at<double>(2, 0) / (Altitude - pDoc->ground_meta.at<double>(2, 0));

	cv::Mat real_pos = photo_points / lambda;

	real_pos += pDoc->ground_meta;

	mouse_real_x = real_pos.at<double>(0, 0);
	mouse_real_y = real_pos.at<double>(1, 0);
	mouse_real_z = pDoc->ground_meta.at<double>(2, 0) -real_pos.at<double>(2, 0);

#pragma endregion

	if (pDoc->previous_Ellipse.PtInRect(point))
	{
		ClientToScreen(&point);
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, FALSE);
	}
	//::PostMessage(this->m_hWnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(-1, -1));
	

	pMainFrame->m_wndProperties.UpdateWindow();
	pMainFrame->m_wndProperties.is_mouse_out = false;

	CView::OnMouseMove(nFlags, point);
}

void CImageGPSviewerView::OnMouseLeave()
{
	CMainFrame* pMainFrame = static_cast<CMainFrame*>(AfxGetMainWnd());
	if (pMainFrame == nullptr)
		return;

	pMainFrame->m_wndProperties.mouse_video_pos_x = 0;
	pMainFrame->m_wndProperties.mouse_video_pos_y = 0;
	pMainFrame->m_wndProperties.mouse_img_pos_x = 0;
	pMainFrame->m_wndProperties.mouse_img_pos_y = 0;
	pMainFrame->m_wndProperties.mouse_real_pos_x = 0;
	pMainFrame->m_wndProperties.mouse_real_pos_y = 0;
	pMainFrame->m_wndProperties.mouse_real_pos_z = 0;

	pMainFrame->m_wndProperties.UpdateWindow();
	pMainFrame->m_wndProperties.is_mouse_out = true;
	CView::OnMouseLeave();
}

void CImageGPSviewerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CImageGPSviewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	pDoc->m_points.Add(point);
	CDC* pDC = GetDC();

	for (int i = 0; i < pDoc->m_points.GetSize(); i++)
	{
		CPoint pt = pDoc->m_points[i];
		pDC->Ellipse(
			pt.x - pDoc->dot_size, 
			pt.y - pDoc->dot_size, 
			pt.x + pDoc->dot_size, 
			pt.y + pDoc->dot_size);
		CRect ellipseRect(
			pt.x - pDoc->dot_size * 2, 
			pt.y - pDoc->dot_size * 2, 
			pt.x + pDoc->dot_size * 2, 
			pt.y + pDoc->dot_size * 2);
		pDoc->previous_Ellipse = ellipseRect;
	}

	ReleaseDC(pDC);
	CView::OnLButtonDown(nFlags, point);
}

//void CImageGPSviewerView::OnLButtonUp(UINT nFlags, CPoint point)
//{
//	CImageGPSviewerDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
//	if (!pDoc)
//		return;
//
//	pDoc->is_Dragging = false;
//	CDC* pDC = GetDC();
//	pDC->MoveTo(pDoc->previous_pt);  // 이전 위치로 이동
//	pDC->LineTo(point);         // 마지막 점까지 선 그리기
//	ReleaseDC(pDC);
//
//	CView::OnLButtonUp(nFlags, point);
//}

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
