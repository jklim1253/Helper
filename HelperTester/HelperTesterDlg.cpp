
// HelperTesterDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "HelperTester.h"
#include "HelperTesterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHelperTesterDlg 대화 상자




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


// CHelperTesterDlg 메시지 처리기

BOOL CHelperTesterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
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
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CHelperTesterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CHelperTesterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CHelperTesterDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	lpMMI->ptMinTrackSize.x = 400;
	lpMMI->ptMinTrackSize.y = 300;

	CDialog::OnGetMinMaxInfo(lpMMI);
}

void CHelperTesterDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
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
