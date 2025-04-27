
// MFCApplication1Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "atltypes.h"

#define WM_SHOWTASK (WM_USER + 1)
#define TOOLTIPS_NAME_ "Alarm"


// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	INT m_iCountDown;							// 单选框(倒计时、闹钟)关联的整数
	CSpinButtonCtrl m_spinHour1;
	CSpinButtonCtrl m_spinMinute1;
	CSpinButtonCtrl m_spinSecond1;
	afx_msg void OnBnClickedStart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_iHour;								// "倒计时" 小时
	int m_iMinute;
	int m_iSecond;
	unsigned int m_seconds;						// 还剩的时间 (秒)
	afx_msg void OnEnChangeHour();
private:
	void UpdateControls(void);
	void ToTray();								// 最小化到托盘
	void DeleteTray();
	static UINT Shutdown(LPVOID pParam);				//关机
	//virtual void OnOK(){};
	virtual void OnCancel(){};


public:
	afx_msg void OnEnChangeMin();
	afx_msg void OnEnChangeSec();
	afx_msg void OnBnClickedReset();
	unsigned int m_preSeconds;
private:
	bool m_bTiming;								//  正在倒计时 (闹钟或倒计时)
	int m_iHour2;								// "闹钟" 小时
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
	//CString m_cstrRemindInfo;					// 闹钟响后的提醒消息 (与控件关联的), 没有用到
	CString m_cstrInfo;							// 闹钟响后的提醒消息
	//BOOL m_bShutdown;							// 是否关机
	//BOOL m_bForceRest;							// 是否强制休息 (时间到后强制锁屏)
	BOOL m_bPauseBtn;							// "开始" 按钮是否变为了 "暂停" 按钮
	CString m_cstrCountDown;				    // 倒计时响铃的时间
public:
	afx_msg void OnEnChangeInfo();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	BOOL m_isMouseDown;							// 鼠标是否按下
	CPoint m_startPoint;						// 鼠标是否按下
	CRect m_startRect;							// 窗口的初始位置所在的矩形
	static BOOL m_bCancelled;					// 取消关机
	static void ShutDownNow(void);				// 立即关机
	void CountDownPause();						// 暂停计时
	void GetRemainSeconds();					// 得到控件上的秒数
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam);
	//afx_msg void OnBnClickedShutdown();
	afx_msg void OnClose();
	//afx_msg void OnBnClickedRest();
private:
	INT m_iTimeupAction;						// 时间到后的行为 (time up action)
	UINT m_iFirstPress;							// 按 Start 按钮的次数, 初始值为 1
public:
	afx_msg void OnBnClickedTimeupaction();
};
