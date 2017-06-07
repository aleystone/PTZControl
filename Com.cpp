// Com.cpp : 实现文件
//

#include "stdafx.h"
#include "YT.h"
#include "Com.h"
#include ".\com.h"


// CCom 对话框

IMPLEMENT_DYNAMIC(CCom, CDialog)
CCom::CCom(CWnd* pParent /*=NULL*/)
	: CDialog(CCom::IDD, pParent)
	//, m_nRate(7)
	//, m_strParity(_T("NONE"))
	//, m_nData(4)
	//, m_nStop(0)
	//, m_nComNo(0)
{
	m_bOpenCom = FALSE;
	m_nComNo = 0;
	m_nRate = 4800;
	m_nParity = NOPARITY;//NONE
	m_nData = 8;
	m_nStop = ONESTOPBIT;//1
}

CCom::~CCom()
{
}

void CCom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COM_NO, m_cbCom);
	DDX_Control(pDX, IDC_COMBO_COM_RATE, m_cb_Rate);
	DDX_Control(pDX, IDC_COMBO_COM_PARITY, m_cb_Parity);
	DDX_Control(pDX, IDC_COMBO_DATE, m_cb_Data);
	DDX_Control(pDX, IDC_COMBO_STOP, m_cb_Stop);
	

	//DDX_CBIndex(pDX, IDC_COMBO_COM_RATE, m_nRate);
	//DDX_CBString(pDX, IDC_COMBO_COM_PARITY, m_strParity);
	//DDX_CBIndex(pDX, IDC_COMBO_DATE, m_nData);
	//DDX_CBIndex(pDX, IDC_COMBO_STOP, m_nStop);

	//DDX_CBIndex(pDX, IDC_COMBO_COM_NO, m_nComNo);
}


BEGIN_MESSAGE_MAP(CCom, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CCom 消息处理程序

BOOL CCom::OnInitDialog()
{

	
	CDialog::OnInitDialog();
	InitComBox();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
//
void CCom::InitComBox(void)
{
	//
	//m_cbCom.Clear();
	m_cbCom.InsertString(0,"COM 1");
	m_cbCom.InsertString(1,"COM 2");
	m_cbCom.InsertString(2,"COM 3");
	m_cbCom.InsertString(3,"COM 4");
	m_cbCom.SetCurSel(m_nComNo);
	//
	//m_cb_Rate.Clear();
	m_cb_Rate.InsertString(0,"1200");
	m_cb_Rate.InsertString(1,"2400");
	m_cb_Rate.InsertString(2,"4800");
	m_cb_Rate.InsertString(3,"9600");
	switch(m_nRate)
	{
	case 1200:
		m_cb_Rate.SetCurSel(0);
		break;
	case 2400:
		m_cb_Rate.SetCurSel(1);
		break;
	case 4800:
		m_cb_Rate.SetCurSel(2);
		break;
	case 9600:
		m_cb_Rate.SetCurSel(3);
		break;
	default:
		break;
	}
	//
	//m_cb_Data.Clear();
	m_cb_Data.InsertString(0,"4");
	m_cb_Data.InsertString(1,"5");
	m_cb_Data.InsertString(2,"6");
	m_cb_Data.InsertString(3,"7");
	m_cb_Data.InsertString(4,"8");
	m_cb_Data.SetCurSel(m_nData-4);

	//
	//m_cb_Parity.Clear();
	m_cb_Parity.InsertString(0,"NONE");
	m_cb_Parity.InsertString(1,"ODD");
	m_cb_Parity.InsertString(2,"EVEN");
	m_cb_Parity.InsertString(3,"MARK");
	m_cb_Parity.InsertString(4,"SPACE");
	m_cb_Parity.SetCurSel(m_nParity);
	//
	//m_cb_Stop.Clear();
	m_cb_Stop.AddString("1");
	m_cb_Stop.AddString("1.5");
	m_cb_Stop.AddString("2");
	m_cb_Stop.SetCurSel(m_nStop);

}
void CCom::OnBnClickedOk()
{
	UpdateData(TRUE);

	m_nComNo = m_cbCom.GetCurSel();
	switch(m_cb_Rate.GetCurSel())
	{
	case 0:
		m_nRate = 1200;
		break;
	
	case 1:
		m_nRate = 2400;
		break;
	case 2:
		m_nRate = 4800;
		break;
	case 3:
		m_nRate = 9600;
		break;
	default:
		break;
	}
	m_nParity = m_cb_Parity.GetCurSel();
	m_nData = m_cb_Data.GetCurSel() + 4;
	m_nStop = m_cb_Stop.GetCurSel();

	if(m_bOpenCom)
		Close();
	if(OpenCOM(m_nComNo+1) == INVALID_HANDLE_VALUE)
	{
		MessageBox("打开串口失败！", "提示",MB_ICONEXCLAMATION);
	}
	OnOK();
}



//////////////////////////////////////////////////////////////
//功能:     打开串口
//入口:     iPort:串口号
//返回:     >=0 打开后的串口指针,
//          INVALID_HANDLE_VALUE(-1) 失败
///////////////////////////////////////////////////////////////
HANDLE CCom::OpenCOM(int iPort)
{
    char szPortName[20];

  	wsprintf(szPortName, "COM%d", iPort);
    HANDLE hTemp = CreateFile( szPortName,
				GENERIC_READ | GENERIC_WRITE,
				0,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
				NULL);

    if (hTemp == INVALID_HANDLE_VALUE)
	{
	    return INVALID_HANDLE_VALUE;
    }
    m_hHandle = hTemp;
    
    SetCommMask(m_hHandle, EV_RXCHAR);
    SetupComm(m_hHandle, 4096, 4096); //
    PurgeComm(m_hHandle, PURGE_TXABORT | PURGE_RXABORT |	//清理串口
              PURGE_TXCLEAR | PURGE_RXCLEAR);

    COMMTIMEOUTS CommTimeOuts;
    CommTimeOuts.ReadIntervalTimeout = MAXDWORD;
    CommTimeOuts.ReadTotalTimeoutMultiplier = 2;
    CommTimeOuts.ReadTotalTimeoutConstant = 2000;
    CommTimeOuts.WriteTotalTimeoutMultiplier = 2;
    CommTimeOuts.WriteTotalTimeoutConstant = 800;
    if (!SetCommTimeouts(m_hHandle, &CommTimeOuts))
    {
        Close();
        return INVALID_HANDLE_VALUE;
    }

    DCB PortDCB;
  	// Set the default settings
    if (!GetCommState(m_hHandle, &PortDCB))
   	{
        Close();
	    return INVALID_HANDLE_VALUE;
    }
	PortDCB.DCBlength = sizeof(DCB);
	PortDCB.BaudRate = m_nRate;
    PortDCB.ByteSize = m_nData;
	PortDCB.Parity   = m_nParity;
    PortDCB.StopBits = m_nStop;
    if (!SetCommState(m_hHandle, &PortDCB))
	{
        Close();
    	return INVALID_HANDLE_VALUE;
	}

	return m_hHandle;
}


///////////////////////////////////////////////////////////////
//功能:     关闭端口
//
///////////////////////////////////////////////////////////////
void CCom::Close()
{
	if (m_hHandle == INVALID_HANDLE_VALUE)
		return;
    SetCommMask(m_hHandle, 0 );
    // purge any outstanding reads/writes and close device handle
   	PurgeComm(m_hHandle, PURGE_TXABORT | PURGE_RXABORT |
              PURGE_TXCLEAR | PURGE_RXCLEAR);
	CloseHandle(m_hHandle);
    m_hHandle = INVALID_HANDLE_VALUE;
}



///////////////////////////////////////////////////////////////
//功能:     从端口读数据
//
///////////////////////////////////////////////////////////////
int CCom::Read(char *buffer, int iMaxLength)
{
	BOOL       fReadStat ;
	COMSTAT    ComStat ;
	DWORD      dwErrorFlags;
	DWORD      dwLength;
	OVERLAPPED osRead;

	memset(&osRead, 0, sizeof(OVERLAPPED));
	if (m_hHandle == INVALID_HANDLE_VALUE)
		return 0;
	// only try to read number of bytes in queue
	ClearCommError(m_hHandle, &dwErrorFlags, &ComStat);
	dwLength = min((DWORD)iMaxLength, ComStat.cbInQue);

	if (dwLength<=0) return 0;
	fReadStat = ReadFile(m_hHandle, buffer, dwLength, &dwLength, &osRead) ;
	if (!fReadStat)
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			while (!GetOverlappedResult(m_hHandle, &osRead, &dwLength, true))
			{
				if (GetLastError() == ERROR_IO_INCOMPLETE) // normal result if not finished
					continue;
				else
				{
					// an error occurred, try to recover
					ClearCommError(m_hHandle, &dwErrorFlags, &ComStat ) ;
                    return 0;
				}
			}
		}
		else
		{
			// some other error occurred
			ClearCommError(m_hHandle, &dwErrorFlags, &ComStat ) ;
			return 0;
		}
	}
	return (int)dwLength;
}




///////////////////////////////////////////////////////////////
//功能:     写数据到端口
//
///////////////////////////////////////////////////////////////
int CCom::Write(char *buffer, int iLength)
{
	BOOL        fWriteStat;
	DWORD       dwBytesWritten;
	DWORD       dwErrorFlags;
	DWORD       dwBytesSent;
	COMSTAT     ComStat;
	OVERLAPPED  osWrite;

	if (m_hHandle == INVALID_HANDLE_VALUE)
		return 0;

	memset(&osWrite, 0, sizeof(OVERLAPPED));
	fWriteStat = WriteFile(m_hHandle, buffer, (DWORD)iLength, &dwBytesWritten, &osWrite);

	dwBytesSent = dwBytesWritten;
	if (!fWriteStat)
	{
    	dwBytesSent = 0;
		if(GetLastError() == ERROR_IO_PENDING)
		{
			while (!GetOverlappedResult(m_hHandle, &osWrite, &dwBytesWritten, true))
			{
				if (GetLastError() == ERROR_IO_INCOMPLETE)
				{
					// normal result if not finished
					dwBytesSent += dwBytesWritten;
					continue;
				}
				else
				{
					// an error occurred, try to recover
					ClearCommError(m_hHandle, &dwErrorFlags, &ComStat) ;
					break;
				}
			}
			dwBytesSent += dwBytesWritten;
		}
		else
		{
			// some other error occurred
			ClearCommError(m_hHandle, &dwErrorFlags, &ComStat) ;
		}
	}
	return (int)dwBytesSent;
}