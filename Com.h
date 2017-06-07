#pragma once
#include "afxwin.h"

// CCom �Ի���

class CCom : public CDialog
{
	DECLARE_DYNAMIC(CCom)

public:
	CCom(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCom();

// �Ի�������
	enum { IDD = IDD_COM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void InitComBox(void);
	HANDLE OpenCOM(int iPort);
	void Close();
	int  Read(char* buffer, int iMaxLength);
	int Write(char* buffer, int iLength);

	afx_msg void OnBnClickedOk();
public:

	BOOL m_bOpenCom;
	CComboBox m_cbCom;
	CComboBox m_cb_Rate;
	CComboBox m_cb_Parity;
	CComboBox m_cb_Data;
	CComboBox m_cb_Stop;

	HANDLE m_hHandle;
	int m_nComNo;
	int m_nRate;
	int m_nParity;
	int m_nData;
	int m_nStop;
	

};
