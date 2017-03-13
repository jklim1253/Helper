
// HelperTesterDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "HelperTester.h"
#include "HelperTesterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHelperTesterDlg ��ȭ ����




CHelperTesterDlg::CHelperTesterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHelperTesterDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    Logger.AddMessage(_T("MainDialog created."));
}

void CHelperTesterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VALUE, m_ctrlValueEdit);
	DDX_Control(pDX, IDC_ADD, m_ctrlAddButton);
	DDX_Control(pDX, IDC_SEARCHLIST, m_ctrlSearchList);
}

BEGIN_MESSAGE_MAP(CHelperTesterDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
    ON_WM_CLOSE()
END_MESSAGE_MAP()


// CHelperTesterDlg �޽��� ó����

BOOL CHelperTesterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	this->UpdateLayout();

    int width = Config[_T("width")];
    int height = Config[_T("height")];
    int x = (::GetSystemMetrics(SM_CXSCREEN) - width)/2;
    int y = (::GetSystemMetrics(SM_CYSCREEN) - height)/2;
    WINDOWPLACEMENT wp;
    wp.showCmd = Config[_T("showcmd")];
    wp.rcNormalPosition.left = x;
    wp.rcNormalPosition.right = x + width;
    wp.rcNormalPosition.top = y;
    wp.rcNormalPosition.bottom = y + height;
    this->SetWindowPlacement(&wp);

    //this->MoveWindow(x, y, width, height);

    Logger.AddMessage(_T("MainDialog initialized."));
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CHelperTesterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CHelperTesterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CHelperTesterDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	lpMMI->ptMinTrackSize.x = 400;
	lpMMI->ptMinTrackSize.y = 300;

	CDialog::OnGetMinMaxInfo(lpMMI);
}

void CHelperTesterDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	this->UpdateLayout();

    if (this->IsWindowVisible()) {
        Config[_T("width")] = cx;
        Config[_T("height")] = cy;
    }
}

void CHelperTesterDlg::UpdateLayout(void)
{
	if (!::IsWindow(m_ctrlValueEdit.GetSafeHwnd()) ||
		!::IsWindow(m_ctrlAddButton.GetSafeHwnd()) ||
		!::IsWindow(m_ctrlSearchList.GetSafeHwnd())) {
		return;
	}

	int nMargin = 5;
	int nHeight = 25;
	int nButtonWidth = 100;

	CRect rc, rcLocal;
	this->GetClientRect(&rc);

	m_ctrlValueEdit.MoveWindow(nMargin, nMargin, rc.Width() - 3*nMargin - nButtonWidth, nHeight);
	m_ctrlValueEdit.GetWindowRect(&rcLocal);
	this->ScreenToClient(&rcLocal);

	m_ctrlAddButton.MoveWindow(rcLocal.right + nMargin, nMargin, nButtonWidth, nHeight);
	m_ctrlAddButton.GetWindowRect(&rcLocal);
	this->ScreenToClient(&rcLocal);

	m_ctrlSearchList.MoveWindow(nMargin, rcLocal.bottom + nMargin, rc.Width() - 2*nMargin, rc.Height() - 3*nMargin - nHeight);
	m_ctrlSearchList.GetWindowRect(&rcLocal);
	this->ScreenToClient(&rcLocal);

//    Logger.AddMessage(_T("MainDialog Layout Updated."));
}


void CHelperTesterDlg::OnClose()
{
    // TODO: Add your message handler code here and/or call default
    WINDOWPLACEMENT wp;
    this->GetWindowPlacement(&wp);
    CRect rc(wp.rcNormalPosition);
    Config[_T("width")] = rc.Width();
    Config[_T("height")] = rc.Height();
    Config[_T("showcmd")] = wp.showCmd;

    CDialog::OnClose();
}
