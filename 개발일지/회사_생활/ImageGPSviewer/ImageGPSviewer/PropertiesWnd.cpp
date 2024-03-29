
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
	/*CString propName = pProp->GetName();
	COleVariant propValue = pProp->GetValue();
	
	if (propName == _T("위도"))
	{
		CImageGPSviewerView* test = static_cast<CImageGPSviewerView* const>(AfxGetMainWnd());
		propValue = test->ground_meta.at<double>(0, 0);
		pProp->SetValue(propValue);
	}
	
	m_wndPropList.UpdateWindow();*/
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
	POSITION templatePos = AfxGetApp()->GetFirstDocTemplatePosition();
	if (templatePos == nullptr)
		return;

	CDocTemplate* pTemplate = AfxGetApp()->GetNextDocTemplate(templatePos);
	if (pTemplate == nullptr)
		return;
	
	POSITION docPos = pTemplate->GetFirstDocPosition();
	if (docPos == nullptr)
		return;

	CImageGPSviewerDoc* pDocument = static_cast<CImageGPSviewerDoc*>(pTemplate->GetNextDoc(docPos));
	if (pDocument == nullptr)
		return;

	// GPS
	CMFCPropertyGridProperty* GPS_prop = m_wndPropList.GetProperty(0);
	if (GPS_prop == nullptr)
		return;
	//const COleVariant gpsinfo[3]
	//{
	//	pDocument->ground_meta.at<double>(0, 0),
	//	pDocument->ground_meta.at<double>(1, 0),
	//	pDocument->ground_meta.at<double>(2, 0)
	//};
	//GPS_prop->GetSubItem(0)->SetValue(gpsinfo[0]);
	//GPS_prop->GetSubItem(1)->SetValue(gpsinfo[1]);
	//GPS_prop->GetSubItem(2)->SetValue(gpsinfo[2]);
	for (int i = 0; i < GPS_prop->GetSubItemsCount(); ++i)
	{
		double value = pDocument->ground_meta.at<double>(i, 0);
		COleVariant propValue(value);
		GPS_prop->GetSubItem(i)->SetValue(propValue);
	}
	
	// 이미지 크기
	CMFCPropertyGridProperty* Img_prop = m_wndPropList.GetProperty(1);
	if (Img_prop == nullptr)
		return;
	
	for (int i = 0; i < Img_prop->GetSubItemsCount(); ++i)
	{
		double value = pDocument->ground_meta.at<double>(i, 0);
		COleVariant propValue(value);
		GPS_prop->GetSubItem(i)->SetValue(propValue);
	}

	m_wndPropList.UpdateWindow();
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


	// 지상 좌표
	CMFCPropertyGridProperty* pRealPos = new CMFCPropertyGridProperty(_T("GPS"));
	pRealPos->AddSubItem(new CMFCPropertyGridProperty(_T("위도"), (_variant_t)0.0, _T("")));
	pRealPos->AddSubItem(new CMFCPropertyGridProperty(_T("경도"), (_variant_t)0.0, _T("")));
	pRealPos->AddSubItem(new CMFCPropertyGridProperty(_T("고도"), (_variant_t)0.0, _T("")));

	m_wndPropList.AddProperty(pRealPos);

	// 영상 좌표
	/*CMFCPropertyGridProperty* pVideoPos = new CMFCPropertyGridProperty(_T("영상 좌표"));
	pVideoPos->AddSubItem(new CMFCPropertyGridProperty(_T("X"), (_variant_t)0l, _T("")));
	pVideoPos->AddSubItem(new CMFCPropertyGridProperty(_T("Y"), (_variant_t)0l, _T("")));*/
	//pVideoPos->AddSubItem(new CMFCPropertyGridProperty(_T("고도"), (_variant_t)0l, _T("")));

	//m_wndPropList.AddProperty(pVideoPos);

	// 사진 좌표
	/*CMFCPropertyGridProperty* pImgPos = new CMFCPropertyGridProperty(_T("사진 좌표"));
	pImgPos->AddSubItem(new CMFCPropertyGridProperty(_T("X"), (_variant_t)0l, _T("")));
	pImgPos->AddSubItem(new CMFCPropertyGridProperty(_T("Y"), (_variant_t)0l, _T("")));*/
	//pImgPos->AddSubItem(new CMFCPropertyGridProperty(_T("고도"), (_variant_t)0l, _T("")));

	//m_wndPropList.AddProperty(pImgPos);

	// 이미지 크기
	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("이미지 크기"));
	pSize->AddSubItem(new CMFCPropertyGridProperty(_T("너비"), (_variant_t)0l, _T("")));
	pSize->AddSubItem(new CMFCPropertyGridProperty(_T("높이"), (_variant_t)0l, _T("")));
	pSize->AddSubItem(new CMFCPropertyGridProperty(_T("수평 해상도"), (_variant_t)0l, _T("")));
	pSize->AddSubItem(new CMFCPropertyGridProperty(_T("수직 해상도"), (_variant_t)0l, _T("")));
	pSize->AddSubItem(new CMFCPropertyGridProperty(_T("비트 수준"), (_variant_t)0l, _T("")));
	
	m_wndPropList.AddProperty(pSize);
	
	// 이미지 속성
	CMFCPropertyGridProperty* pProperty = new CMFCPropertyGridProperty(_T("이미지 속성"));
	pProperty->AddSubItem(new CMFCPropertyGridProperty(_T("파일 이름"), _T("")));
	pProperty->AddSubItem(new CMFCPropertyGridProperty(_T("확장자"), _T("")));
	pProperty->AddSubItem(new CMFCPropertyGridProperty(_T("폴더 경로"), _T("")));

	m_wndPropList.AddProperty(pProperty);
	
	for (int i = 0; i < m_wndPropList.GetPropertyCount(); ++i)
	{
		CMFCPropertyGridProperty* prop = m_wndPropList.GetProperty(i);
		if (prop == nullptr)
			break;

		for (int j = 0; j < prop->GetSubItemsCount(); ++j)
		{
			CMFCPropertyGridProperty* sub_prop = prop->GetSubItem(j);
			if (sub_prop == nullptr)
				break;

			prop_mp.insert({ sub_prop->GetName(), j });
		}
	}
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
