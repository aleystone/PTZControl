// CheckButton.cpp : ʵ���ļ�
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
//����: ת��ͼ��
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
//����: ת��ͼ��
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
//����: ת��ͼ��
//
//
///////////////////////////////////////////////////////////////////////////
void CCheckButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
//����: 
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
//����: 
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
//����: 
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
//����: 
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
