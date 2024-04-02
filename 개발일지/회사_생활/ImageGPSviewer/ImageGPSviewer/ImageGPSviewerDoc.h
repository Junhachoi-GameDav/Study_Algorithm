
// ImageGPSviewerDoc.h: CImageGPSviewerDoc 클래스의 인터페이스
//


#pragma once
#include "pch.h"
#include <span>

// Proj
#include <proj.h>

// opencv
#include <opencv2/opencv.hpp>

// Exiv2
#include <exiv2/exiv2.hpp>

class CImageGPSviewerDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CImageGPSviewerDoc() noexcept;
	DECLARE_DYNCREATE(CImageGPSviewerDoc)

// 특성입니다.
public:

// 작업입니다.
public:
	double convert_rational_to_decimal(const Exiv2::Rational& rational);
	double convert_gps_lon_lat(const Exiv2::Value& value);
	double convert_gps_alt(const Exiv2::Value& value);
	std::array<double, 3> meta_transform(const std::span<double>& s);
	std::array<double, 3> read_meta_data(const std::string& img_path);

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CImageGPSviewerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	CString image_path = _T("");

public:
	std::map<int , std::string> GPS_data;
	std::array<double, 3> meta_data;
	std::array<double, 3> img_meta;
	cv::Mat_<double> ground_meta;
	long img_width;
	long img_height;

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
