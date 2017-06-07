// YTDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "YT.h"
#include "YTDlg.h"
#include ".\ytdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
CYTDlg *g_pMainDlg ;
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CYTDlg 对话框



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
	//给控件关联变量
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
	//映射函数
	ON_BN_CLICKED(IDC_BTN_SPEED_OK, OnBnClickedButtonSpeedOK)
	ON_BN_CLICKED(IDC_BTN_UP_OK, OnBnClickedButtonUpOK)
	ON_BN_CLICKED(IDC_BTN_DOWN_OK, OnBnClickedButtonDownOK)
	ON_BN_CLICKED(IDC_BTN_LEFT_OK, OnBnClickedButtonLeftOK)
	ON_BN_CLICKED(IDC_BTN_RIGHT_OK, OnBnClickedButtonRightOK)
END_MESSAGE_MAP()


// CYTDlg 消息处理程序

BOOL CYTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_CCom.m_bOpenCom = TRUE;
	if(m_CCom.OpenCOM(1) == INVALID_HANDLE_VALUE)
	{
		MessageBox("打开串口失败！", "提示",MB_ICONEXCLAMATION);
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


	// TODO: 在此添加额外的初始化代码
	InitBtn();

	bPatternStart = FALSE;
	bPatternPlay = FALSE;
	GetDlgItem(IDC_BUTTON_START_PATTERN)->SetWindowText("开始录制");
	GetDlgItem(IDC_BUTTON_PLAY_PATTERN)->SetWindowText("开始播放");

	
//	m_nSpeed = 30 * 0x3f / 100;
//	m_CStageLens.SetSpeed(m_nSpeed);
	
	

	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CYTDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
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
	// TODO: 在此添加控件通知处理程序代码

}

void CYTDlg::OnEnChangeEditYtAddr()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
// 	UpdateData();
// 	//获取Slider值
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
	m_btnUp.SetTooltipText("上");

	m_btnDown.SubclassDlgItem(IDC_BUTTON_DOWN, this);
	m_btnDown.LoadBitmaps(IDB_BITMAP_DOWN, IDB_BITMAP_DOWN_F);
	m_btnDown.SizeToContent();
	m_btnDown.SetTooltipText("下");

	m_btnLeft.SubclassDlgItem(IDC_BUTTON_LEFT, this);
	m_btnLeft.LoadBitmaps(IDB_BITMAP_LEFT, IDB_BITMAP_LEFT_F);
	m_btnLeft.SizeToContent();
	m_btnLeft.SetTooltipText("左");

	m_btnRight.SubclassDlgItem(IDC_BUTTON_RIGHT, this);
	m_btnRight.LoadBitmaps(IDB_BITMAP_RIGHT, IDB_BITMAP_RIGHT_F);
	m_btnRight.SizeToContent();
	m_btnRight.SetTooltipText("右");

	m_btnTopLeft.SubclassDlgItem(IDC_BUTTON_TOP_LEFT, this);
	m_btnTopLeft.LoadBitmaps(IDB_BITMAP_TOP_LEFT, IDB_BITMAP_TOP_LEFT_F);
	m_btnTopLeft.SizeToContent();
	m_btnTopLeft.SetTooltipText("左上");

	m_btnTopRight.SubclassDlgItem(IDC_BUTTON_TOP_RIGHT, this);
	m_btnTopRight.LoadBitmaps(IDB_BITMAP_TOP_RIGHT, IDB_BITMAP_TOP_RIGHT_F);
	m_btnTopRight.SizeToContent();
	m_btnTopRight.SetTooltipText("右上");

	m_btnButtomLeft.SubclassDlgItem(IDC_BUTTON_BOTTOM_LEFT, this);
	m_btnButtomLeft.LoadBitmaps(IDB_BITMAP_BOTTOM_LEFT, IDB_BITMAP_BOTTOM_LEFT_F);
	m_btnButtomLeft.SizeToContent();
	m_btnButtomLeft.SetTooltipText("左下");

	m_btnButtomRight.SubclassDlgItem(IDC_BUTTON_BOTTOM_RIGHT, this);
	m_btnButtomRight.LoadBitmaps(IDB_BITMAP_BOTTOM_RIGHT, IDB_BITMAP_BOTTOM_RIGHT_F);
	m_btnButtomRight.SizeToContent();
	m_btnButtomRight.SetTooltipText("右下");
*/

	//CZBitmap ,,,,,;

	m_btnIrisIn.SubclassDlgItem(IDC_BUTTON_IRIS_IN, this);
	m_btnIrisIn.LoadBitmaps(IDB_BITMAP_ZOOM_IN, IDB_BITMAP_ZOOM_IN_F);
	m_btnIrisIn.SizeToContent();
	m_btnIrisIn.SetTooltipText("光圈-");

	m_btnIrisOut.SubclassDlgItem(IDC_BUTTON_IRIS_OUT, this);
	m_btnIrisOut.LoadBitmaps(IDB_BITMAP_ZOOM_OUT, IDB_BITMAP_ZOOM_OUT_F);
	m_btnIrisOut.SizeToContent();
	m_btnIrisOut.SetTooltipText("光圈+");


	m_btnFoucsIn.SubclassDlgItem(IDC_BUTTON_FOCUS_IN, this);
	m_btnFoucsIn.LoadBitmaps(IDB_BITMAP_ZOOM_IN, IDB_BITMAP_ZOOM_IN_F);
	m_btnFoucsIn.SizeToContent();
	m_btnFoucsIn.SetTooltipText("聚焦-");

	m_btnFoucsOut.SubclassDlgItem(IDC_BUTTON_FOCUS_OUT, this);
	m_btnFoucsOut.LoadBitmaps(IDB_BITMAP_ZOOM_OUT, IDB_BITMAP_ZOOM_OUT_F);
	m_btnFoucsOut.SizeToContent();
	m_btnFoucsOut.SetTooltipText("聚焦+");

	m_btnZoomIn.SubclassDlgItem(IDC_BUTTON_ZOOM_IN, this);
	m_btnZoomIn.LoadBitmaps(IDB_BITMAP_ZOOM_IN, IDB_BITMAP_ZOOM_IN_F);
	m_btnZoomIn.SizeToContent();
	m_btnZoomIn.SetTooltipText("变倍-");

	m_btnZoomOut.SubclassDlgItem(IDC_BUTTON_ZOOM_OUT, this);
	m_btnZoomOut.LoadBitmaps(IDB_BITMAP_ZOOM_OUT, IDB_BITMAP_ZOOM_OUT_F);
	m_btnZoomOut.SizeToContent();
	m_btnZoomOut.SetTooltipText("变倍+");
/*
	m_cbtnAutoScan.SubclassDlgItem(IDC_BUTTON_AUTO_SCAN,this);
	m_cbtnAutoScan.SetBMPID(IDB_BITMAP_AUTO_SCAN,IDB_BITMAP_AUTO_SCAN_F);
	m_cbtnAutoScan.SetTooltipText("自动扫描");*/
// 
// 	m_cbtnRainBrush.SubclassDlgItem(IDC_BUTTON_RAIN_BRUSH,this);
// 	m_cbtnRainBrush.SetBMPID(IDB_BITMAP_RAIN_BRUSH,IDB_BITMAP_RAIN_BRUSH_F);
// 	m_cbtnRainBrush.SetTooltipText("雨刷");
// 
// 	m_cbtnSearchLight.SubclassDlgItem(IDC_BUTTON_SEARCH_LIGHT,this);
// 	m_cbtnSearchLight.SetBMPID(IDB_BITMAP_SEARCH_LIGHT,IDB_BITMAP_SEARCH_LIGHT_F);
// 	m_cbtnSearchLight.SetTooltipText("射灯");
	
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
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	UpdateData(TRUE);
	CString strPoint;
	m_nPrePoint.GetWindowText(strPoint);
	m_nPre =atoi(strPoint) ;
}

void CYTDlg::OnBnClickedButtonPreGo()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	if(!bPatternStart)
	{
		//开路
		m_CStageLens.Pattern(m_nAddr,CStageLens::PatternAction_Start);
		GetDlgItem(IDC_BUTTON_START_PATTERN)->SetWindowText("停止录制");
		UpdateData(FALSE);
		bPatternStart = !bPatternStart;
	}
	else
	{
		//停止
		m_CStageLens.Pattern(m_nAddr,CStageLens::PatternAction_Stop);
		GetDlgItem(IDC_BUTTON_START_PATTERN)->SetWindowText("开始录制");
		UpdateData(FALSE);
		bPatternStart = !bPatternStart;
	}

}

void CYTDlg::OnBnClickedButtonPlayPattern()
{
	if(!bPatternPlay)
	{
		//开路
		m_CStageLens.Pattern(m_nAddr,CStageLens::PatternAction_Run);
		GetDlgItem(IDC_BUTTON_PLAY_PATTERN)->SetWindowText("停止播放");
		UpdateData(FALSE);
		bPatternPlay = !bPatternPlay;
	}
	else
	{
		//停止
		m_CStageLens.Noop(m_nAddr);
		GetDlgItem(IDC_BUTTON_PLAY_PATTERN)->SetWindowText("开始播放");
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
	//设置转速
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



