// CheckButton.cpp : 实现文件
//

#include "stdafx.h"
#include "YT.h"
#include "CheckButton.h"
#include ".\checkbutton.h"
#include "YTDlg.h"
#include <commctrl.h>


// CCheckButton

IMPLEMENT_DYNAMIC(CCheckButton, CBitmapButton)
CCheckButton::CCheckButton()
{
	m_nNormalID = 0;
	m_nDownID = 0;
	m_bDowned = FALSE;
	m_ToolTip.m_hWnd = NULL;
}

CCheckButton::~CCheckButton()
{
}

BEGIN_MESSAGE_MAP(CCheckButton, CBitmapButton)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


void CCheckButton::SetBMPID(UINT nNormalID, UINT nDownID)
{
	m_nNormalID = nNormalID;
	m_nDownID = nDownID;
	LoadBitmaps(m_nNormalID, nDownID);
	SizeToContent();
}

///////////////////////////////////////////////////////////////////////////
//功能: 转换图像
//
//
///////////////////////////////////////////////////////////////////////////
void CCheckButton::SetDown(BOOL bDown)
{
	m_bDowned = bDown;
	if ( m_bDowned )
	{
		LoadBitmaps(m_nDownID, m_nDownID);
	}
	else
	{
		LoadBitmaps(m_nNormalID, m_nDownID);
	}
	SizeToContent();
	RedrawWindow();
}

///////////////////////////////////////////////////////////////////////////
//功能: 转换图像
//
//
///////////////////////////////////////////////////////////////////////////
/*LRESULT CCheckButton::OnSetCheck(WPARAM wParam, LPARAM lParam)
{
	if (wParam == BST_CHECKED)
	{
		SetBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(m_nDownID)) );
	}
	else if (wParam == BST_UNCHECKED)
	{
		SetBitmap(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(m_nNormalID)) );
	}
	return wParam;
}*/

///////////////////////////////////////////////////////////////////////////
//功能: 转换图像
//
//
///////////////////////////////////////////////////////////////////////////
void CCheckButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetDown(!m_bDowned);
	((CYTDlg *)AfxGetMainWnd())->YTCHECKBtn(GetDlgCtrlID());
//	AfxGetMainWnd()->SendMessage(WM_YTBUTTONDOWN, (WPARAM)nFlags, (LPARAM)GetDlgCtrlID());
	//CBitmapButton::OnLButtonDown(nFlags, point);
}
//void CCheckButton::OnBnClicked()
//{
//	SetDown(!m_bDowned);
//}

///////////////////////////////////////////////////////////////////////////
//功能: 
//
//
///////////////////////////////////////////////////////////////////////////
void CCheckButton::InitToolTip()
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
//功能: 
//
//
///////////////////////////////////////////////////////////////////////////
BOOL CCheckButton::PreTranslateMessage(MSG* pMsg) 
{
	InitToolTip();
	m_ToolTip.RelayEvent(pMsg);
	return CBitmapButton::PreTranslateMessage(pMsg);
}
///////////////////////////////////////////////////////////////////////////
//功能: 
//
//
///////////////////////////////////////////////////////////////////////////
void CCheckButton::SetTooltipText(int nText, BOOL bActivate)
{
	CString sText;
	sText.LoadString(nText);
	if (sText.IsEmpty() == FALSE)
	{
		SetTooltipText((LPCTSTR)sText, bActivate);
	}
}
void CCheckButton::SetTooltipText(LPCTSTR lpszText, BOOL bActivate)
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
//功能: 
//
//
///////////////////////////////////////////////////////////////////////////
void CCheckButton::ActivateTooltip(BOOL bActivate)
{
	if (m_ToolTip.GetToolCount() == 0)
	{
		return;
	}
	m_ToolTip.Activate(bActivate);
}
