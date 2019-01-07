// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.
#pragma once

#include "MFCToolsDefines.h"
#include "Controls/DlgBars.h"

class MFC_TOOLS_PLUGIN_API CToolbarDialog : public CXTPDialogBase<CXTResizeDialog>
{
	DECLARE_DYNAMIC(CToolbarDialog)
public:
	CToolbarDialog();
	CToolbarDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	virtual ~CToolbarDialog();

	void RecalcLayout();
	void RecalcBarLayout() { RecalcLayout(); }
protected:
	void RepositionBarsInternal(UINT nIDFirst, UINT nIDLast, UINT nIDLeftOver,
	                            UINT nFlags = reposDefault, LPRECT lpRectParam = NULL, LPCRECT lpRectClient = NULL, BOOL bStretch = TRUE);
	void RepositionWindowInternal(AFX_SIZEPARENTPARAMS* lpLayout, HWND hWnd, LPCRECT lpRect);

	// Generated message map functions
	//{{AFX_MSG(CTerrainDialog)
	afx_msg BOOL OnToolTipText(UINT, NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg BOOL CToolbarDialog::OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnEnterIdle(UINT nWhy, CWnd* pWho);
	afx_msg LRESULT OnKickIdle(WPARAM wParam, LPARAM);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// Custom frame window.
//////////////////////////////////////////////////////////////////////////
// disable virtual function override warnings, as MFC headers do not pass them.
#pragma warning(push)
#pragma warning(disable: 4264)
class MFC_TOOLS_PLUGIN_API CCustomFrameWnd : public CXTPFrameWnd
{
public:
	DECLARE_DYNAMIC(CCustomFrameWnd)

	CCustomFrameWnd();

	BOOL                    Create(DWORD dwStyle, const CRect& rect, CWnd* pParentWnd, UINT nID);

	void                    LoadLayout(const CString& profile);
	void                    InstallDockingPanes();

	CXTPDockingPaneManager* GetDockingPaneManager() { return &m_paneManager; }

protected:
	DECLARE_MESSAGE_MAP()

	virtual BOOL    OnInitDialog()                                    { return TRUE; }
	virtual LRESULT OnDockingPaneNotify(WPARAM wParam, LPARAM lParam) { return 0; }

	virtual BOOL    PreTranslateMessage(MSG* pMsg);
	virtual BOOL    OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual void    PostNcDestroy() {}

	afx_msg BOOL    OnEraseBkgnd(CDC* pDC);
	afx_msg void    OnDestroy();
	afx_msg BOOL    OnToggleBar(UINT nID);
	afx_msg void    OnUpdateControlBar(CCmdUI* pCmdUI);

protected:
	CWnd*                  m_pViewWnd;
	CXTPDockingPaneManager m_paneManager;
	CString                m_profile;
};
#pragma warning(pop)
