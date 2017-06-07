// YTDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "YT.h"
#include "YTDlg.h"
#include ".\ytdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
CYTDlg *g_pMainDlg ;
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CYTDlg �Ի���



CYTDlg::CYTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CYTDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_PTZControl);
}

void CYTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_YT_TYPE, m_cb_YT_Type);
	DDX_Control(pDX, IDC_EDIT_YT_ADDR, m_nEdit_Addr);
//	DDX_Control(pDX, IDC_SLIDER_SPEED, m_Slider_Speed);
	DDX_Control(pDX, IDC_EDIT_PRE, m_nPrePoint);
	//���ؼ���������
	DDX_Text(pDX, IDC_EDIT_SPEED, m_nEdit_Speed);
	DDX_Text(pDX, IDC_EDIT_ANGLE, m_nEdit_Angle);
}

BEGIN_MESSAGE_MAP(CYTDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_SETUP, OnBnClickedButtonSetup)
	ON_CBN_SELCHANGE(IDC_COMBO_YT_TYPE, OnCbnSelchangeComboYtType)
	ON_EN_CHANGE(IDC_EDIT_YT_ADDR, OnEnChangeEditYtAddr)
//	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_SPEED, OnNMReleasedcaptureSliderSpeed)
	ON_EN_CHANGE(IDC_EDIT_PRE, OnEnChangeEditPre)
	ON_BN_CLICKED(IDC_BUTTON_PRE_GO, OnBnClickedButtonPreGo)
	ON_BN_CLICKED(IDC_BUTTON_PRE_SET, OnBnClickedButtonPreSet)
	ON_BN_CLICKED(IDC_BUTTON_PRE_CLEAR, OnBnClickedButtonPreClear)
	ON_BN_CLICKED(IDC_BUTTON_START_PATTERN, OnBnClickedButtonStartPattern)
	ON_BN_CLICKED(IDC_BUTTON_PLAY_PATTERN, OnBnClickedButtonPlayPattern)
	//ӳ�亯��
	ON_BN_CLICKED(IDC_BTN_SPEED_OK, OnBnClickedButtonSpeedOK)
	ON_BN_CLICKED(IDC_BTN_UP_OK, OnBnClickedButtonUpOK)
	ON_BN_CLICKED(IDC_BTN_DOWN_OK, OnBnClickedButtonDownOK)
	ON_BN_CLICKED(IDC_BTN_LEFT_OK, OnBnClickedButtonLeftOK)
	ON_BN_CLICKED(IDC_BTN_RIGHT_OK, OnBnClickedButtonRightOK)
END_MESSAGE_MAP()


// CYTDlg ��Ϣ�������

BOOL CYTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��\������...\���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_CCom.m_bOpenCom = TRUE;
	if(m_CCom.OpenCOM(1) == INVALID_HANDLE_VALUE)
	{
		MessageBox("�򿪴���ʧ�ܣ�", "��ʾ",MB_ICONEXCLAMATION);
		m_CCom.m_bOpenCom = FALSE;
	}

	m_cb_YT_Type.InsertString(0,"PELCO_D");
	m_cb_YT_Type.InsertString(1,"PELCO_P");
	m_cb_YT_Type.SetCurSel(0);
	m_nPelcoType =0;

	//CString iStr;
	//iStr.Format("%d", m_nEdit_Angle);
	m_nAddr =1;
	m_nEdit_Addr.SetWindowText("1");

// 	m_Slider_Speed.SetRange(0,100);
// 	m_Slider_Speed.SetTicFreq(10);
// 	m_Slider_Speed.SetPos(30);

	m_CStageLens.SetProtocol(CStageLens::PELCO_D);
	m_CStageLens.SetSpeed(0);
	g_pMainDlg =this;


	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitBtn();

	bPatternStart = FALSE;
	bPatternPlay = FALSE;
	GetDlgItem(IDC_BUTTON_START_PATTERN)->SetWindowText("��ʼ¼��");
	GetDlgItem(IDC_BUTTON_PLAY_PATTERN)->SetWindowText("��ʼ����");

	
//	m_nSpeed = 30 * 0x3f / 100;
//	m_CStageLens.SetSpeed(m_nSpeed);
	
	

	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CYTDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CYTDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CYTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CYTDlg::OnBnClickedButtonSetup()
{
	m_CCom.DoModal();
}

void CYTDlg::OnCbnSelchangeComboYtType()
{
	UpdateData(TRUE);
	CString strAddr;
	m_nEdit_Addr.GetWindowText(strAddr);
	m_nAddr =atoi(strAddr) ;

	m_nPelcoType = m_cb_YT_Type.GetCurSel();
	if(m_nPelcoType == 0)
	{
		m_CStageLens.SetProtocol(CStageLens::PELCO_D);
	 
	}
	else if(m_nPelcoType == 1)
	{
		m_CStageLens.SetProtocol(CStageLens::PELCO_P);
		m_nAddr = m_nAddr-1;
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}

void CYTDlg::OnEnChangeEditYtAddr()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CString strAddr;
	m_nEdit_Addr.GetWindowText(strAddr);
	m_nAddr =atoi(strAddr) ;
	m_nPelcoType = m_cb_YT_Type.GetCurSel();
	if(m_nPelcoType) //PELCO_P
		m_nAddr = m_nAddr-1;
}

//void CYTDlg::OnNMReleasedcaptureSliderSpeed(NMHDR *pNMHDR, LRESULT *pResult)
//{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
// 	UpdateData();
// 	//��ȡSliderֵ
// 	int iTest = m_Slider_Speed.GetPos();
// 
// 	m_nSpeed = m_Slider_Speed.GetPos() * 0x3f / 100;
// 
// 	m_CStageLens.SetSpeed(m_nSpeed);
// 	*pResult = 0;
//}



void CYTDlg::InitBtn()
{/*
	m_btnUp.SubclassDlgItem(IDC_BUTTON_UP, this);
	m_btnUp.LoadBitmaps(IDB_BITMAP_UP, IDB_BITMAP_UP_F);
	m_btnUp.SizeToContent();
	m_btnUp.SetTooltipText("��");

	m_btnDown.SubclassDlgItem(IDC_BUTTON_DOWN, this);
	m_btnDown.LoadBitmaps(IDB_BITMAP_DOWN, IDB_BITMAP_DOWN_F);
	m_btnDown.SizeToContent();
	m_btnDown.SetTooltipText("��");

	m_btnLeft.SubclassDlgItem(IDC_BUTTON_LEFT, this);
	m_btnLeft.LoadBitmaps(IDB_BITMAP_LEFT, IDB_BITMAP_LEFT_F);
	m_btnLeft.SizeToContent();
	m_btnLeft.SetTooltipText("��");

	m_btnRight.SubclassDlgItem(IDC_BUTTON_RIGHT, this);
	m_btnRight.LoadBitmaps(IDB_BITMAP_RIGHT, IDB_BITMAP_RIGHT_F);
	m_btnRight.SizeToContent();
	m_btnRight.SetTooltipText("��");

	m_btnTopLeft.SubclassDlgItem(IDC_BUTTON_TOP_LEFT, this);
	m_btnTopLeft.LoadBitmaps(IDB_BITMAP_TOP_LEFT, IDB_BITMAP_TOP_LEFT_F);
	m_btnTopLeft.SizeToContent();
	m_btnTopLeft.SetTooltipText("����");

	m_btnTopRight.SubclassDlgItem(IDC_BUTTON_TOP_RIGHT, this);
	m_btnTopRight.LoadBitmaps(IDB_BITMAP_TOP_RIGHT, IDB_BITMAP_TOP_RIGHT_F);
	m_btnTopRight.SizeToContent();
	m_btnTopRight.SetTooltipText("����");

	m_btnButtomLeft.SubclassDlgItem(IDC_BUTTON_BOTTOM_LEFT, this);
	m_btnButtomLeft.LoadBitmaps(IDB_BITMAP_BOTTOM_LEFT, IDB_BITMAP_BOTTOM_LEFT_F);
	m_btnButtomLeft.SizeToContent();
	m_btnButtomLeft.SetTooltipText("����");

	m_btnButtomRight.SubclassDlgItem(IDC_BUTTON_BOTTOM_RIGHT, this);
	m_btnButtomRight.LoadBitmaps(IDB_BITMAP_BOTTOM_RIGHT, IDB_BITMAP_BOTTOM_RIGHT_F);
	m_btnButtomRight.SizeToContent();
	m_btnButtomRight.SetTooltipText("����");
*/

	//CZBitmap ,,,,,;

	m_btnIrisIn.SubclassDlgItem(IDC_BUTTON_IRIS_IN, this);
	m_btnIrisIn.LoadBitmaps(IDB_BITMAP_ZOOM_IN, IDB_BITMAP_ZOOM_IN_F);
	m_btnIrisIn.SizeToContent();
	m_btnIrisIn.SetTooltipText("��Ȧ-");

	m_btnIrisOut.SubclassDlgItem(IDC_BUTTON_IRIS_OUT, this);
	m_btnIrisOut.LoadBitmaps(IDB_BITMAP_ZOOM_OUT, IDB_BITMAP_ZOOM_OUT_F);
	m_btnIrisOut.SizeToContent();
	m_btnIrisOut.SetTooltipText("��Ȧ+");


	m_btnFoucsIn.SubclassDlgItem(IDC_BUTTON_FOCUS_IN, this);
	m_btnFoucsIn.LoadBitmaps(IDB_BITMAP_ZOOM_IN, IDB_BITMAP_ZOOM_IN_F);
	m_btnFoucsIn.SizeToContent();
	m_btnFoucsIn.SetTooltipText("�۽�-");

	m_btnFoucsOut.SubclassDlgItem(IDC_BUTTON_FOCUS_OUT, this);
	m_btnFoucsOut.LoadBitmaps(IDB_BITMAP_ZOOM_OUT, IDB_BITMAP_ZOOM_OUT_F);
	m_btnFoucsOut.SizeToContent();
	m_btnFoucsOut.SetTooltipText("�۽�+");

	m_btnZoomIn.SubclassDlgItem(IDC_BUTTON_ZOOM_IN, this);
	m_btnZoomIn.LoadBitmaps(IDB_BITMAP_ZOOM_IN, IDB_BITMAP_ZOOM_IN_F);
	m_btnZoomIn.SizeToContent();
	m_btnZoomIn.SetTooltipText("�䱶-");

	m_btnZoomOut.SubclassDlgItem(IDC_BUTTON_ZOOM_OUT, this);
	m_btnZoomOut.LoadBitmaps(IDB_BITMAP_ZOOM_OUT, IDB_BITMAP_ZOOM_OUT_F);
	m_btnZoomOut.SizeToContent();
	m_btnZoomOut.SetTooltipText("�䱶+");
/*
	m_cbtnAutoScan.SubclassDlgItem(IDC_BUTTON_AUTO_SCAN,this);
	m_cbtnAutoScan.SetBMPID(IDB_BITMAP_AUTO_SCAN,IDB_BITMAP_AUTO_SCAN_F);
	m_cbtnAutoScan.SetTooltipText("�Զ�ɨ��");*/
// 
// 	m_cbtnRainBrush.SubclassDlgItem(IDC_BUTTON_RAIN_BRUSH,this);
// 	m_cbtnRainBrush.SetBMPID(IDB_BITMAP_RAIN_BRUSH,IDB_BITMAP_RAIN_BRUSH_F);
// 	m_cbtnRainBrush.SetTooltipText("��ˢ");
// 
// 	m_cbtnSearchLight.SubclassDlgItem(IDC_BUTTON_SEARCH_LIGHT,this);
// 	m_cbtnSearchLight.SetBMPID(IDB_BITMAP_SEARCH_LIGHT,IDB_BITMAP_SEARCH_LIGHT_F);
// 	m_cbtnSearchLight.SetTooltipText("���");
	
}


void CYTDlg::YTBtnDown(int nResourceID)
{
	switch(nResourceID)
	{
		/*
		case IDC_BUTTON_UP:
			m_CStageLens.Up(m_nAddr);
			break;
		case IDC_BUTTON_DOWN:
			m_CStageLens.Down(m_nAddr);
			break;
		case IDC_BUTTON_LEFT:
			m_CStageLens.Left(m_nAddr);
			break;
		case IDC_BUTTON_RIGHT:
			m_CStageLens.Right(m_nAddr);
			break;
		case IDC_BUTTON_TOP_LEFT:
			m_CStageLens.TopLeft(m_nAddr);
			break;
		case IDC_BUTTON_TOP_RIGHT:
			m_CStageLens.TopRight(m_nAddr);
			break;
		case IDC_BUTTON_BOTTOM_LEFT:
			m_CStageLens.BottomLeft(m_nAddr);
			break;
		case IDC_BUTTON_BOTTOM_RIGHT:
			m_CStageLens.BottomRight(m_nAddr);
			break;*/


		case IDC_BUTTON_FOCUS_IN:
			m_CStageLens.FocusMinus(m_nAddr);
			break;
		case IDC_BUTTON_FOCUS_OUT:
			m_CStageLens.FocusPlus(m_nAddr);
			break;
		case IDC_BUTTON_IRIS_IN:
			m_CStageLens.IrisMinus(m_nAddr);
			break;
		case IDC_BUTTON_IRIS_OUT:
			m_CStageLens.IrisPlus(m_nAddr);
			break;
		case IDC_BUTTON_ZOOM_IN:
			m_CStageLens.ZoomMinus(m_nAddr);
		case IDC_BUTTON_ZOOM_OUT:
			m_CStageLens.ZoomPlus(m_nAddr);
			break;
			
	}
}

void CYTDlg::YTBtnUp(int nResourceID)
{
	m_CStageLens.Noop(m_nAddr);
	
}

void CYTDlg::YTCHECKBtn(int nResourceID)
{
	switch(nResourceID)
	{
		
	case IDC_BUTTON_AUTO_SCAN:
		if (m_cbtnAutoScan.GetDowned())
		{
			m_CStageLens.AutoScan(m_nAddr);
			m_CStageLens.PreSet(m_nAddr,99,CStageLens::PresetAction_Goto);
		}
		else
		{
			m_CStageLens.Noop(m_nAddr);
		}
		break;
	case IDC_BUTTON_RAIN_BRUSH:
		if (m_cbtnRainBrush.GetDowned())
		{
			m_CStageLens.RainBrushON(m_nAddr);
		}
		else
		{
			m_CStageLens.RainBrushOFF(m_nAddr);
		}
		break;
	case IDC_BUTTON_SEARCH_LIGHT:
			if (m_cbtnRainBrush.GetDowned())
		{
			m_CStageLens.SearchLightON(m_nAddr);
		}
		else
		{
			m_CStageLens.SearchLightOFF(m_nAddr);
		}
		break;
	}

}




void CYTDlg::OnEnChangeEditPre()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	UpdateData(TRUE);
	CString strPoint;
	m_nPrePoint.GetWindowText(strPoint);
	m_nPre =atoi(strPoint) ;
}

void CYTDlg::OnBnClickedButtonPreGo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_CStageLens.PreSet(m_nAddr,m_nPre,CStageLens::PresetAction_Goto);
}

void CYTDlg::OnBnClickedButtonPreSet()
{
	m_CStageLens.PreSet(m_nAddr,m_nPre,CStageLens::PresetAction_Set);
}

void CYTDlg::OnBnClickedButtonPreClear()
{
	m_CStageLens.PreSet(m_nAddr,m_nPre,CStageLens::PresetAction_Clear);
}

/////////////////////////////////////////////////////
void CYTDlg::OnBnClickedButtonStartPattern()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!bPatternStart)
	{
		//��·
		m_CStageLens.Pattern(m_nAddr,CStageLens::PatternAction_Start);
		GetDlgItem(IDC_BUTTON_START_PATTERN)->SetWindowText("ֹͣ¼��");
		UpdateData(FALSE);
		bPatternStart = !bPatternStart;
	}
	else
	{
		//ֹͣ
		m_CStageLens.Pattern(m_nAddr,CStageLens::PatternAction_Stop);
		GetDlgItem(IDC_BUTTON_START_PATTERN)->SetWindowText("��ʼ¼��");
		UpdateData(FALSE);
		bPatternStart = !bPatternStart;
	}

}

void CYTDlg::OnBnClickedButtonPlayPattern()
{
	if(!bPatternPlay)
	{
		//��·
		m_CStageLens.Pattern(m_nAddr,CStageLens::PatternAction_Run);
		GetDlgItem(IDC_BUTTON_PLAY_PATTERN)->SetWindowText("ֹͣ����");
		UpdateData(FALSE);
		bPatternPlay = !bPatternPlay;
	}
	else
	{
		//ֹͣ
		m_CStageLens.Noop(m_nAddr);
		GetDlgItem(IDC_BUTTON_PLAY_PATTERN)->SetWindowText("��ʼ����");
		UpdateData(FALSE);
		bPatternPlay = !bPatternPlay;
	}
}

//************************************
// Method:    OnBnClickedButtonSpeedOK
// FullName:  CYTDlg::OnBnClickedButtonSpeedOK
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: NMHDR * pNMHDR
// Parameter: LRESULT * pResult
//************************************
void CYTDlg::OnBnClickedButtonSpeedOK(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData(TRUE);
	//����ת��
	int iSpeed = atoi(m_nEdit_Speed);
	m_nSpeed = iSpeed * 0x3f / 100;
	m_CStageLens.SetSpeed(m_nSpeed);
	*pResult = 0;
}

void CYTDlg::OnBnClickedButtonUpOK()
{
	UpdateData(TRUE);
	m_nAddr = atoi(m_nEdit_Angle);
	m_CStageLens.Up(m_nAddr);

}
void CYTDlg::OnBnClickedButtonDownOK()
{
	UpdateData(TRUE);
	m_nAddr = atoi(m_nEdit_Angle);
	m_CStageLens.Down(m_nAddr);
	

}
void CYTDlg::OnBnClickedButtonLeftOK()
{
	UpdateData(TRUE);
	m_nAddr = atoi(m_nEdit_Angle);
	m_CStageLens.Left(m_nAddr);


}
void CYTDlg::OnBnClickedButtonRightOK()
{
	UpdateData(TRUE);
	m_nAddr = atoi(m_nEdit_Angle);
	m_CStageLens.Right(m_nAddr);

}



