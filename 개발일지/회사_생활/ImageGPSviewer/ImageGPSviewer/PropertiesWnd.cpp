
#include "pch.h"
#include "framework.h"

#include "ImageGPSviewer.h"
#include "ImageGPSviewerView.h"
#include "ImageGPSviewerDoc.h"
#include "MainFrm.h"
#include "PropertiesWnd.h"
#include "Resource.h"

#include <exiv2/exiv2.hpp>
#include <opencv2/opencv.hpp>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd() noexcept :
	m_nComboHeight(0)
{
	//m_nComboHeight = 0;
}

//CPropertiesWnd::~CPropertiesWnd()
//{
//}

void CPropertiesWnd::OnPropertyChanged(CMFCPropertyGridProperty* pProp)
{
	
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_WM_MOUSEMOVE()
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar 메시지 처리기

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd () == nullptr || (AfxGetMainWnd() != nullptr && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	//int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndObjectCombo.SetWindowPos(nullptr, rectClient.left, rectClient.top, rectClient.Width(), m_nComboHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	//m_wndToolBar.SetWindowPos(nullptr, rectClient.left, rectClient.top + m_nComboHeight, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(nullptr, rectClient.left, rectClient.top + m_nComboHeight, rectClient.Width(), rectClient.Height() -(m_nComboHeight), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 콤보 상자를 만듭니다.
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("속성 콤보 상자를 만들지 못했습니다. \n");
		return -1;      // 만들지 못했습니다.
	}

	//m_wndObjectCombo.AddString(_T("애플리케이션"));
	m_wndObjectCombo.AddString(_T("속성 창"));
	m_wndObjectCombo.SetCurSel(0);

	CRect rectCombo;
	m_wndObjectCombo.GetClientRect (&rectCombo);

	m_nComboHeight = rectCombo.Height();

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("속성 표를 만들지 못했습니다. \n");
		return -1;      // 만들지 못했습니다.
	}

	InitPropList();

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* 잠금 */);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* 잠금 */);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// 모든 명령은 부모 프레임이 아닌 이 컨트롤을 통해 라우팅됩니다.
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* pCmdUI)
{
	// 영상 좌표
	CMFCPropertyGridProperty* video_prop = m_wndPropList.GetProperty(0);
	const COleVariant video_info[2]
	{
		COleVariant(CComBSTR(std::to_string(mouse_video_pos_x).c_str())),
		COleVariant(CComBSTR(std::to_string(mouse_video_pos_y).c_str())),
	};
	video_prop->GetSubItem(0)->SetValue(mouse_video_pos_x != 0 ? video_info[0] : _T("out of range"));
	video_prop->GetSubItem(1)->SetValue(mouse_video_pos_x != 0 ? video_info[1] : _T("out of range"));

	// 사진 좌표
	CMFCPropertyGridProperty* img_pos_prop = m_wndPropList.GetProperty(1);
	const COleVariant img_pos_info[2]
	{
		COleVariant(CComBSTR(std::to_string(mouse_img_pos_x).c_str())),
		COleVariant(CComBSTR(std::to_string(mouse_img_pos_y).c_str())),
	};
	img_pos_prop->GetSubItem(0)->SetValue(mouse_video_pos_x != 0 ? img_pos_info[0] : _T("out of range"));
	img_pos_prop->GetSubItem(1)->SetValue(mouse_video_pos_x != 0 ? img_pos_info[1] : _T("out of range"));

	// 지상 좌표
	CMFCPropertyGridProperty* real_pos_prop = m_wndPropList.GetProperty(2);
	const COleVariant real_pos_info[3]
	{
		COleVariant(CComBSTR(std::to_string(mouse_real_pos_x).c_str())),
		COleVariant(CComBSTR(std::to_string(mouse_real_pos_y).c_str())),
		COleVariant(CComBSTR(std::to_string(mouse_real_pos_z).c_str()))
	};
	real_pos_prop->GetSubItem(0)->SetValue(mouse_video_pos_x != 0 ? real_pos_info[0] : _T("out of range"));
	real_pos_prop->GetSubItem(1)->SetValue(mouse_video_pos_x != 0 ? real_pos_info[1] : _T("out of range"));
	real_pos_prop->GetSubItem(2)->SetValue(mouse_video_pos_x != 0 ? real_pos_info[2] : _T("out of range"));
	if (!is_mouse_view_out)
	{
		COleVariant varValue = real_pos_prop->GetSubItem(3)->GetValue();
		VARIANT destVal;
		VariantInit(&destVal);
		HRESULT hr = VariantChangeType(&destVal, &varValue, 0, VT_R8);
		set_altitude = V_R8(&destVal);
		VariantClear(&destVal);
	}

	// 방위각
	CMFCPropertyGridProperty* azimuth_prop = m_wndPropList.GetProperty(3);
	const COleVariant azimuth_info[5]
	{
		COleVariant(CComBSTR(std::to_string(pre_mouse_real_pos_x).c_str())),
		COleVariant(CComBSTR(std::to_string(pre_mouse_real_pos_y).c_str())),
		COleVariant(CComBSTR(std::to_string(cur_mouse_real_pos_x).c_str())),
		COleVariant(CComBSTR(std::to_string(cur_mouse_real_pos_y).c_str())),
		COleVariant(CComBSTR(std::to_string(azimuth).c_str()))
	};
	azimuth_prop->GetSubItem(0)->SetValue(mouse_video_pos_x != 0 ? azimuth_info[0] : _T("out of range"));
	azimuth_prop->GetSubItem(1)->SetValue(mouse_video_pos_x != 0 ? azimuth_info[1] : _T("out of range"));
	azimuth_prop->GetSubItem(2)->SetValue(mouse_video_pos_x != 0 ? azimuth_info[2] : _T("out of range"));
	azimuth_prop->GetSubItem(3)->SetValue(mouse_video_pos_x != 0 ? azimuth_info[3] : _T("out of range"));
	azimuth_prop->GetSubItem(4)->SetValue(mouse_video_pos_x != 0 ? azimuth_info[4] : _T("out of range"));

	if (is_view_changed && !is_mouse_view_out)
		return;

	CMDIFrameWnd* pMainFrame = static_cast<CMDIFrameWnd*>(AfxGetMainWnd()->GetActiveWindow());
	if (pMainFrame == nullptr)
		return;

	CMDIChildWnd* pChild = pMainFrame->MDIGetActive();
	if (pChild == nullptr)
		return;

	CView* pView = pChild->GetActiveView();
	if (pView == nullptr)
		return;

	CImageGPSviewerDoc* pDocument = static_cast<CImageGPSviewerDoc*>(pView->GetDocument());
	if (pDocument == nullptr)
		return;

	// GPS
	CMFCPropertyGridProperty* GPS_prop = m_wndPropList.GetProperty(5);
	if (GPS_prop == nullptr)
		return;

	const COleVariant gpsinfo_4326[3]
	{
		pDocument->meta_data[0],
		pDocument->meta_data[1],
		pDocument->meta_data[2],
	};
	const COleVariant gpsinfo_5186[3]
	{
		pDocument->ground_meta.at<double>(0, 0),
		pDocument->ground_meta.at<double>(1, 0),
		pDocument->ground_meta.at<double>(2, 0)
	};
	if (GPS_prop->GetSubItem(0)->GetValue() == _T("4326"))
	{
		GPS_prop->GetSubItem(1)->SetValue(gpsinfo_4326[0]);
		GPS_prop->GetSubItem(1)->SetName(_T("위도"));
		GPS_prop->GetSubItem(2)->SetValue(gpsinfo_4326[1]);
		GPS_prop->GetSubItem(2)->SetName(_T("경도"));
		GPS_prop->GetSubItem(3)->SetValue(gpsinfo_4326[2]);
		GPS_prop->GetSubItem(3)->SetName(_T("고도"));
	}
	else if (GPS_prop->GetSubItem(0)->GetValue() == _T("5186"))
	{
		GPS_prop->GetSubItem(1)->SetValue(gpsinfo_5186[0]);
		GPS_prop->GetSubItem(1)->SetName(_T("X"));
		GPS_prop->GetSubItem(2)->SetValue(gpsinfo_5186[1]);
		GPS_prop->GetSubItem(2)->SetName(_T("Y"));
		GPS_prop->GetSubItem(3)->SetValue(gpsinfo_5186[2]);
		GPS_prop->GetSubItem(3)->SetName(_T("Z"));
	}

	// 이미지
	CMFCPropertyGridProperty* img_prop = m_wndPropList.GetProperty(6);
	if (img_prop == nullptr)
		return;

	const COleVariant img_info[7]
	{
		(_variant_t)pDocument->img_width,
		(_variant_t)pDocument->img_height,
		focal_length,
		pixel_size,
		(_variant_t)pDocument->GetTitle(),
		_T(".jpg"),
		(_variant_t)pDocument->image_path
	};
	img_prop->GetSubItem(0)->SetValue(img_info[0]);
	img_prop->GetSubItem(1)->SetValue(img_info[1]);
	
	COleVariant varValue_focal = img_prop->GetSubItem(2)->GetValue();
	COleVariant varValue_pixel = img_prop->GetSubItem(3)->GetValue();
	VARIANT destVal;
	VARIANT destVal2;
	VariantInit(&destVal);
	VariantInit(&destVal2);
	HRESULT focal_hr = VariantChangeType(&destVal, &varValue_focal, 0, VT_R8);
	HRESULT pixel_hr = VariantChangeType(&destVal2, &varValue_pixel, 0, VT_R8);

	focal_length = V_R8(&destVal);
	pixel_size = V_R8(&destVal2);
	
	img_prop->GetSubItem(4)->SetValue(img_info[4]);
	img_prop->GetSubItem(5)->SetValue(img_info[5]);
	img_prop->GetSubItem(6)->SetValue(img_info[6]);
	
	VariantClear(&destVal);
	VariantClear(&destVal2);

	is_view_changed = true;
}

void CPropertiesWnd::OnSortProperties()
{
	//m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	//pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnProperties1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CPropertiesWnd::InitPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	// 영상 좌표
	CMFCPropertyGridProperty* pVideoPos = new CMFCPropertyGridProperty(_T("영상 좌표(*마우스 기준)"));
	pVideoPos->AddSubItem(new CMFCPropertyGridProperty(_T("X"), _T(""), _T("")));
	pVideoPos->AddSubItem(new CMFCPropertyGridProperty(_T("Y"), _T(""), _T("")));
	pVideoPos->GetSubItem(0)->AllowEdit(FALSE);
	pVideoPos->GetSubItem(1)->AllowEdit(FALSE);
	//pVideoPos->AddSubItem(new CMFCPropertyGridProperty(_T("고도"), (_variant_t)0l, _T("")));

	m_wndPropList.AddProperty(pVideoPos);

	// 사진 좌표
	CMFCPropertyGridProperty* pImgPos = new CMFCPropertyGridProperty(_T("사진 좌표(*마우스 기준)"));
	pImgPos->AddSubItem(new CMFCPropertyGridProperty(_T("X"), _T(""), _T("")));
	pImgPos->AddSubItem(new CMFCPropertyGridProperty(_T("Y"), _T(""), _T("")));
	pImgPos->GetSubItem(0)->AllowEdit(FALSE);
	pImgPos->GetSubItem(1)->AllowEdit(FALSE);

	//pImgPos->AddSubItem(new CMFCPropertyGridProperty(_T("고도"), (_variant_t)0l, _T("")));

	m_wndPropList.AddProperty(pImgPos);

	// 지상 좌표
	CMFCPropertyGridProperty* pRealPos = new CMFCPropertyGridProperty(_T("지상 좌표(*마우스 기준)"));
	pRealPos->AddSubItem(new CMFCPropertyGridProperty(_T("X"), _T(""), _T("")));
	pRealPos->AddSubItem(new CMFCPropertyGridProperty(_T("Y"), _T(""), _T("")));
	pRealPos->AddSubItem(new CMFCPropertyGridProperty(_T("Z"), _T(""), _T("")));
	pRealPos->AddSubItem(new CMFCPropertyGridProperty(_T("* 고정 고도 설정"), (_variant_t)0.0, _T("")));
	pRealPos->GetSubItem(0)->AllowEdit(FALSE);
	pRealPos->GetSubItem(1)->AllowEdit(FALSE);
	pRealPos->GetSubItem(2)->AllowEdit(FALSE);

	m_wndPropList.AddProperty(pRealPos);

	// 방위각
	CMFCPropertyGridProperty* pAzimuth = new CMFCPropertyGridProperty(_T("방위각( A to B )"));
	pAzimuth->AddSubItem(new CMFCPropertyGridProperty(_T("Ax"), _T(""), _T("")));
	pAzimuth->AddSubItem(new CMFCPropertyGridProperty(_T("Ay"), _T(""), _T("")));
	pAzimuth->AddSubItem(new CMFCPropertyGridProperty(_T("Bx"), _T(""), _T("")));
	pAzimuth->AddSubItem(new CMFCPropertyGridProperty(_T("By"), _T(""), _T("")));
	pAzimuth->AddSubItem(new CMFCPropertyGridProperty(_T("각(도)"), _T(""), _T("")));
	pAzimuth->GetSubItem(0)->AllowEdit(FALSE);
	pAzimuth->GetSubItem(1)->AllowEdit(FALSE);
	pAzimuth->GetSubItem(2)->AllowEdit(FALSE);
	pAzimuth->GetSubItem(3)->AllowEdit(FALSE);
	pAzimuth->GetSubItem(4)->AllowEdit(FALSE);

	m_wndPropList.AddProperty(pAzimuth);

	// 빈 칸
	CMFCPropertyGridProperty* pSeparator = new CMFCPropertyGridProperty(_T(" "), (_variant_t)_T(""), _T("이 부분은 시각적으로 구분하기 위한 공간입니다."));
	pSeparator->Enable(FALSE); // 비활성화
	m_wndPropList.AddProperty(pSeparator);
	// 빈 칸


	// 밑에 더블형과 문자열이 충돌중이니까 고쳐라
	// GPS
	CMFCPropertyGridProperty* pGpsPos = new CMFCPropertyGridProperty(_T("GPS"));
	
	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("EPSG"), _T("4326"),_T(""));
	pProp->AddOption(_T("4326"));
	pProp->AddOption(_T("5186"));
	pProp->AllowEdit(FALSE);

	pGpsPos->AddSubItem(pProp);
	pGpsPos->AddSubItem(new CMFCPropertyGridProperty(_T("위도"), (_variant_t)0.0, _T("")));
	pGpsPos->AddSubItem(new CMFCPropertyGridProperty(_T("경도"), (_variant_t)0.0, _T("")));
	pGpsPos->AddSubItem(new CMFCPropertyGridProperty(_T("고도"), (_variant_t)0.0, _T("")));
	pGpsPos->GetSubItem(1)->AllowEdit(FALSE);
	pGpsPos->GetSubItem(2)->AllowEdit(FALSE);
	pGpsPos->GetSubItem(3)->AllowEdit(FALSE);
	
	m_wndPropList.AddProperty(pGpsPos);

	// 이미지
	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("이미지 크기"));
	pSize->AddSubItem(new CMFCPropertyGridProperty(_T("너비"), (_variant_t)0l, _T("")));
	pSize->AddSubItem(new CMFCPropertyGridProperty(_T("높이"), (_variant_t)0l, _T("")));
	pSize->AddSubItem(new CMFCPropertyGridProperty(_T("* 초점 거리"), (_variant_t)0.0, _T("")));
	pSize->AddSubItem(new CMFCPropertyGridProperty(_T("* 픽셀 크기"), (_variant_t)0.0,_T("")));
	pSize->AddSubItem(new CMFCPropertyGridProperty(_T("파일 이름"), _T("")));
	pSize->AddSubItem(new CMFCPropertyGridProperty(_T("확장자"), _T("")));
	pSize->AddSubItem(new CMFCPropertyGridProperty(_T("폴더 경로"), _T("")));
	pSize->GetSubItem(0)->AllowEdit(FALSE);
	pSize->GetSubItem(1)->AllowEdit(FALSE);
	pSize->GetSubItem(4)->AllowEdit(FALSE);
	pSize->GetSubItem(5)->AllowEdit(FALSE);
	pSize->GetSubItem(6)->AllowEdit(FALSE);

	m_wndPropList.AddProperty(pSize);
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();

	/*CMFCPropertyGridCtrl pRealPos = m_wndPropList.;
	OnPropertyChanged(pRealPos);*/
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
	m_wndObjectCombo.SetFont(&m_fntPropList);
}
