﻿
#pragma once

#include "ViewTree.h"
#include "pch.h"
#include <map>
#include <iostream>

class CFileViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CFileView : public CDockablePane
{
// 생성입니다.
public:
	CFileView() noexcept;

	void AdjustLayout();
	void OnChangeVisualStyle();

// 특성입니다.
public:
	CViewTree m_wndFileView;
	CImageList m_FileViewImages;
	CFileViewToolBar m_wndToolBar;
	CImage m_image;
	CListCtrl m_wndFileList;

public:
	//void FillFileView();
	void UpdateFileView(const std::string& path);

public:
	CString select_img_path;

// 구현입니다.
public:
	virtual ~CFileView();

public:
	afx_msg void OnFileOpen();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnProperties();
	//afx_msg void OnFileOpen();
	//afx_msg void OnFileOpenWith();
	afx_msg void OnDummyCompile();
	//afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};

