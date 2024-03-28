
// ImageGPSviewerDoc.cpp: CImageGPSviewerDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageGPSviewer.h"
#endif

#include "ImageGPSviewerDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageGPSviewerDoc

IMPLEMENT_DYNCREATE(CImageGPSviewerDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageGPSviewerDoc, CDocument)
END_MESSAGE_MAP()


// CImageGPSviewerDoc 생성/소멸

CImageGPSviewerDoc::CImageGPSviewerDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImageGPSviewerDoc::~CImageGPSviewerDoc()
{
}

/** convert_rational_to_decimal
* @brief	- 분수로 소수점 전환
* @param	- rational 경도 or 위도
*/
double CImageGPSviewerDoc::convert_rational_to_decimal(const Exiv2::Rational& rational)
{
	if (rational.second == 0)
		return 0.0;
	return static_cast<double>(rational.first) / static_cast<double>(rational.second);
}

/** convert_gps_lon_lat
* @brief	- 경도, 위도 십진수로 전환
* @param	- value 경도 or 위도 메타데이터
*/
double CImageGPSviewerDoc::convert_gps_lon_lat(const Exiv2::Value& value)
{
	const double degrees = convert_rational_to_decimal(value.toRational(0));
	const double minutes = convert_rational_to_decimal(value.toRational(1));
	const double seconds = convert_rational_to_decimal(value.toRational(2));

	return degrees + minutes / 60.0 + seconds / 3600.0;
}

/** convert_gps_alt
* @brief	- 고도 double로 변환
* @param	- value 고도
*/
double CImageGPSviewerDoc::convert_gps_alt(const Exiv2::Value& value)
{
	const double altitude = convert_rational_to_decimal(value.toRational(0));

	return altitude;
}

/** meta_transform
* @brief	- proj 라이브러리(9.x.x 버전 이상)을 사용하여 메타데이터의 위/경도 좌표를 EPSG:5186으로 변환한다.
* @param	- 메타데이터 std::span<double>
* @return	- 경도, 위도, 고도
*/
std::array<double, 3> CImageGPSviewerDoc::meta_transform(const std::span<double>& s)
{
	if (s[0] == 0 && s[1] == 0 && s[2] == 0)
		return { 0,0,0 };

	std::unique_ptr<PJ_CONTEXT, decltype((void(*)(PJ_CONTEXT*))(proj_context_destroy))> ctx(proj_context_create(), (void(*)(PJ_CONTEXT*))(proj_context_destroy));
	std::shared_ptr<PJ> trans_obj
	(
		proj_create_crs_to_crs
		(
			ctx.get(),
			"+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs",
			"+proj=tmerc +lat_0=38 +lon_0=127 +k=1 +x_0=200000 +y_0=600000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs",
			nullptr
		),
		proj_destroy
	);
	// from src to dst
	PJ_COORD from = proj_coord(s[1], s[0], s[2], 0.0); //경도, 위도, 고도
	PJ_COORD to = proj_trans(trans_obj.get(), PJ_DIRECTION::PJ_FWD, from);

	return { to.xyz.x, to.xyz.y, to.xyz.z };
}

/** read_meta_data
* @brief		- 이미지 경로를 받아 메타데이터를 읽어온 후 변환한다.
* @param	- img_path 이미지 경로
* @return	- cur_value 위도, 경도, 고도
*/
std::array<double, 3> CImageGPSviewerDoc::read_meta_data(const std::string& img_path)
{
	const std::unique_ptr<Exiv2::Image> image = Exiv2::ImageFactory::open(img_path);

	image->readMetadata();

	const Exiv2::ExifData& exifData = image->exifData();

	std::array<double, 3> cur_value{};
	int num = 0;
	for (const auto& data : exifData)
	{
		if (data.tagName() == "GPSLatitude" || data.tagName() == "GPSLongitude")
		{
			const Exiv2::Value& value = data.value();
			cur_value[num] = convert_gps_lon_lat(value);
			num++;
			continue;
		}
		if (data.tagName() == "GPSAltitude")
		{
			const Exiv2::Value& value = data.value();
			cur_value[num] = convert_gps_alt(value);
		}
	}

	return cur_value;
}

BOOL CImageGPSviewerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageGPSviewerDoc serialization

void CImageGPSviewerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageGPSviewerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImageGPSviewerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageGPSviewerDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageGPSviewerDoc 진단

#ifdef _DEBUG
void CImageGPSviewerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageGPSviewerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageGPSviewerDoc 명령

