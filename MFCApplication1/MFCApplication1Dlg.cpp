
// MFCApplication1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg �Ի���

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
	//, m_cstrRemindInfo(_T("��Ϣһ��!"))
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
	ON_MESSAGE(WM_SHOWTASK, OnShowTask)     // ���� WM_SHOWTASK ����Ϣ��, OnShowTask ���Լ��������Ϣ��Ӧ����, ������˵��. 
	//ON_BN_CLICKED(IDCK_SHUTDOWN, &CMFCApplication1Dlg::OnBnClickedShutdown)
	ON_WM_CLOSE()
	//ON_BN_CLICKED(IDCK_REST, &CMFCApplication1Dlg::OnBnClickedRest)
	ON_BN_CLICKED(IDR_TIMEUPACTION, &CMFCApplication1Dlg::OnBnClickedTimeupaction)
	ON_BN_CLICKED(IDR_TIMEUPACTION2, &CMFCApplication1Dlg::OnBnClickedTimeupaction)
	ON_BN_CLICKED(IDR_TIMEUPACTION3, &CMFCApplication1Dlg::OnBnClickedTimeupaction)
	ON_BN_CLICKED(IDR_TIMEUPACTION4, &CMFCApplication1Dlg::OnBnClickedTimeupaction)
END_MESSAGE_MAP()


// CMFCApplication1Dlg ��Ϣ�������

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	SetDlgItemText(IDE_INFO, m_cstrInfo);

	// ��ֵ���ڿؼ���ʼ��
	m_spinHour1.SetRange32(0, 23);						// ���÷�Χ
	m_spinHour1.SetBase(10);							// �������ݵĽ���
	m_spinHour1.SetBuddy(GetDlgItem(IDE_HOUR));			// ���û��ؼ�
	m_spinHour1.SetPos(0);								// ����Ĭ����ʾ

	m_spinMinute1.SetRange32(0, 59);					// ���÷�Χ
	m_spinMinute1.SetBase(10);							// �������ݵĽ���
	m_spinMinute1.SetBuddy(GetDlgItem(IDE_MIN));		// ���û��ؼ�
	m_spinMinute1.SetPos(45);							// ����Ĭ����ʾ

	m_spinSecond1.SetRange32(0, 59);					// ���÷�Χ
	m_spinSecond1.SetBase(10);							// �������ݵĽ���
	m_spinSecond1.SetBuddy(GetDlgItem(IDE_SEC));		// ���û��ؼ�
	m_spinSecond1.SetPos(0);							// ����Ĭ����ʾ

	m_spinHour2.SetRange32(0, 23);						// ���÷�Χ
	m_spinHour2.SetBase(10);							// �������ݵĽ���
	m_spinHour2.SetBuddy(GetDlgItem(IDE_HOUR2));		// ���û��ؼ�
	m_spinHour2.SetPos(0);								// ����Ĭ����ʾ

	m_spinMinute2.SetRange32(0, 59);					// ���÷�Χ
	m_spinMinute2.SetBase(10);							// �������ݵĽ���
	m_spinMinute2.SetBuddy(GetDlgItem(IDE_MIN2));		// ���û��ؼ�
	m_spinMinute2.SetPos(0);							// ����Ĭ����ʾ

	m_spinSecond2.SetRange32(0, 59);					// ���÷�Χ
	m_spinSecond2.SetBase(10);							// �������ݵĽ���
	m_spinSecond2.SetBuddy(GetDlgItem(IDE_SEC2));		// ���û��ؼ�
	m_spinSecond2.SetPos(0);							// ����Ĭ����ʾ

	UpdateData(TRUE);
	GetRemainSeconds();									// �õ� m_seconds (�ؼ��ϵ�ʱ������������)
	UpdateControls();



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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
		ToTray(); //��С�������̵ĺ���
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// �ڵ���ʱ����ʱ, �����ͣ
	if ( m_bPauseBtn && (0 == m_iCountDown) )
	{
		GetDlgItem(IDB_START)->SetWindowText(_T("Start"));
		CountDownPause();												// ��ͣ��ʱ
		m_bPauseBtn = FALSE;											// ��"��ʼ" ��ť��Ϊ "��ʼ" ���� 
		return;
	}

	// �ڵ���ʱ����ʱ, �����ʼ/����
	m_bPauseBtn = TRUE;													// ��"��ʼ" ��ť��Ϊ "��ͣ" ���� 
	m_bTiming = true;													// �Ƿ���������ʱ/����

	SYSTEMTIME LocalTime;												// ��ǰϵͳʱ�����
	GetLocalTime(&LocalTime);
	UINT currentSeconds = LocalTime.wHour * 3600 + LocalTime.wMinute * 60 + LocalTime.wSecond;				// ��ǰϵͳʱ�� (��)

	UpdateData();
	switch (m_iCountDown)
	{
	case 0:																// ����ʱ
	default:
	{
		m_seconds = m_iHour * 3600 + m_iMinute * 60 + m_iSecond;
		if (1 == m_iFirstPress)
		{
			m_preSeconds = m_seconds;										// ���浱ǰ��ʣ��ʱ�� (��), ���ڽ�����ʱ���ܱ����ϴ��趨��ʱ��
			++m_iFirstPress;
		}
		UINT cdSeconds = (currentSeconds + m_seconds) % (24 * 3600);	// �� "����ʱ" ʱ�������ʾ "����ʱ" ����ֹʱ��
		m_cstrCountDown.Format(_T("%02d:%02d:%02d"), cdSeconds / 3600, (cdSeconds % 3600) / 60, cdSeconds % 60);
		SetDlgItemText(IDC_SCOUNTDOWN, m_cstrCountDown);
	}
	break;

	case 1:																// ����
		m_seconds = m_iHour2 * 3600 + m_iMinute2 * 60 + m_iSecond2;		// �����趨�����Ӿ������ 0 ʱ������
		if (m_seconds < currentSeconds)									// С�ڵ�ǰʱ��, ������ʱ������� 1 ��
		{
			m_seconds += 24 * 3600;
		}
		m_seconds -= currentSeconds;									// ����ʱ����뵱ǰʱ�������
		m_cstrCountDown.Format(_T("%02d:%02d:%02d"), m_seconds / 3600, (m_seconds % 3600) / 60, m_seconds % 60);	// �� "����" ʱ�������ʾ "����ʱ" �൱ǰʱ��ľ���
		SetDlgItemText(IDC_SALARM, m_cstrCountDown);
		break;
	}

	//m_preSeconds = m_seconds;											// ���浱ǰ��ʣ��ʱ�� (��), ���ڽ�����ʱ���ܱ����ϴ��趨��ʱ��

	//SYSTEMTIME LocalTime;
	//GetLocalTime(&LocalTime);
	//UINT currentSeconds = LocalTime.wHour * 3600 + LocalTime.wMinute * 60 + LocalTime.wSecond;

	//switch(m_iCountDown)
	//{
	//case 0:	// ����ʱ
	//	{
	//		// �� "����ʱ"��ǩ����ʾ "����ʱ" ����ֹʱ��
	//		UINT cdSeconds = (currentSeconds + m_seconds) % (24 * 3600);
	//		m_cstrCountDown.Format(_T("%02d:%02d:%02d"), cdSeconds / 3600, (cdSeconds % 3600) / 60, cdSeconds % 60);
	//		SetDlgItemText(IDC_SCOUNTDOWN, m_cstrCountDown);
	//	}
	//	break;
	//case 1: // ����
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
	SetTimer(1, 1000, NULL);											// ����1�Ǵ����Ķ�ʱ��ID, 1000��ÿ��1000���봥��һ�ζ�ʱ�� (����WM_TIMER��Ϣ) 
}


void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (1 == nIDEvent)
	{
		//UpdateData();
		--m_seconds;
		m_iSecond = m_seconds % 60;
		m_iMinute = (m_seconds % 3600) / 60;
		m_iHour = m_seconds / 3600;

		switch(m_iCountDown)
		{
		case 0:	// ���µ���ʱʱ��
			UpdateData(FALSE);
			break;
		case 1: // ���ӣ�����ʣ��ʱ��
			m_cstrCountDown.Format(_T("%02d:%02d:%02d"), m_iHour, m_iMinute, m_iSecond);
			SetDlgItemText(IDC_SALARM, m_cstrCountDown);
			break;
		default:
			break;
		}

		if(0 == m_seconds)								// ����ʱ������ʱ�䵽
		{
			m_bTiming = false;
			m_bPauseBtn = FALSE;						// ����ʱ�ָ� "��ʼ" ��ť�� "��ʼ" ����
			KillTimer(1);

			if (m_iCountDown == 0)						// �ָ��������õĵ���ʱ��ֵ
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
			case 0:														// ������ʾ, ������
			default:
				MessageBox(m_cstrInfo, _T("Info"), MB_ICONWARNING | MB_SYSTEMMODAL);
				break;
			case 1:														// ֱ��ǿ������
				LockWorkStation();										// ����, �൱�� win + L
				break;
			case 2:														// �� 'OK' ������
				if (IDOK == MessageBox(m_cstrInfo, _T("Info"), MB_ICONWARNING | MB_SYSTEMMODAL))
				{
					LockWorkStation();							
				}
				break;
			case 3:														// ��ѡǿ�ƹػ�
				::AfxBeginThread(Shutdown, NULL);		// ����һ�� "5���ػ�" ���߳�, ��ִ��
				if (IDNO == MessageBox(_T("Confirm shutdown (in 5s)?"), _T("Confirm"), MB_YESNO))
				{
					m_bCancelled = TRUE;								// ��ֹ��ʱ�ػ��߳� (ȡ���ػ�)
				}
				else
				{
					m_bCancelled = TRUE;								// ��ֹ��ʱ�ػ��߳�, �ֶ������ػ�
					ShutDownNow();
				}
				break;
			}
			// ����ѡ�ػ�
			//if (m_bShutdown)							// �ػ�
			//if (3 == m_iTimeupAction)					// ����ѡǿ�ƹػ�
			//{
			//	::AfxBeginThread(Shutdown, NULL);		// ����һ�� "5���ػ�" ���߳�, ��ִ��
			//	if (IDNO == MessageBox(_T("ȷ��Ҫ�ػ���(5 ����Զ��ػ�)?"), _T("ȷ��"), MB_YESNO))
			//	{
			//		m_bCancelled = TRUE;				// ��ֹ��ʱ�ػ��߳� (ȡ���ػ�)
			//	}
			//	else
			//	{
			//		m_bCancelled = TRUE;				// ��ֹ��ʱ�ػ��߳�, �ֶ������ػ�
			//		ShutDownNow();
			//	}
			//	UpdateControls();
			//	return;
			//}

			// ��û�й�ѡ�ػ�. ���� "ʱ�䵽" ���Ѳ�����
			// ����ѡ "ǿ����Ϣ", ����������, ����ʾ
			//if (m_bForceRest)
			//{
			//	LockWorkStation();

			//} else if ( IDOK == MessageBox(m_cstrInfo, _T("��Ϣ"), MB_ICONWARNING|MB_SYSTEMMODAL) )	 // û��ѡ "ǿ����Ϣ", �򵯳���ʾ
			//{
			//	LockWorkStation();							// ����, �൱�� win + L
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
		if (0 == m_iCountDown)			// ����ʱ
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
				//GetDlgItem(IDB_START)->SetWindowText(_T("��ʼ"));
				SetDlgItemText(IDB_START, _T("Start"));
				BOOL enabled = (0 == m_seconds) ? FALSE : TRUE;
				((CButton*)GetDlgItem(IDB_START))->EnableWindow(enabled);				// ѡ�񵹼�ʱʱ, �趨ʱ��Ϊ 0, �� Start ��ť��� (û�м�ʱʱ)
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
			((CButton*)GetDlgItem(IDB_START))->EnableWindow(TRUE);						// ѡ������ʱ start ����� (û�м�ʱʱ)

			break;
		default:
			break;
		}

		((CButton*)GetDlgItem(IDB_CLEAR))->EnableWindow(TRUE); 
		((CButton*)GetDlgItem(IDB_RESET))->EnableWindow(FALSE); 
		((CButton*)GetDlgItem(IDRB_COUNTDOWN))->EnableWindow(TRUE); 
		((CButton*)GetDlgItem(IDRB_ALARM))->EnableWindow(TRUE); 
		//((CEdit*)GetDlgItem(IDE_INFO))->EnableWindow(TRUE); 
		SetDlgItemText(IDC_SCOUNTDOWN, _T(""));				// ��յ���ʱ��ǩ
		SetDlgItemText(IDC_SALARM, _T(""));					// ������ӱ�ǩ
	}
}


void CMFCApplication1Dlg::OnEnChangeHour()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	UpdateData(TRUE);
	m_seconds = m_iHour * 3600 + m_iMinute * 60 + m_iSecond;
	UpdateControls();

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication1Dlg::OnEnChangeMin()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	UpdateData(TRUE);
	m_seconds = m_iHour * 3600 + m_iMinute * 60 + m_iSecond;
	UpdateControls();

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication1Dlg::OnEnChangeSec()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	UpdateData(TRUE);
	m_seconds = m_iHour * 3600 + m_iMinute * 60 + m_iSecond;
	UpdateControls();

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication1Dlg::OnBnClickedReset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	SetDlgItemText(IDC_SCOUNTDOWN, _T(""));				// ��յ���ʱ��ǩ
	SetDlgItemText(IDC_SALARM, _T(""));					// ������ӱ�ǩ
	m_iFirstPress = 1;							
	/*GetDlgItem(IDB_START)->SetWindowText(_T("��ʼ"));*/
	UpdateControls();
}


void CMFCApplication1Dlg::OnBnClickedCountdown()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	//switch(m_iCountDown)
	//{
	//case 0:				// ����ʱ
	//	m_seconds = m_iHour * 3600 + m_iMinute * 60 + m_iSecond;
	//	break;
	//case 1:				// ����
	//	m_seconds = m_iHour2 * 3600 + m_iMinute2 * 60 + m_iSecond2;		// �������ҹ��ʱ��
	//	break;
	//default:
	//	m_seconds = m_iHour * 3600 + m_iMinute * 60 + m_iSecond;
	//	break;
	//}

	//if (0 == m_iCountDown)
	//{
	//	m_preSeconds = m_seconds;											// ���浱ǰ��ʣ��ʱ�� (��), ���ڽ�����ʱ���ܱ����ϴ��趨��ʱ��
	//}

	UpdateControls();
}



void CMFCApplication1Dlg::OnBnClickedClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
	m_seconds = m_iHour2 * 3600 + m_iMinute2 * 60 + m_iSecond2;
	UpdateControls();
}


void CMFCApplication1Dlg::OnEnChangeMin2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	UpdateData(TRUE);
	m_seconds = m_iHour2 * 3600 + m_iMinute2 * 60 + m_iSecond2;
	UpdateControls();

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication1Dlg::OnEnChangeSec2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	UpdateData(TRUE);
	m_seconds = m_iHour2 * 3600 + m_iMinute2 * 60 + m_iSecond2;
	UpdateControls();

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication1Dlg::OnEnChangeInfo()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDE_INFO, m_cstrInfo);
}


void CMFCApplication1Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_isMouseDown = TRUE;
	m_startPoint = point;
	this->GetWindowRect(m_startRect);

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCApplication1Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (TRUE == m_isMouseDown)
	{
		int Dx = point.x - m_startPoint.x;
		int Dy = point.y - m_startPoint.y;
		m_startRect.left += Dx;
		m_startRect.right += Dx;
		m_startRect.top += Dy;
		m_startRect.bottom +=Dy;             // ��ȡ�µ�λ��
		this->MoveWindow(&m_startRect);      // �������Ƶ��µ�λ��
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CMFCApplication1Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_isMouseDown = FALSE;
	CDialogEx::OnLButtonUp(nFlags, point);
}

// ��С�������̺���
void CMFCApplication1Dlg::ToTray()
{
    NOTIFYICONDATA nid;
    nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
    nid.hWnd = this->m_hWnd;
    nid.uID = IDR_MAINFRAME;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_SHOWTASK; // �Զ������Ϣ����, ���ﶨ����������Ӧ��Ϣ.���û����������������ͼ���ʱ�� (��������������Ҽ�),����hWnd������Ĵ��ڴ�����Ϣ. 
    nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));

    wcscpy_s(nid.szTip, _T(TOOLTIPS_NAME_));                                                    // ��Ϣ��ʾ��
    Shell_NotifyIcon(NIM_ADD, &nid);                                                            // �����������ͼ��
    ShowWindow(SW_HIDE);                                                                        // ����������
}

// ɾ������ͼ�꺯��
void CMFCApplication1Dlg::DeleteTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP ;
	nid.uCallbackMessage = WM_SHOWTASK;															// �Զ������Ϣ����
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	wcscpy_s(nid.szTip, _T("Alarm"));													    // ��Ϣ��ʾ��Ϊ���ƻ��������ѡ�
	Shell_NotifyIcon(NIM_DELETE,&nid);															// ��������ɾ��ͼ��
}


// �ָ����溯��. wParam ���յ���ͼ��� ID, �� lParam ���յ���������Ϊ
LRESULT CMFCApplication1Dlg::OnShowTask(WPARAM wParam, LPARAM lParam)
{
	if(wParam != IDR_MAINFRAME)
		return 1;

	switch(lParam)
	{
	case WM_RBUTTONUP:											// �Ҽ�����ʱ������ݲ˵�, ����ֻ��һ�� "�ر�" 
		{
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint);								// �õ����λ��

			CMenu menu;
			menu.CreatePopupMenu();											// ����һ������ʽ�˵�
			//menu.AppendMenu(MF_STRING, WM_DESTROY, _T("�˳�"));				// ���Ӳ˵���"�˳�", ���������Ϣ WM_DESTROY �������� (������), ���������. 			
			menu.AppendMenu(MF_STRING, IDOK, _T("Exit"));				// ���Ӳ˵���"�˳�", ���������Ϣ WM_DESTROY �������� (������), ���������. 			
			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this); // ȷ������ʽ�˵���λ��

			HMENU hmenu = menu.Detach();
			menu.DestroyMenu(); //��Դ����
			delete lpoint;
		}
		break;
	case WM_LBUTTONDBLCLK: // ˫������Ĵ���
	case WM_LBUTTONDOWN:   // ��������Ĵ���
		this->ShowWindow(SW_SHOW);										// �򵥵���ʾ���������¶�
		//DeleteTray();													// ���ﲻɾҲ����, û��Ҫ��ͼ���������ɾ��
		break;
	default: 
		break;
	}

	return 0;
}


// �ػ�
UINT CMFCApplication1Dlg::Shutdown(LPVOID pParam)
{
	//Sleep(2000);

	// �ȴ� 5 ��
	UINT sec = 5;								// ���ȴ� 5 ��
	UINT interval = 100;						// ÿ�����߼�� 100ms
	UINT count = sec * 1000 / interval;
	while (--count > 0)
	{
		Sleep(interval);
		if (m_bCancelled)						// �ж��û��Ƿ���ȡ����
			return 1;
	}
	
	ShutDownNow();								// �����ػ�

	return 0;									// �̷߳���ֵ���߳����ͨ������ֵ�˳��̣߳��������ͷ��߳�������Դ
}


// �����ػ�
void CMFCApplication1Dlg::ShutDownNow(void)
{
	// 1. ������
    HANDLE hToken;//�������ƾ��
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &hToken))   //�����ƾ������������Ȩ��
    {
        AfxMessageBox(_T("OpenProcessToken Error."));
        return;
    }

    // 2. ����ϵͳȨ�޵���Ȩֵ?(LUID), Leo.
    TOKEN_PRIVILEGES tkp;                                                       // �ṹ����� LUID ����Ȩ������
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);      // �鿴����Ȩ��
    tkp.PrivilegeCount = 1;                                                     // ����Ԫ�صĸ���
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;                        // ����Ԫ�ص�Ȩ��. SE_PRIVILEGE_ENABLED: ��Ȩ����

    //3. �޸��û�Ȩ��. FALSE: ����Ȩ��?, Leo
    AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);  // �޸��û�Ȩ�޵ĺ���

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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	EndDialog(IDCANCEL);
	CDialogEx::OnClose();
	//CDialog::OnClose();
}



// ��ͣ��ʱ
void CMFCApplication1Dlg::CountDownPause()
{
	GetDlgItem(IDB_START)->SetWindowText(_T("Resume"));
	KillTimer(1);
}

// �õ� m_seconds
void CMFCApplication1Dlg::GetRemainSeconds()
{
	switch (m_iCountDown)
	{
	case 0:				// ����ʱ
		m_seconds = m_iHour * 3600 + m_iMinute * 60 + m_iSecond;
		break;
	case 1:				// ����
		m_seconds = m_iHour2 * 3600 + m_iMinute2 * 60 + m_iSecond2;		// �������ҹ��ʱ��
		break;
	default:
		m_seconds = m_iHour * 3600 + m_iMinute * 60 + m_iSecond;
		break;
	}
}

void CMFCApplication1Dlg::OnBnClickedTimeupaction()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	//int x = m_iTimeupAction;
}
