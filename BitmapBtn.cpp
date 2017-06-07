/////////////////////////////////////////////////////////////////////////////
//Project:      
//Discription:  ͼ�ΰ�ť,������̨��
//Written By:   ZXZ
//Date:         2006-06-28
//Version:      1.0
//
//Modified by:
//Modified Date:
//Version:
//
////////////////////////////////////////////////////////////////////////////
// BitmapBtn.cpp : implementation file
//

#include "stdafx.h"
#include "YT.h"
#include "BitmapBtn.h"
#include "resource.h"
#include "YTDlg.h"
#include ".\bitmapbtn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZBitmap
CZBitmap::CZBitmap()
{
	m_bDown = FALSE;
	m_ToolTip.m_hWnd = NULL;
}

CZBitmap::~CZBitmap()
{
}

BEGIN_MESSAGE_MAP(CZBitmap, CBitmapButton)
	//{{AFX_MSG_MAP(CZBitmap)
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CZBitmap message handlers

///////////////////////////////////////////////////////////////////////////
//����: ���°�ť, ִ����̨��Ӧ�Ĳ���
//
//
///////////////////////////////////////////////////////////////////////////
void CZBitmap::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!m_bDown)
	{
		m_bDown = TRUE;
		((CYTDlg *)AfxGetMainWnd())->YTBtnDown(GetDlgCtrlID());
	}
	CBitmapButton::OnLButtonDown(nFlags, point);
}

///////////////////////////////////////////////////////////////////////////
//����: �ͷŰ�ť, ֹͣ��̨����
//
//
///////////////////////////////////////////////////////////////////////////
void CZBitmap::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bDown)
	{
		m_bDown = FALSE;
		((CYTDlg *)AfxGetMainWnd())->YTBtnUp(GetDlgCtrlID());
	}
	CBitmapButton::OnLButtonUp(nFlags, point);
}

///////////////////////////////////////////////////////////////////////////
//����: 
//
//
///////////////////////////////////////////////////////////////////////////
void CZBitmap::InitToolTip()
{
	if (m_ToolTip.m_hWnd == NULL)
	{
		m_ToolTip.Create(this);
		m_ToolTip.Activate(FALSE);
		// Enable multiline
		m_ToolTip.SendMessage(TTM_SETMAXTIPWIDTH, 0, 400);
		m_ToolTip.SetTipTextColor(RGB(255,0,0));
	}
}

///////////////////////////////////////////////////////////////////////////
//����: 
//
//
///////////////////////////////////////////////////////////////////////////
BOOL CZBitmap::PreTranslateMessage(MSG* pMsg) 
{
	InitToolTip();
	m_ToolTip.RelayEvent(pMsg);
	return CButton::PreTranslateMessage(pMsg);
}

///////////////////////////////////////////////////////////////////////////
//����: 
//
//
///////////////////////////////////////////////////////////////////////////
void CZBitmap::SetTooltipText(int nText, BOOL bActivate)
{
	CString sText;
	sText.LoadString(nText);
	if (sText.IsEmpty() == FALSE)
	{
		SetTooltipText((LPCTSTR)sText, bActivate);
	}
}
void CZBitmap::SetTooltipText(LPCTSTR lpszText, BOOL bActivate)
{
	if (lpszText == NULL)
	{
		return;
	}

	InitToolTip();

	if (m_ToolTip.GetToolCount() == 0)
	{
		CRect rectBtn; 
		GetClientRect(rectBtn);
		m_ToolTip.AddTool(this, lpszText, rectBtn, 1);
	}
	m_ToolTip.UpdateTipText(lpszText, this, 1);
	m_ToolTip.Activate(bActivate);
}

///////////////////////////////////////////////////////////////////////////
//����: 
//
//
///////////////////////////////////////////////////////////////////////////
void CZBitmap::ActivateTooltip(BOOL bActivate)
{
	if (m_ToolTip.GetToolCount() == 0)
	{
		return;
	}
	m_ToolTip.Activate(bActivate);
}
