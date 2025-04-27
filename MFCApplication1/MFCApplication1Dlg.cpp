
// MFCApplication1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 对话框

BOOL CMFCApplication1Dlg::m_bCancelled = FALSE;

CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
	, m_iCountDown(0)
	, m_iHour(0)
	, m_iMinute(0)
	, m_iSecond(0)
	, m_seconds(0)
	, m_preSeconds(0)
	, m_bTiming(false)
	, m_iHour2(0)
	, m_iMinute2(0)
	, m_iSecond2(0)
	, m_cstrInfo(_T("Take a break!"))
	//, m_cstrRemindInfo(_T("休息一下!"))
	, m_isMouseDown(FALSE)
	, m_startPoint(0)
	//, m_bShutdown(FALSE)
	//, m_bForceRest(FALSE)
	, m_bPauseBtn(FALSE)
	, m_iTimeupAction(2)
	, m_iFirstPress(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDRB_COUNTDOWN, m_iCountDown);
	DDX_Control(pDX, IDC_SPIN1, m_spinHour1);
	DDX_Control(pDX, IDC_SPIN2, m_spinMinute1);
	DDX_Control(pDX, IDC_SPIN3, m_spinSecond1);
	DDX_Text(pDX, IDE_HOUR, m_iHour);
	DDV_MinMaxInt(pDX, m_iHour, 0, 23);
	DDX_Text(pDX, IDE_MIN, m_iMinute);
	DDV_MinMaxInt(pDX, m_iMinute, 0, 59);
	DDX_Text(pDX, IDE_SEC, m_iSecond);
	DDV_MinMaxInt(pDX, m_iSecond, 0, 59);
	DDX_Text(pDX, IDE_HOUR2, m_iHour2);
	DDV_MinMaxInt(pDX, m_iHour2, 0, 23);
	DDX_Text(pDX, IDE_MIN2, m_iMinute2);
	DDV_MinMaxInt(pDX, m_iMinute2, 0, 59);
	DDX_Text(pDX, IDE_SEC2, m_iSecond2);
	DDV_MinMaxInt(pDX, m_iSecond2, 0, 59);
	DDX_Control(pDX, IDC_SPIN4, m_spinHour2);
	DDX_Control(pDX, IDC_SPIN5, m_spinMinute2);
	DDX_Control(pDX, IDC_SPIN6, m_spinSecond2);
	//DDX_Text(pDX, IDE_INFO, m_cstrRemindInfo);
	//DDX_Check(pDX, IDCK_SHUTDOWN, m_bShutdown);
	//DDX_Check(pDX, IDCK_REST, m_bForceRest);
	DDX_Radio(pDX, IDR_TIMEUPACTION, m_iTimeupAction);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDB_START, &CMFCApplication1Dlg::OnBnClickedStart)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDE_HOUR, &CMFCApplication1Dlg::OnEnChangeHour)
	ON_EN_CHANGE(IDE_MIN, &CMFCApplication1Dlg::OnEnChangeMin)
	ON_EN_CHANGE(IDE_SEC, &CMFCApplication1Dlg::OnEnChangeSec)
	ON_BN_CLICKED(IDB_RESET, &CMFCApplication1Dlg::OnBnClickedReset)
	ON_BN_CLICKED(IDRB_COUNTDOWN, &CMFCApplication1Dlg::OnBnClickedCountdown)
	ON_BN_CLICKED(IDRB_ALARM, &CMFCApplication1Dlg::OnBnClickedCountdown)
	ON_BN_CLICKED(IDB_CLEAR, &CMFCApplication1Dlg::OnBnClickedClear)
	ON_EN_CHANGE(IDE_HOUR2, &CMFCApplication1Dlg::OnEnChangeHour2)
	ON_EN_CHANGE(IDE_MIN2, &CMFCApplication1Dlg::OnEnChangeMin2)
	ON_EN_CHANGE(IDE_SEC2, &CMFCApplication1Dlg::OnEnChangeSec2)
	ON_EN_CHANGE(IDE_INFO, &CMFCApplication1Dlg::OnEnChangeInfo)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_MESSAGE(WM_SHOWTASK, OnShowTask)     // 其中 WM_SHOWTASK 是消息名, OnShowTask 是自己定义的消息响应函数, 后面有说明. 
	//ON_BN_CLICKED(IDCK_SHUTDOWN, &CMFCApplication1Dlg::OnBnClickedShutdown)
	ON_WM_CLOSE()
	//ON_BN_CLICKED(IDCK_REST, &CMFCApplication1Dlg::OnBnClickedRest)
	ON_BN_CLICKED(IDR_TIMEUPACTION, &CMFCApplication1Dlg::OnBnClickedTimeupaction)
	ON_BN_CLICKED(IDR_TIMEUPACTION2, &CMFCApplication1Dlg::OnBnClickedTimeupaction)
	ON_BN_CLICKED(IDR_TIMEUPACTION3, &CMFCApplication1Dlg::OnBnClickedTimeupaction)
	ON_BN_CLICKED(IDR_TIMEUPACTION4, &CMFCApplication1Dlg::OnBnClickedTimeupaction)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	// TODO: 在此添加额外的初始化代码

	SetDlgItemText(IDE_INFO, m_cstrInfo);

	// 数值调节控件初始化
	m_spinHour1.SetRange32(0, 23);						// 设置范围
	m_spinHour1.SetBase(10);							// 设置数据的进制
	m_spinHour1.SetBuddy(GetDlgItem(IDE_HOUR));			// 设置伙伴控件
	m_spinHour1.SetPos(0);								// 设置默认显示

	m_spinMinute1.SetRange32(0, 59);					// 设置范围
	m_spinMinute1.SetBase(10);							// 设置数据的进制
	m_spinMinute1.SetBuddy(GetDlgItem(IDE_MIN));		// 设置伙伴控件
	m_spinMinute1.SetPos(45);							// 设置默认显示

	m_spinSecond1.SetRange32(0, 59);					// 设置范围
	m_spinSecond1.SetBase(10);							// 设置数据的进制
	m_spinSecond1.SetBuddy(GetDlgItem(IDE_SEC));		// 设置伙伴控件
	m_spinSecond1.SetPos(0);							// 设置默认显示

	m_spinHour2.SetRange32(0, 23);						// 设置范围
	m_spinHour2.SetBase(10);							// 设置数据的进制
	m_spinHour2.SetBuddy(GetDlgItem(IDE_HOUR2));		// 设置伙伴控件
	m_spinHour2.SetPos(0);								// 设置默认显示

	m_spinMinute2.SetRange32(0, 59);					// 设置范围
	m_spinMinute2.SetBase(10);							// 设置数据的进制
	m_spinMinute2.SetBuddy(GetDlgItem(IDE_MIN2));		// 设置伙伴控件
	m_spinMinute2.SetPos(0);							// 设置默认显示

	m_spinSecond2.SetRange32(0, 59);					// 设置范围
	m_spinSecond2.SetBase(10);							// 设置数据的进制
	m_spinSecond2.SetBuddy(GetDlgItem(IDE_SEC2));		// 设置伙伴控件
	m_spinSecond2.SetPos(0);							// 设置默认显示

	UpdateData(TRUE);
	GetRemainSeconds();									// 得到 m_seconds (控件上的时间计算出的秒数)
	UpdateControls();



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if (nID == SC_MINIMIZE)
	{
		ToTray(); //最小化到托盘的函数
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedStart()
{
	// TODO: 在此添加控件通知处理程序代码

	// 在倒计时功能时, 点击暂停
	if ( m_bPauseBtn && (0 == m_iCountDown) )
	{
		GetDlgItem(IDB_START)->SetWindowText(_T("Start"));
		CountDownPause();												// 暂停计时
		m_bPauseBtn = FALSE;											// 将"开始" 按钮置为 "开始" 功能 
		return;
	}

	// 在倒计时功能时, 点击开始/继续
	m_bPauseBtn = TRUE;													// 将"开始" 按钮置为 "暂停" 功能 
	m_bTiming = true;													// 是否启动倒计时/闹钟

	SYSTEMTIME LocalTime;												// 当前系统时间对象
	GetLocalTime(&LocalTime);
	UINT currentSeconds = LocalTime.wHour * 3600 + LocalTime.wMinute * 60 + LocalTime.wSecond;				// 当前系统时间 (秒)

	UpdateData();
	switch (m_iCountDown)
	{
	case 0:																// 倒计时
	default:
	{
		m_seconds = m_iHour * 3600 + m_iMinute * 60 + m_iSecond;
		if (1 == m_iFirstPress)
		{
			m_preSeconds = m_seconds;										// 保存当前的剩余时间 (秒), 用于结束计时后能保留上次设定的时间
			++m_iFirstPress;
		}
		UINT cdSeconds = (currentSeconds + m_seconds) % (24 * 3600);	// 在 "倒计时" 时间最后显示 "倒计时" 的终止时间
		m_cstrCountDown.Format(_T("%02d:%02d:%02d"), cdSeconds / 3600, (cdSeconds % 3600) / 60, cdSeconds % 60);
		SetDlgItemText(IDC_SCOUNTDOWN, m_cstrCountDown);
	}
	break;

	case 1:																// 闹钟
		m_seconds = m_iHour2 * 3600 + m_iMinute2 * 60 + m_iSecond2;		// 计算设定的闹钟距离今天 0 时的秒数
		if (m_seconds < currentSeconds)									// 小于当前时间, 则闹钟时间往后加 1 天
		{
			m_seconds += 24 * 3600;
		}
		m_seconds -= currentSeconds;									// 闹钟时间距离当前时间的秒数
		m_cstrCountDown.Format(_T("%02d:%02d:%02d"), m_seconds / 3600, (m_seconds % 3600) / 60, m_seconds % 60);	// 在 "闹钟" 时间最后显示 "倒计时" 距当前时间的距离
		SetDlgItemText(IDC_SALARM, m_cstrCountDown);
		break;
	}

	//m_preSeconds = m_seconds;											// 保存当前的剩余时间 (秒), 用于结束计时后能保留上次设定的时间

	//SYSTEMTIME LocalTime;
	//GetLocalTime(&LocalTime);
	//UINT currentSeconds = LocalTime.wHour * 3600 + LocalTime.wMinute * 60 + LocalTime.wSecond;

	//switch(m_iCountDown)
	//{
	//case 0:	// 倒计时
	//	{
	//		// 在 "倒计时"标签上显示 "倒计时" 的终止时间
	//		UINT cdSeconds = (currentSeconds + m_seconds) % (24 * 3600);
	//		m_cstrCountDown.Format(_T("%02d:%02d:%02d"), cdSeconds / 3600, (cdSeconds % 3600) / 60, cdSeconds % 60);
	//		SetDlgItemText(IDC_SCOUNTDOWN, m_cstrCountDown);
	//	}
	//	break;
	//case 1: // 闹钟
	//	if (m_seconds < currentSeconds)
	//	{
	//		m_seconds += 24 * 3600;					
	//	}
	//	m_seconds -= currentSeconds;
	//	m_cstrCountDown.Format(_T("%02d:%02d:%02d"), m_seconds / 3600, (m_seconds % 3600) / 60, m_seconds % 60);
	//	SetDlgItemText(IDC_SALARM, m_cstrCountDown);
	//	break;
	//default:
	//	break;
	//}

	UpdateControls();
	UpdateData(TRUE);
	SetTimer(1, 1000, NULL);											// 其中1是创建的定时器ID, 1000是每个1000毫秒触发一次定时器 (发送WM_TIMER消息) 
}


void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (1 == nIDEvent)
	{
		//UpdateData();
		--m_seconds;
		m_iSecond = m_seconds % 60;
		m_iMinute = (m_seconds % 3600) / 60;
		m_iHour = m_seconds / 3600;

		switch(m_iCountDown)
		{
		case 0:	// 更新倒计时时间
			UpdateData(FALSE);
			break;
		case 1: // 闹钟，更新剩余时间
			m_cstrCountDown.Format(_T("%02d:%02d:%02d"), m_iHour, m_iMinute, m_iSecond);
			SetDlgItemText(IDC_SALARM, m_cstrCountDown);
			break;
		default:
			break;
		}

		if(0 == m_seconds)								// 倒计时或闹钟时间到
		{
			m_bTiming = false;
			m_bPauseBtn = FALSE;						// 结束时恢复 "开始" 按钮的 "开始" 功能
			KillTimer(1);

			if (m_iCountDown == 0)						// 恢复本次设置的倒计时数值
			{
				m_seconds = m_preSeconds;
				m_iSecond = m_seconds % 60;
				m_iMinute = (m_seconds % 3600) / 60;
				m_iHour = m_seconds / 3600;
				UpdateData(FALSE);
			}

			//UpdateData(TRUE);

			switch (m_iTimeupAction)
			{
			case 0:														// 弹出提示, 不锁屏
			default:
				MessageBox(m_cstrInfo, _T("Info"), MB_ICONWARNING | MB_SYSTEMMODAL);
				break;
			case 1:														// 直接强制锁屏
				LockWorkStation();										// 锁屏, 相当于 win + L
				break;
			case 2:														// 按 'OK' 后锁屏
				if (IDOK == MessageBox(m_cstrInfo, _T("Info"), MB_ICONWARNING | MB_SYSTEMMODAL))
				{
					LockWorkStation();							
				}
				break;
			case 3:														// 勾选强制关机
				::AfxBeginThread(Shutdown, NULL);		// 创建一个 "5秒后关机" 的线程, 并执行
				if (IDNO == MessageBox(_T("Confirm shutdown (in 5s)?"), _T("Confirm"), MB_YESNO))
				{
					m_bCancelled = TRUE;								// 终止延时关机线程 (取消关机)
				}
				else
				{
					m_bCancelled = TRUE;								// 终止延时关机线程, 手动立即关机
					ShutDownNow();
				}
				break;
			}
			// 若勾选关机
			//if (m_bShutdown)							// 关机
			//if (3 == m_iTimeupAction)					// 若勾选强制关机
			//{
			//	::AfxBeginThread(Shutdown, NULL);		// 创建一个 "5秒后关机" 的线程, 并执行
			//	if (IDNO == MessageBox(_T("确定要关机吗(5 秒后自动关机)?"), _T("确认"), MB_YESNO))
			//	{
			//		m_bCancelled = TRUE;				// 终止延时关机线程 (取消关机)
			//	}
			//	else
			//	{
			//		m_bCancelled = TRUE;				// 终止延时关机线程, 手动立即关机
			//		ShutDownNow();
			//	}
			//	UpdateControls();
			//	return;
			//}

			// 若没有勾选关机. 弹出 "时间到" 提醒并锁屏
			// 若勾选 "强制休息", 则立即锁屏, 无提示
			//if (m_bForceRest)
			//{
			//	LockWorkStation();

			//} else if ( IDOK == MessageBox(m_cstrInfo, _T("信息"), MB_ICONWARNING|MB_SYSTEMMODAL) )	 // 没勾选 "强制休息", 则弹出提示
			//{
			//	LockWorkStation();							// 锁屏, 相当于 win + L
			//}

			UpdateControls();
			return;
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CMFCApplication1Dlg::UpdateControls(void)
{
	if (m_bTiming)
	{
		if (0 == m_iCountDown)			// 倒计时
		{
			GetDlgItem(IDB_START)->SetWindowText(_T("Pause"));
		}
		else 
		{
			((CButton*)GetDlgItem(IDB_START))->EnableWindow(FALSE);
		}
		((CButton*)GetDlgItem(IDB_RESET))->EnableWindow(TRUE); 
		((CButton*)GetDlgItem(IDB_CLEAR))->EnableWindow(FALSE); 
		((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN1))->EnableWindow(FALSE); 
		((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN2))->EnableWindow(FALSE); 
		((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN3))->EnableWindow(FALSE); 
		((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN4))->EnableWindow(FALSE); 
		((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN5))->EnableWindow(FALSE); 
		((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN6))->EnableWindow(FALSE); 
		((CEdit*)GetDlgItem(IDE_HOUR))->EnableWindow(FALSE); 
		((CEdit*)GetDlgItem(IDE_HOUR2))->EnableWindow(FALSE); 
		((CEdit*)GetDlgItem(IDE_MIN))->EnableWindow(FALSE); 
		((CEdit*)GetDlgItem(IDE_MIN2))->EnableWindow(FALSE); 
		((CEdit*)GetDlgItem(IDE_SEC))->EnableWindow(FALSE); 
		((CEdit*)GetDlgItem(IDE_SEC2))->EnableWindow(FALSE); 
		//((CEdit*)GetDlgItem(IDE_INFO))->EnableWindow(FALSE); 
		((CButton*)GetDlgItem(IDRB_COUNTDOWN))->EnableWindow(FALSE); 
		((CButton*)GetDlgItem(IDRB_ALARM))->EnableWindow(FALSE); 

	}
	else
	{
		UpdateData(TRUE);
		switch(m_iCountDown)
		{
		case 0:
			//((CButton*)GetDlgItem(IDRB_COUNTDOWN))->EnableWindow(TRUE); 
			//((CButton*)GetDlgItem(IDRB_ALARM))->EnableWindow(FALSE); 
			{
				((CEdit*)GetDlgItem(IDE_HOUR))->EnableWindow(TRUE); 
				((CEdit*)GetDlgItem(IDE_MIN))->EnableWindow(TRUE); 
				((CEdit*)GetDlgItem(IDE_SEC))->EnableWindow(TRUE); 
				((CEdit*)GetDlgItem(IDE_HOUR2))->EnableWindow(FALSE); 
				((CEdit*)GetDlgItem(IDE_SEC2))->EnableWindow(FALSE); 
				((CEdit*)GetDlgItem(IDE_MIN2))->EnableWindow(FALSE);
				((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN1))->EnableWindow(TRUE); 
				((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN2))->EnableWindow(TRUE); 
				((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN3))->EnableWindow(TRUE); 
				((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN4))->EnableWindow(FALSE); 
				((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN5))->EnableWindow(FALSE); 
				((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN6))->EnableWindow(FALSE); 
				//GetDlgItem(IDB_START)->SetWindowText(_T("开始"));
				SetDlgItemText(IDB_START, _T("Start"));
				BOOL enabled = (0 == m_seconds) ? FALSE : TRUE;
				((CButton*)GetDlgItem(IDB_START))->EnableWindow(enabled);				// 选择倒计时时, 设定时间为 0, 则 Start 按钮变灰 (没有计时时)
			}
			
			break;
		case 1:
			//((CButton*)GetDlgItem(IDRB_COUNTDOWN))->EnableWindow(FALSE); 
			//((CButton*)GetDlgItem(IDRB_ALARM))->EnableWindow(TRUE); 
			((CEdit*)GetDlgItem(IDE_HOUR))->EnableWindow(FALSE); 
			((CEdit*)GetDlgItem(IDE_MIN))->EnableWindow(FALSE); 
			((CEdit*)GetDlgItem(IDE_SEC))->EnableWindow(FALSE); 
			((CEdit*)GetDlgItem(IDE_HOUR2))->EnableWindow(TRUE); 
			((CEdit*)GetDlgItem(IDE_SEC2))->EnableWindow(TRUE); 
			((CEdit*)GetDlgItem(IDE_MIN2))->EnableWindow(TRUE); 
			((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN1))->EnableWindow(FALSE); 
			((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN2))->EnableWindow(FALSE); 
			((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN3))->EnableWindow(FALSE); 
			((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN4))->EnableWindow(TRUE); 
			((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN5))->EnableWindow(TRUE); 
			((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN6))->EnableWindow(TRUE); 
			((CButton*)GetDlgItem(IDB_START))->EnableWindow(TRUE);						// 选择闹钟时 start 不变灰 (没有计时时)

			break;
		default:
			break;
		}

		((CButton*)GetDlgItem(IDB_CLEAR))->EnableWindow(TRUE); 
		((CButton*)GetDlgItem(IDB_RESET))->EnableWindow(FALSE); 
		((CButton*)GetDlgItem(IDRB_COUNTDOWN))->EnableWindow(TRUE); 
		((CButton*)GetDlgItem(IDRB_ALARM))->EnableWindow(TRUE); 
		//((CEdit*)GetDlgItem(IDE_INFO))->EnableWindow(TRUE); 
		SetDlgItemText(IDC_SCOUNTDOWN, _T(""));				// 清空倒计时标签
		SetDlgItemText(IDC_SALARM, _T(""));					// 清空闹钟标签
	}
}


void CMFCApplication1Dlg::OnEnChangeHour()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(TRUE);
	m_seconds = m_iHour * 3600 + m_iMinute * 60 + m_iSecond;
	UpdateControls();

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication1Dlg::OnEnChangeMin()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	UpdateData(TRUE);
	m_seconds = m_iHour * 3600 + m_iMinute * 60 + m_iSecond;
	UpdateControls();

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication1Dlg::OnEnChangeSec()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	UpdateData(TRUE);
	m_seconds = m_iHour * 3600 + m_iMinute * 60 + m_iSecond;
	UpdateControls();

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication1Dlg::OnBnClickedReset()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
	m_bPauseBtn = FALSE;

	if (0 == m_iCountDown)
	{
		m_seconds = m_preSeconds;
		m_iSecond = m_seconds % 60;
		m_iMinute = (m_seconds % 3600) / 60;
		m_iHour = m_seconds / 3600;
		UpdateData(FALSE);
	}


	m_bTiming = false;
	SetDlgItemText(IDC_SCOUNTDOWN, _T(""));				// 清空倒计时标签
	SetDlgItemText(IDC_SALARM, _T(""));					// 清空闹钟标签
	m_iFirstPress = 1;							
	/*GetDlgItem(IDB_START)->SetWindowText(_T("开始"));*/
	UpdateControls();
}


void CMFCApplication1Dlg::OnBnClickedCountdown()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	//switch(m_iCountDown)
	//{
	//case 0:				// 倒计时
	//	m_seconds = m_iHour * 3600 + m_iMinute * 60 + m_iSecond;
	//	break;
	//case 1:				// 闹钟
	//	m_seconds = m_iHour2 * 3600 + m_iMinute2 * 60 + m_iSecond2;		// 计算距午夜的时间
	//	break;
	//default:
	//	m_seconds = m_iHour * 3600 + m_iMinute * 60 + m_iSecond;
	//	break;
	//}

	//if (0 == m_iCountDown)
	//{
	//	m_preSeconds = m_seconds;											// 保存当前的剩余时间 (秒), 用于结束计时后能保留上次设定的时间
	//}

	UpdateControls();
}



void CMFCApplication1Dlg::OnBnClickedClear()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_iHour = 0;
	m_iHour2 = 0;
	m_iMinute = 0;
	m_iMinute2 = 0;
	m_iSecond = 0;
	m_iSecond2 = 0;
	m_seconds = 0;
	UpdateData(FALSE);
	UpdateControls();
}


void CMFCApplication1Dlg::OnEnChangeHour2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);
	m_seconds = m_iHour2 * 3600 + m_iMinute2 * 60 + m_iSecond2;
	UpdateControls();
}


void CMFCApplication1Dlg::OnEnChangeMin2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	UpdateData(TRUE);
	m_seconds = m_iHour2 * 3600 + m_iMinute2 * 60 + m_iSecond2;
	UpdateControls();

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication1Dlg::OnEnChangeSec2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	UpdateData(TRUE);
	m_seconds = m_iHour2 * 3600 + m_iMinute2 * 60 + m_iSecond2;
	UpdateControls();

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication1Dlg::OnEnChangeInfo()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	

	// TODO:  在此添加控件通知处理程序代码
	GetDlgItemText(IDE_INFO, m_cstrInfo);
}


void CMFCApplication1Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_isMouseDown = TRUE;
	m_startPoint = point;
	this->GetWindowRect(m_startRect);

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCApplication1Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (TRUE == m_isMouseDown)
	{
		int Dx = point.x - m_startPoint.x;
		int Dy = point.y - m_startPoint.y;
		m_startRect.left += Dx;
		m_startRect.right += Dx;
		m_startRect.top += Dy;
		m_startRect.bottom +=Dy;             // 获取新的位置
		this->MoveWindow(&m_startRect);      // 将窗口移到新的位置
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CMFCApplication1Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_isMouseDown = FALSE;
	CDialogEx::OnLButtonUp(nFlags, point);
}

// 最小化到托盘函数
void CMFCApplication1Dlg::ToTray()
{
    NOTIFYICONDATA nid;
    nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
    nid.hWnd = this->m_hWnd;
    nid.uID = IDR_MAINFRAME;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_SHOWTASK; // 自定义的消息名称, 这里定义了托盘响应消息.当用户用鼠标点击托盘区的图标的时候 (无论是左键还是右键),会向hWnd所代表的窗口传送消息. 
    nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));

    wcscpy_s(nid.szTip, _T(TOOLTIPS_NAME_));                                                    // 信息提示条
    Shell_NotifyIcon(NIM_ADD, &nid);                                                            // 在托盘区添加图标
    ShowWindow(SW_HIDE);                                                                        // 隐藏主窗口
}

// 删除托盘图标函数
void CMFCApplication1Dlg::DeleteTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP ;
	nid.uCallbackMessage = WM_SHOWTASK;															// 自定义的消息名称
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	wcscpy_s(nid.szTip, _T("Alarm"));													    // 信息提示条为“计划任务提醒”
	Shell_NotifyIcon(NIM_DELETE,&nid);															// 在托盘区删除图标
}


// 恢复界面函数. wParam 接收的是图标的 ID, 而 lParam 接收的是鼠标的行为
LRESULT CMFCApplication1Dlg::OnShowTask(WPARAM wParam, LPARAM lParam)
{
	if(wParam != IDR_MAINFRAME)
		return 1;

	switch(lParam)
	{
	case WM_RBUTTONUP:											// 右键起来时弹出快捷菜单, 这里只有一个 "关闭" 
		{
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint);								// 得到鼠标位置

			CMenu menu;
			menu.CreatePopupMenu();											// 声明一个弹出式菜单
			//menu.AppendMenu(MF_STRING, WM_DESTROY, _T("退出"));				// 增加菜单项"退出", 点击则发送消息 WM_DESTROY 给主窗口 (已隐藏), 将程序结束. 			
			menu.AppendMenu(MF_STRING, IDOK, _T("Exit"));				// 增加菜单项"退出", 点击则发送消息 WM_DESTROY 给主窗口 (已隐藏), 将程序结束. 			
			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this); // 确定弹出式菜单的位置

			HMENU hmenu = menu.Detach();
			menu.DestroyMenu(); //资源回收
			delete lpoint;
		}
		break;
	case WM_LBUTTONDBLCLK: // 双击左键的处理
	case WM_LBUTTONDOWN:   // 单击左键的处理
		this->ShowWindow(SW_SHOW);										// 简单的显示主窗口完事儿
		//DeleteTray();													// 这里不删也可以, 没必要把图标从任务栏删掉
		break;
	default: 
		break;
	}

	return 0;
}


// 关机
UINT CMFCApplication1Dlg::Shutdown(LPVOID pParam)
{
	//Sleep(2000);

	// 等待 5 秒
	UINT sec = 5;								// 最多等待 5 秒
	UINT interval = 100;						// 每次休眠间隔 100ms
	UINT count = sec * 1000 / interval;
	while (--count > 0)
	{
		Sleep(interval);
		if (m_bCancelled)						// 判断用户是否按下取消键
			return 1;
	}
	
	ShutDownNow();								// 立即关机

	return 0;									// 线程返回值，线程最好通过返回值退出线程，这样会释放线程所有资源
}


// 立即关机
void CMFCApplication1Dlg::ShutDownNow(void)
{
	// 1. 打开令牌
    HANDLE hToken;//创建令牌句柄
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &hToken))   //打开令牌句柄，设置令牌权限
    {
        AfxMessageBox(_T("OpenProcessToken Error."));
        return;
    }

    // 2. 返回系统权限的特权值?(LUID), Leo.
    TOKEN_PRIVILEGES tkp;                                                       // 结构体包括 LUID 和特权的属性
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);      // 查看令牌权限
    tkp.PrivilegeCount = 1;                                                     // 设置元素的个数
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;                        // 设置元素的权限. SE_PRIVILEGE_ENABLED: 特权启用

    //3. 修改用户权限. FALSE: 开启权限?, Leo
    AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);  // 修改用户权限的函数

    if (GetLastError() != ERROR_SUCCESS)
    {
        AfxMessageBox(_T("AdjustTokenPrivileges Error"));
        return;
    }

	// InitiateSystemShutdownEx ?
    if (!ExitWindowsEx(EWX_SHUTDOWN, 0))
    {
        AfxMessageBox(_T("ExitWindowsEx Error"));
    }
}


void CMFCApplication1Dlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	EndDialog(IDCANCEL);
	CDialogEx::OnClose();
	//CDialog::OnClose();
}



// 暂停计时
void CMFCApplication1Dlg::CountDownPause()
{
	GetDlgItem(IDB_START)->SetWindowText(_T("Resume"));
	KillTimer(1);
}

// 得到 m_seconds
void CMFCApplication1Dlg::GetRemainSeconds()
{
	switch (m_iCountDown)
	{
	case 0:				// 倒计时
		m_seconds = m_iHour * 3600 + m_iMinute * 60 + m_iSecond;
		break;
	case 1:				// 闹钟
		m_seconds = m_iHour2 * 3600 + m_iMinute2 * 60 + m_iSecond2;		// 计算距午夜的时间
		break;
	default:
		m_seconds = m_iHour * 3600 + m_iMinute * 60 + m_iSecond;
		break;
	}
}

void CMFCApplication1Dlg::OnBnClickedTimeupaction()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	//int x = m_iTimeupAction;
}
