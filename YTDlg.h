// YTDlg.h : ͷ�ļ�
//

#pragma once
#include"Com.h"
//#include "Pelco_D.h"
//#include"Pelco_P.h"
#include "StageLens.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "BitmapBtn.h"
#include "CheckButton.h"

// CYTDlg �Ի���
class CYTDlg : public CDialog
{
// ����
public:
	CYTDlg(CWnd* pParent = NULL);	// ��׼���캯��

	int		m_Number;
// �Ի�������
	enum { IDD = IDD_YT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	CCom m_CCom;//Class
	CStageLens m_CStageLens;
//	CMSComm	m_ctrlComm;
// ʵ��
protected:
	HICON m_hIcon;
	
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CZBitmap m_btnUp,m_btnDown,m_btnLeft,m_btnRight,m_btnTopLeft,m_btnTopRight,m_btnButtomLeft,m_btnButtomRight;
	CZBitmap m_btnIrisIn,m_btnIrisOut,m_btnFoucsIn,m_btnFoucsOut,m_btnZoomIn,m_btnZoomOut;
	CCheckButton m_cbtnAutoScan,m_cbtnRainBrush,m_cbtnSearchLight;
public:
	int m_nAddr;
	int m_nPelcoType;
	int m_nSpeed;
	int m_nPre;
	BOOL bPatternStart,bPatternPlay;
	
public:
	void InitBtn();
	void YTBtnUp(int nResourceID);
	void YTBtnDown(int nResourceID);
	void YTCHECKBtn(int nResourceID);
	//��������
	afx_msg void OnBnClickedButtonUpOK();
	afx_msg void OnBnClickedButtonDownOK();
	afx_msg void OnBnClickedButtonLeftOK();
	afx_msg void OnBnClickedButtonRightOK();

	afx_msg void OnBnClickedButtonSpeedOK(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonSetup();
	CComboBox m_cb_YT_Type;
	afx_msg void OnCbnSelchangeComboYtType();
	afx_msg void OnEnChangeEditYtAddr();
	CEdit m_nEdit_Addr;		//�Ƶ�ַ
	CString m_nEdit_Speed;	//ת��
	CString m_nEdit_Angle;	//�Ƕ���

//	CSliderCtrl m_Slider_Speed;
//	afx_msg void OnNMReleasedcaptureSliderSpeed(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnEnChangeEditPre();
	CEdit m_nPrePoint;
	afx_msg void OnBnClickedButtonPreGo();
	afx_msg void OnBnClickedButtonPreSet();
	afx_msg void OnBnClickedButtonPreClear();
	afx_msg void OnBnClickedButtonStartPattern();
	afx_msg void OnBnClickedButtonPlayPattern();
};
extern CYTDlg *g_pMainDlg ;
