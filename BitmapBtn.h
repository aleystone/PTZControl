#pragma once


/////////////////////////////////////////////////////////////////////////////
// CZBitmap window
class CZBitmap : public CBitmapButton
{
// Construction
public:
	CZBitmap();
	virtual ~CZBitmap();

protected:
	BOOL m_bDown;
	CToolTipCtrl m_ToolTip;			// Tooltip

	// Generated message map functions
protected:
	//{{AFX_MSG(CZBitmap)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	void InitToolTip();
public:
	void SetTooltipText(int nText, BOOL bActivate = TRUE);
	void SetTooltipText(LPCTSTR lpszText, BOOL bActivate = TRUE);
	void ActivateTooltip(BOOL bEnable = TRUE);

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

