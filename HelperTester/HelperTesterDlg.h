
// HelperTesterDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CHelperTesterDlg ��ȭ ����
class CHelperTesterDlg : public CDialog
{
// �����Դϴ�.
public:
	CHelperTesterDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_HELPERTESTER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
