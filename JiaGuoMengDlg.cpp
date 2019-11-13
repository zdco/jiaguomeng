
// JiaGuoMengDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "JiaGuoMeng.h"
#include "JiaGuoMengDlg.h"
#include "afxdialogex.h"
#include "PolicyDlg.h"
#include "PhotoDlg.h"
#include "MissionDlg.h"

#include "Calc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CJiaGuoMengDlg 对话框

CJiaGuoMengDlg::CJiaGuoMengDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_JIAGUOMENG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJiaGuoMengDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CJiaGuoMengDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_POLICY, &CJiaGuoMengDlg::OnBnClickedPolicy)
	ON_BN_CLICKED(IDC_PHOTO, &CJiaGuoMengDlg::OnBnClickedPhoto)
	ON_BN_CLICKED(IDC_MISSION, &CJiaGuoMengDlg::OnBnClickedMission)
	ON_BN_CLICKED(ID_START, &CJiaGuoMengDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_MW_CALC, &CJiaGuoMengDlg::OnBnClickedMwCalc)
	ON_BN_CLICKED(IDC_GJGF_CALC, &CJiaGuoMengDlg::OnBnClickedGjgfCalc)
	ON_BN_CLICKED(IDC_PF_CALC, &CJiaGuoMengDlg::OnBnClickedPfCalc)
	ON_BN_CLICKED(IDC_XXGY_CALC, &CJiaGuoMengDlg::OnBnClickedXxgyCalc)
	ON_BN_CLICKED(IDC_JML_CALC, &CJiaGuoMengDlg::OnBnClickedJmlCalc)
	ON_BN_CLICKED(IDC_RCGY_CALC, &CJiaGuoMengDlg::OnBnClickedRcgyCalc)
	ON_BN_CLICKED(IDC_HYYF_CALC, &CJiaGuoMengDlg::OnBnClickedHyyfCalc)
	ON_BN_CLICKED(IDC_ZSXL_CALC, &CJiaGuoMengDlg::OnBnClickedZsxlCalc)
	ON_BN_CLICKED(IDC_KZBS_CALC, &CJiaGuoMengDlg::OnBnClickedKzbsCalc)
	ON_BN_CLICKED(IDC_FXGG_CALC, &CJiaGuoMengDlg::OnBnClickedFxggCalc)
	ON_BN_CLICKED(IDC_BLD_CALC, &CJiaGuoMengDlg::OnBnClickedBldCalc)
	ON_BN_CLICKED(IDC_XX_CALC, &CJiaGuoMengDlg::OnBnClickedXxCalc)
	ON_BN_CLICKED(IDC_FZD_CALC, &CJiaGuoMengDlg::OnBnClickedFzdCalc)
	ON_BN_CLICKED(IDC_WJD_CALC, &CJiaGuoMengDlg::OnBnClickedWjdCalc)
	ON_BN_CLICKED(IDC_CSC_CALC, &CJiaGuoMengDlg::OnBnClickedCscCalc)
	ON_BN_CLICKED(IDC_TSC_CALC, &CJiaGuoMengDlg::OnBnClickedTscCalc)
	ON_BN_CLICKED(IDC_SMZX_CALC, &CJiaGuoMengDlg::OnBnClickedSmzxCalc)
	ON_BN_CLICKED(IDC_JYZ_CALC, &CJiaGuoMengDlg::OnBnClickedJyzCalc)
	ON_BN_CLICKED(IDC_MSZ_CALC, &CJiaGuoMengDlg::OnBnClickedMszCalc)
	ON_BN_CLICKED(IDC_MTZS_CALC, &CJiaGuoMengDlg::OnBnClickedMtzsCalc)
	ON_BN_CLICKED(IDC_MCC_CALC, &CJiaGuoMengDlg::OnBnClickedMccCalc)
	ON_BN_CLICKED(IDC_ZZC_CALC, &CJiaGuoMengDlg::OnBnClickedZzcCalc)
	ON_BN_CLICKED(IDC_SC_CALC, &CJiaGuoMengDlg::OnBnClickedScCalc)
	ON_BN_CLICKED(IDC_DC_CALC, &CJiaGuoMengDlg::OnBnClickedDcCalc)
	ON_BN_CLICKED(IDC_SPC_CALC, &CJiaGuoMengDlg::OnBnClickedSpcCalc)
	ON_BN_CLICKED(IDC_GTC_CALC, &CJiaGuoMengDlg::OnBnClickedGtcCalc)
	ON_BN_CLICKED(IDC_FZC_CALC, &CJiaGuoMengDlg::OnBnClickedFzcCalc)
	ON_BN_CLICKED(IDC_LJC_CALC, &CJiaGuoMengDlg::OnBnClickedLjcCalc)
	ON_BN_CLICKED(IDC_QEJX_CALC, &CJiaGuoMengDlg::OnBnClickedQejxCalc)
	ON_BN_CLICKED(IDC_RMSY_CALC, &CJiaGuoMengDlg::OnBnClickedRmsyCalc)
END_MESSAGE_MAP()


// CJiaGuoMengDlg 消息处理程序

BOOL CJiaGuoMengDlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN1))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN3))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN5))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN7))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN9))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN11))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN13))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN15))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN17))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN19))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN21))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN23))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN25))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN27))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN29))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN31))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN33))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN35))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN37))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN39))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN41))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN43))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN45))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN47))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN49))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN51))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN53))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN55))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN57))->SetRange(1, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN59))->SetRange(1, 5);

	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN1))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN3))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN5))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN7))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN9))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN11))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN13))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN15))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN17))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN19))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN21))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN23))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN25))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN27))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN29))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN31))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN33))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN35))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN37))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN39))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN41))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN43))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN45))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN47))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN49))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN51))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN53))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN55))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN57))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN59))->SetPos(1);

	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN2))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN4))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN6))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN8))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN10))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN12))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN14))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN16))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN18))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN20))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN22))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN24))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN26))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN28))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN30))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN32))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN34))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN36))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN38))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN40))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN42))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN44))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN46))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN48))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN50))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN52))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN54))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN56))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN58))->SetRange(1, 2000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN60))->SetRange(1, 2000);

	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN2))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN4))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN6))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN8))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN10))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN12))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN14))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN16))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN18))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN20))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN22))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN24))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN26))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN28))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN30))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN32))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN34))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN36))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN38))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN40))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN42))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN44))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN46))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN48))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN50))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN52))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN54))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN56))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN58))->SetPos(1);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN60))->SetPos(1);

	LoadeBuildingConfig();
	LoadJiaguoConfig();

	Config::GetInstance()->Init();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CJiaGuoMengDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CJiaGuoMengDlg::OnPaint()
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
HCURSOR CJiaGuoMengDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CJiaGuoMengDlg::OnBnClickedMwCalc()
{
	EnableTextField(IDC_MW_STAR, IDC_MW_LEVEL, IDC_MW_CALC);
}

void CJiaGuoMengDlg::OnBnClickedGjgfCalc()
{
	EnableTextField(IDC_GJGF_STAR, IDC_GJGF_LEVEL, IDC_GJGF_CALC);
}

void CJiaGuoMengDlg::OnBnClickedPfCalc()
{
	EnableTextField(IDC_PF_STAR, IDC_PF_LEVEL, IDC_PF_CALC);
}

void CJiaGuoMengDlg::OnBnClickedXxgyCalc()
{
	EnableTextField(IDC_XXGY_STAR, IDC_XXGY_LEVEL, IDC_XXGY_CALC);
}

void CJiaGuoMengDlg::OnBnClickedJmlCalc()
{
	EnableTextField(IDC_JML_STAR, IDC_JML_LEVEL, IDC_JML_CALC);
}

void CJiaGuoMengDlg::OnBnClickedRcgyCalc()
{
	EnableTextField(IDC_RCGY_STAR, IDC_RCGY_LEVEL, IDC_RCGY_CALC);
}

void CJiaGuoMengDlg::OnBnClickedHyyfCalc()
{
	EnableTextField(IDC_HYYF_STAR, IDC_HYYF_LEVEL, IDC_HYYF_CALC);
}

void CJiaGuoMengDlg::OnBnClickedZsxlCalc()
{
	EnableTextField(IDC_ZSXL_STAR, IDC_ZSXL_LEVEL, IDC_ZSXL_CALC);
}

void CJiaGuoMengDlg::OnBnClickedKzbsCalc()
{
	EnableTextField(IDC_KZBS_STAR, IDC_KZBS_LEVEL, IDC_KZBS_CALC);
}

void CJiaGuoMengDlg::OnBnClickedFxggCalc()
{
	EnableTextField(IDC_FXGG_STAR, IDC_FXGG_LEVEL, IDC_FXGG_CALC);
}

void CJiaGuoMengDlg::OnBnClickedBldCalc()
{
	EnableTextField(IDC_BLD_STAR, IDC_BLD_LEVEL, IDC_BLD_CALC);
}

void CJiaGuoMengDlg::OnBnClickedXxCalc()
{
	EnableTextField(IDC_XX_STAR, IDC_XX_LEVEL, IDC_XX_CALC);
}

void CJiaGuoMengDlg::OnBnClickedFzdCalc()
{
	EnableTextField(IDC_FZD_STAR, IDC_FZD_LEVEL, IDC_FZD_CALC);
}

void CJiaGuoMengDlg::OnBnClickedWjdCalc()
{
	EnableTextField(IDC_WJD_STAR, IDC_WJD_LEVEL, IDC_WJD_CALC);
}

void CJiaGuoMengDlg::OnBnClickedCscCalc()
{
	EnableTextField(IDC_CSC_STAR, IDC_CSC_LEVEL, IDC_CSC_CALC);
}

void CJiaGuoMengDlg::OnBnClickedTscCalc()
{
	EnableTextField(IDC_TSC_STAR, IDC_TSC_LEVEL, IDC_TSC_CALC);
}

void CJiaGuoMengDlg::OnBnClickedSmzxCalc()
{
	EnableTextField(IDC_SMZX_STAR, IDC_SMZX_LEVEL, IDC_SMZX_CALC);
}

void CJiaGuoMengDlg::OnBnClickedJyzCalc()
{
	EnableTextField(IDC_JYZ_STAR, IDC_JYZ_LEVEL, IDC_JYZ_CALC);
}

void CJiaGuoMengDlg::OnBnClickedMszCalc()
{
	EnableTextField(IDC_MSZ_STAR, IDC_MSZ_LEVEL, IDC_MSZ_CALC);
}

void CJiaGuoMengDlg::OnBnClickedMtzsCalc()
{
	EnableTextField(IDC_MTZS_STAR, IDC_MTZS_LEVEL, IDC_MTZS_CALC);
}

void CJiaGuoMengDlg::OnBnClickedMccCalc()
{
	EnableTextField(IDC_MCC_STAR, IDC_MCC_LEVEL, IDC_MCC_CALC);
}

void CJiaGuoMengDlg::OnBnClickedZzcCalc()
{
	EnableTextField(IDC_ZZC_STAR, IDC_ZZC_LEVEL, IDC_ZZC_CALC);
}

void CJiaGuoMengDlg::OnBnClickedScCalc()
{
	EnableTextField(IDC_SC_STAR, IDC_SC_LEVEL, IDC_SC_CALC);
}

void CJiaGuoMengDlg::OnBnClickedDcCalc()
{
	EnableTextField(IDC_DC_STAR, IDC_DC_LEVEL, IDC_DC_CALC);
}

void CJiaGuoMengDlg::OnBnClickedSpcCalc()
{
	EnableTextField(IDC_SPC_STAR, IDC_SPC_LEVEL, IDC_SPC_CALC);
}

void CJiaGuoMengDlg::OnBnClickedGtcCalc()
{
	EnableTextField(IDC_GTC_STAR, IDC_GTC_LEVEL, IDC_GTC_CALC);
}

void CJiaGuoMengDlg::OnBnClickedFzcCalc()
{
	EnableTextField(IDC_FZC_STAR, IDC_FZC_LEVEL, IDC_FZC_CALC);
}

void CJiaGuoMengDlg::OnBnClickedLjcCalc()
{
	EnableTextField(IDC_LJC_STAR, IDC_LJC_LEVEL, IDC_LJC_CALC);
}

void CJiaGuoMengDlg::OnBnClickedQejxCalc()
{
	EnableTextField(IDC_QEJX_STAR, IDC_QEJX_LEVEL, IDC_QEJX_CALC);
}

void CJiaGuoMengDlg::OnBnClickedRmsyCalc()
{
	EnableTextField(IDC_RMSY_STAR, IDC_RMSY_LEVEL, IDC_RMSY_CALC);
}

void CJiaGuoMengDlg::OnBnClickedPolicy()
{
	CPolicyDlg dlg;
	dlg.DoModal();
}

void CJiaGuoMengDlg::OnBnClickedPhoto()
{
	CPhotoDlg dlg;
	dlg.DoModal();
}

void CJiaGuoMengDlg::OnBnClickedMission()
{
	CMissionDlg dlg;
	dlg.DoModal();
}

void CJiaGuoMengDlg::EnableTextField(int nStarID, int nLevelID, int nCalcID)
{
	bool bShow = (((CButton*)GetDlgItem(nCalcID))->GetCheck() == 1);
	((CEdit*)GetDlgItem(nStarID))->EnableWindow(bShow);
	((CEdit*)GetDlgItem(nLevelID))->EnableWindow(bShow);
}

string CJiaGuoMengDlg::GetTextField(int nID)
{
	CString sField;
	((CEdit*)GetDlgItem(nID))->GetWindowText(sField);
	return CT2A(sField.GetBuffer());
}

void CJiaGuoMengDlg::SetTextField(int nID, const string &sField)
{
	((CEdit*)GetDlgItem(nID))->SetWindowText(CA2T(sField.c_str()));
}

string CJiaGuoMengDlg::GetCheckField(int nID)
{
	if (((CButton*)GetDlgItem(nID))->GetCheck() == 1)
	{
		return "1";
	}
	return "0";
}

void CJiaGuoMengDlg::SetCheckField(int nID, const string &sField)
{
	if (sField == "1")
	{
		((CButton*)GetDlgItem(nID))->SetCheck(1);
	}
}

vector<string> CJiaGuoMengDlg::GetBuildingField(const string &sId, int nStartID, int nLevelID, int nCalcID)
{
	vector<string> vBuildingField;
	vBuildingField.push_back(sId);
	vBuildingField.push_back(GetTextField(nStartID));
	vBuildingField.push_back(GetTextField(nLevelID));
	vBuildingField.push_back(GetCheckField(nCalcID));
	return vBuildingField;
}

void CJiaGuoMengDlg::SetBuildingField(int nStarID, int nLevelID, int nCalcID, const vector<string> &vField)
{
	SetTextField(nStarID, vField[1]);
	SetTextField(nLevelID, vField[2]);
	SetCheckField(nCalcID, vField[3]);
	EnableTextField(nStarID, nLevelID, nCalcID);
}

void CJiaGuoMengDlg::LoadeBuildingConfig()
{
	vector<vector<string> > vConfig = Config::GetInstance()->ParseConfig(BuildingConfig);
	for (size_t i = 0; i < vConfig.size(); i++)
	{
		const vector<string> &vField = vConfig[i];
		if (vField.size() >= 4)
		{
			if (vField[0] == "1000") SetBuildingField(IDC_MW_STAR, IDC_MW_LEVEL, IDC_MW_CALC, vField);
			else if (vField[0] == "1010") SetBuildingField(IDC_GJGF_STAR, IDC_GJGF_LEVEL, IDC_GJGF_CALC, vField);
			else if (vField[0] == "1020") SetBuildingField(IDC_PF_STAR, IDC_PF_LEVEL, IDC_PF_CALC, vField);
			else if (vField[0] == "1030") SetBuildingField(IDC_XXGY_STAR, IDC_XXGY_LEVEL, IDC_XXGY_CALC, vField);
			else if (vField[0] == "1040") SetBuildingField(IDC_JML_STAR, IDC_JML_LEVEL, IDC_JML_CALC, vField);
			else if (vField[0] == "1050") SetBuildingField(IDC_RCGY_STAR, IDC_RCGY_LEVEL, IDC_RCGY_CALC, vField);
			else if (vField[0] == "1060") SetBuildingField(IDC_HYYF_STAR, IDC_HYYF_LEVEL, IDC_HYYF_CALC, vField);
			else if (vField[0] == "1070") SetBuildingField(IDC_ZSXL_STAR, IDC_ZSXL_LEVEL, IDC_ZSXL_CALC, vField);
			else if (vField[0] == "1080") SetBuildingField(IDC_KZBS_STAR, IDC_KZBS_LEVEL, IDC_KZBS_CALC, vField);
			else if (vField[0] == "1090") SetBuildingField(IDC_FXGG_STAR, IDC_FXGG_LEVEL, IDC_FXGG_CALC, vField);
			else if (vField[0] == "3000") SetBuildingField(IDC_BLD_STAR, IDC_BLD_LEVEL, IDC_BLD_CALC, vField);
			else if (vField[0] == "3010") SetBuildingField(IDC_XX_STAR, IDC_XX_LEVEL, IDC_XX_CALC, vField);
			else if (vField[0] == "3020") SetBuildingField(IDC_FZD_STAR, IDC_FZD_LEVEL, IDC_FZD_CALC, vField);
			else if (vField[0] == "3030") SetBuildingField(IDC_WJD_STAR, IDC_WJD_LEVEL, IDC_WJD_CALC, vField);
			else if (vField[0] == "3040") SetBuildingField(IDC_CSC_STAR, IDC_CSC_LEVEL, IDC_CSC_CALC, vField);
			else if (vField[0] == "3050") SetBuildingField(IDC_TSC_STAR, IDC_TSC_LEVEL, IDC_TSC_CALC, vField);
			else if (vField[0] == "3060") SetBuildingField(IDC_SMZX_STAR, IDC_SMZX_LEVEL, IDC_SMZX_CALC, vField);
			else if (vField[0] == "3070") SetBuildingField(IDC_JYZ_STAR, IDC_JYZ_LEVEL, IDC_JYZ_CALC, vField);
			else if (vField[0] == "3080") SetBuildingField(IDC_MSZ_STAR, IDC_MSZ_LEVEL, IDC_MSZ_CALC, vField);
			else if (vField[0] == "3090") SetBuildingField(IDC_MTZS_STAR, IDC_MTZS_LEVEL, IDC_MTZS_CALC, vField);
			else if (vField[0] == "5000") SetBuildingField(IDC_MCC_STAR, IDC_MCC_LEVEL, IDC_MCC_CALC, vField);
			else if (vField[0] == "5010") SetBuildingField(IDC_ZZC_STAR, IDC_ZZC_LEVEL, IDC_ZZC_CALC, vField);
			else if (vField[0] == "5020") SetBuildingField(IDC_SC_STAR, IDC_SC_LEVEL, IDC_SC_CALC, vField);
			else if (vField[0] == "5030") SetBuildingField(IDC_DC_STAR, IDC_DC_LEVEL, IDC_DC_CALC, vField);
			else if (vField[0] == "5040") SetBuildingField(IDC_SPC_STAR, IDC_SPC_LEVEL, IDC_SPC_CALC, vField);
			else if (vField[0] == "5050") SetBuildingField(IDC_GTC_STAR, IDC_GTC_LEVEL, IDC_GTC_CALC, vField);
			else if (vField[0] == "5060") SetBuildingField(IDC_FZC_STAR, IDC_FZC_LEVEL, IDC_FZC_CALC, vField);
			else if (vField[0] == "5070") SetBuildingField(IDC_LJC_STAR, IDC_LJC_LEVEL, IDC_LJC_CALC, vField);
			else if (vField[0] == "5080") SetBuildingField(IDC_QEJX_STAR, IDC_QEJX_LEVEL, IDC_QEJX_CALC, vField);
			else if (vField[0] == "5090") SetBuildingField(IDC_RMSY_STAR, IDC_RMSY_LEVEL, IDC_RMSY_CALC, vField);
		}
	}
}

void CJiaGuoMengDlg::SaveBuildingConfig()
{
	vector<vector<string> > vBuildingConfig;
	vBuildingConfig.push_back(GetBuildingField("1000", IDC_MW_STAR, IDC_MW_LEVEL, IDC_MW_CALC));
	vBuildingConfig.push_back(GetBuildingField("1010", IDC_GJGF_STAR, IDC_GJGF_LEVEL, IDC_GJGF_CALC));
	vBuildingConfig.push_back(GetBuildingField("1020", IDC_PF_STAR, IDC_PF_LEVEL, IDC_PF_CALC));
	vBuildingConfig.push_back(GetBuildingField("1030", IDC_XXGY_STAR, IDC_XXGY_LEVEL, IDC_XXGY_CALC));
	vBuildingConfig.push_back(GetBuildingField("1040", IDC_JML_STAR, IDC_JML_LEVEL, IDC_JML_CALC));
	vBuildingConfig.push_back(GetBuildingField("1050", IDC_RCGY_STAR, IDC_RCGY_LEVEL, IDC_RCGY_CALC));
	vBuildingConfig.push_back(GetBuildingField("1060", IDC_HYYF_STAR, IDC_HYYF_LEVEL, IDC_HYYF_CALC));
	vBuildingConfig.push_back(GetBuildingField("1070", IDC_ZSXL_STAR, IDC_ZSXL_LEVEL, IDC_ZSXL_CALC));
	vBuildingConfig.push_back(GetBuildingField("1080", IDC_KZBS_STAR, IDC_KZBS_LEVEL, IDC_KZBS_CALC));
	vBuildingConfig.push_back(GetBuildingField("1090", IDC_FXGG_STAR, IDC_FXGG_LEVEL, IDC_FXGG_CALC));
	vBuildingConfig.push_back(GetBuildingField("3000", IDC_BLD_STAR, IDC_BLD_LEVEL, IDC_BLD_CALC));
	vBuildingConfig.push_back(GetBuildingField("3010", IDC_XX_STAR, IDC_XX_LEVEL, IDC_XX_CALC));
	vBuildingConfig.push_back(GetBuildingField("3020", IDC_FZD_STAR, IDC_FZD_LEVEL, IDC_FZD_CALC));
	vBuildingConfig.push_back(GetBuildingField("3030", IDC_WJD_STAR, IDC_WJD_LEVEL, IDC_WJD_CALC));
	vBuildingConfig.push_back(GetBuildingField("3040", IDC_CSC_STAR, IDC_CSC_LEVEL, IDC_CSC_CALC));
	vBuildingConfig.push_back(GetBuildingField("3050", IDC_TSC_STAR, IDC_TSC_LEVEL, IDC_TSC_CALC));
	vBuildingConfig.push_back(GetBuildingField("3060", IDC_SMZX_STAR, IDC_SMZX_LEVEL, IDC_SMZX_CALC));
	vBuildingConfig.push_back(GetBuildingField("3070", IDC_JYZ_STAR, IDC_JYZ_LEVEL, IDC_JYZ_CALC));
	vBuildingConfig.push_back(GetBuildingField("3080", IDC_MSZ_STAR, IDC_MSZ_LEVEL, IDC_MSZ_CALC));
	vBuildingConfig.push_back(GetBuildingField("3090", IDC_MTZS_STAR, IDC_MTZS_LEVEL, IDC_MTZS_CALC));
	vBuildingConfig.push_back(GetBuildingField("5000", IDC_MCC_STAR, IDC_MCC_LEVEL, IDC_MCC_CALC));
	vBuildingConfig.push_back(GetBuildingField("5010", IDC_ZZC_STAR, IDC_ZZC_LEVEL, IDC_ZZC_CALC));
	vBuildingConfig.push_back(GetBuildingField("5020", IDC_SC_STAR, IDC_SC_LEVEL, IDC_SC_CALC));
	vBuildingConfig.push_back(GetBuildingField("5030", IDC_DC_STAR, IDC_DC_LEVEL, IDC_DC_CALC));
	vBuildingConfig.push_back(GetBuildingField("5040", IDC_SPC_STAR, IDC_SPC_LEVEL, IDC_SPC_CALC));
	vBuildingConfig.push_back(GetBuildingField("5050", IDC_GTC_STAR, IDC_GTC_LEVEL, IDC_GTC_CALC));
	vBuildingConfig.push_back(GetBuildingField("5060", IDC_FZC_STAR, IDC_FZC_LEVEL, IDC_FZC_CALC));
	vBuildingConfig.push_back(GetBuildingField("5070", IDC_LJC_STAR, IDC_LJC_LEVEL, IDC_LJC_CALC));
	vBuildingConfig.push_back(GetBuildingField("5080", IDC_QEJX_STAR, IDC_QEJX_LEVEL, IDC_QEJX_CALC));
	vBuildingConfig.push_back(GetBuildingField("5090", IDC_RMSY_STAR, IDC_RMSY_LEVEL, IDC_RMSY_CALC));

	Config::GetInstance()->SaveBuildingConfig(vBuildingConfig);
}

void CJiaGuoMengDlg::LoadJiaguoConfig()
{
	vector<vector<string> > vConfig = Config::GetInstance()->ParseConfig(JiaguoConfig);
	for (size_t i = 0; i < vConfig.size(); i++)
	{
		const vector<string> &vField = vConfig[i];
		if (vField.size() >= 1)
		{
			SetTextField(IDC_JGZG, vField[0]);
		}
	}
}

void CJiaGuoMengDlg::SaveJiaguoConfig()
{
	vector<vector<string> > vJiaguoConfig;
	vector<string> vJiaguoField;
	vJiaguoField.push_back(GetTextField(IDC_JGZG));
	vJiaguoConfig.push_back(vJiaguoField);
	Config::GetInstance()->SaveJiaguoConfig(vJiaguoConfig);
}

void CJiaGuoMengDlg::OnBnClickedStart()
{
	SaveBuildingConfig();
	SaveJiaguoConfig();

	Calc calc;
	multimap<double, unordered_map<string, double> > mapTotalProfit = calc.Start();
	auto it = mapTotalProfit.rbegin();
	if (it != mapTotalProfit.rend())
	{
		ostringstream os;
		os << "总收入：" << it->first << "\r\n";
		for (auto data_it = it->second.begin(); data_it != it->second.end(); data_it++)
		{
			Building* building = Config::GetInstance()->GetBuilding(data_it->first);
			if (building)
			{
				double baseProfit = building->GetBaseProfit();
				os << data_it->first << "（" << building->GetName() << "）：" << data_it->second << "（" << baseProfit << "+" << data_it->second - baseProfit << "）\r\n";
			}
		}
		SetTextField(IDC_RESULT, os.str());
	}
}