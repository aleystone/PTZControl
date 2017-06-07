#pragma once


// CCheckButton

class CCheckButton : public CBitmapButton //CButton
{
	DECLARE_DYNAMIC(CCheckButton)

public:
	CCheckButton();
	virtual ~CCheckButton();

private:
	UINT m_nNormalID, m_nDownID;
	BOOL m_bDowned;
	CToolTipCtrl m_ToolTip;			// Tooltip

private:
	void InitToolTip();

	/*CDC			m_dcBk;
	CBitmap		m_bmpBk;
	CBitmap*	m_pbmpOldBk;*/

public:
	void SetBMPID(UINT nNormalID, UINT nDownID);
	void SetDown(BOOL bDown = TRUE);
	//BOOL OnClick();
	BOOL GetDowned() {return m_bDowned; }
	void SetTooltipText(int nText, BOOL bActivate = TRUE);
	void SetTooltipText(LPCTSTR lpszText, BOOL bActivate = TRUE);
	void ActivateTooltip(BOOL bEnable = TRUE);

protected:
	//{{AFX_MSG(CZBitmap)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


