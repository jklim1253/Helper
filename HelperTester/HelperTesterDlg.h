
// HelperTesterDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CHelperTesterDlg 대화 상자
class CHelperTesterDlg : public CDialog
{
// 생성입니다.
public:
	CHelperTesterDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_HELPERTESTER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
private:
	void UpdateLayout(void);
	CEdit m_ctrlValueEdit;
	CButton m_ctrlAddButton;
	CListCtrl m_ctrlSearchList;
public:
    afx_msg void OnClose();
};
