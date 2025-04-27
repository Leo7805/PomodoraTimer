
// MFCApplication1Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "atltypes.h"

#define WM_SHOWTASK (WM_USER + 1)
#define TOOLTIPS_NAME_ "Alarm"


// CMFCApplication1Dlg �Ի���
class CMFCApplication1Dlg : public CDialogEx
{
// ����
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	INT m_iCountDown;							// ��ѡ��(����ʱ������)����������
	CSpinButtonCtrl m_spinHour1;
	CSpinButtonCtrl m_spinMinute1;
	CSpinButtonCtrl m_spinSecond1;
	afx_msg void OnBnClickedStart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_iHour;								// "����ʱ" Сʱ
	int m_iMinute;
	int m_iSecond;
	unsigned int m_seconds;						// ��ʣ��ʱ�� (��)
	afx_msg void OnEnChangeHour();
private:
	void UpdateControls(void);
	void ToTray();								// ��С��������
	void DeleteTray();
	static UINT Shutdown(LPVOID pParam);				//�ػ�
	//virtual void OnOK(){};
	virtual void OnCancel(){};


public:
	afx_msg void OnEnChangeMin();
	afx_msg void OnEnChangeSec();
	afx_msg void OnBnClickedReset();
	unsigned int m_preSeconds;
private:
	bool m_bTiming;								//  ���ڵ���ʱ (���ӻ򵹼�ʱ)
	int m_iHour2;								// "����" Сʱ
	int m_iMinute2;
	int m_iSecond2;
	CSpinButtonCtrl m_spinHour2;
	CSpinButtonCtrl m_spinMinute2;
	CSpinButtonCtrl m_spinSecond2;
public:
	afx_msg void OnBnClickedCountdown();
	afx_msg void OnBnClickedClear();
	afx_msg void OnEnChangeHour2();
	afx_msg void OnEnChangeMin2();
	afx_msg void OnEnChangeSec2();
private:
	//CString m_cstrRemindInfo;					// ��������������Ϣ (��ؼ�������), û���õ�
	CString m_cstrInfo;							// ��������������Ϣ
	//BOOL m_bShutdown;							// �Ƿ�ػ�
	//BOOL m_bForceRest;							// �Ƿ�ǿ����Ϣ (ʱ�䵽��ǿ������)
	BOOL m_bPauseBtn;							// "��ʼ" ��ť�Ƿ��Ϊ�� "��ͣ" ��ť
	CString m_cstrCountDown;				    // ����ʱ�����ʱ��
public:
	afx_msg void OnEnChangeInfo();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	BOOL m_isMouseDown;							// ����Ƿ���
	CPoint m_startPoint;						// ����Ƿ���
	CRect m_startRect;							// ���ڵĳ�ʼλ�����ڵľ���
	static BOOL m_bCancelled;					// ȡ���ػ�
	static void ShutDownNow(void);				// �����ػ�
	void CountDownPause();						// ��ͣ��ʱ
	void GetRemainSeconds();					// �õ��ؼ��ϵ�����
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam);
	//afx_msg void OnBnClickedShutdown();
	afx_msg void OnClose();
	//afx_msg void OnBnClickedRest();
private:
	INT m_iTimeupAction;						// ʱ�䵽�����Ϊ (time up action)
	UINT m_iFirstPress;							// �� Start ��ť�Ĵ���, ��ʼֵΪ 1
public:
	afx_msg void OnBnClickedTimeupaction();
};
