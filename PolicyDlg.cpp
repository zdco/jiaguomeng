// PolicyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "JiaGuoMeng.h"
#include "PolicyDlg.h"
#include "afxdialogex.h"

#include "Config.h"


// CPolicyDlg dialog

IMPLEMENT_DYNAMIC(CPolicyDlg, CDialogEx)

CPolicyDlg::CPolicyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_POLICY, pParent)
{

}

CPolicyDlg::~CPolicyDlg()
{
}

void CPolicyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPolicyDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_STAGE, &CPolicyDlg::OnCbnSelchangeStage)
	ON_BN_CLICKED(IDOK, &CPolicyDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CPolicyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_mapStagePolicy[1].push_back(make_pair("40001", "一带一路建设"));
	m_mapStagePolicy[1].push_back(make_pair("40002", "自由贸易区建设"));
	m_mapStagePolicy[1].push_back(make_pair("40003", "区域协调发展"));
	m_mapStagePolicy[2].push_back(make_pair("40004", "全面深化改革"));
	m_mapStagePolicy[2].push_back(make_pair("40005", "全面依法治国"));
	m_mapStagePolicy[2].push_back(make_pair("40006", "科教兴国"));
	m_mapStagePolicy[2].push_back(make_pair("40007", "创新驱动"));
	m_mapStagePolicy[3].push_back(make_pair("40008", "制造强国"));
	m_mapStagePolicy[3].push_back(make_pair("40009", "优化营商环境"));
	m_mapStagePolicy[3].push_back(make_pair("40010", "减税降费"));
	m_mapStagePolicy[3].push_back(make_pair("40011", "普惠金融"));
	m_mapStagePolicy[4].push_back(make_pair("40012", "新型城镇化"));
	m_mapStagePolicy[4].push_back(make_pair("40013", "乡村振兴"));
	m_mapStagePolicy[4].push_back(make_pair("40014", "精准扶贫"));
	m_mapStagePolicy[4].push_back(make_pair("40015", "新一代人工智能"));
	m_mapStagePolicy[5].push_back(make_pair("40016", "蓝天保卫战"));
	m_mapStagePolicy[5].push_back(make_pair("40017", "拍蝇打虎猎狐"));
	m_mapStagePolicy[5].push_back(make_pair("40018", "扫黑除恶"));
	m_mapStagePolicy[5].push_back(make_pair("40019", "平安中国"));
	m_mapStagePolicy[5].push_back(make_pair("40020", "美丽中国"));
	m_mapStagePolicy[6].push_back(make_pair("40021", "互联网+"));
	m_mapStagePolicy[6].push_back(make_pair("40022", "健康中国"));
	m_mapStagePolicy[6].push_back(make_pair("40023", "河长制"));
	m_mapStagePolicy[6].push_back(make_pair("40024", "厕所革命"));
	m_mapStagePolicy[6].push_back(make_pair("40025", "社会主义核心价值观"));
	m_mapStagePolicy[7].push_back(make_pair("40026", "双一流建设"));
	m_mapStagePolicy[7].push_back(make_pair("40027", "体育强国"));
	m_mapStagePolicy[7].push_back(make_pair("40028", "民族团结"));
	m_mapStagePolicy[7].push_back(make_pair("40029", "节约资源"));
	m_mapStagePolicy[7].push_back(make_pair("40030", "强军兴军"));
	m_mapStagePolicy[8].push_back(make_pair("40031", "个税改革"));
	m_mapStagePolicy[8].push_back(make_pair("40032", "大众创业万众创新"));
	m_mapStagePolicy[8].push_back(make_pair("40033", "产权保护"));
	m_mapStagePolicy[8].push_back(make_pair("40034", "户籍制度改革"));
	m_mapStagePolicy[8].push_back(make_pair("40035", "文化惠民"));
	m_mapStagePolicy[9].push_back(make_pair("40036", "棚户区改造"));
	m_mapStagePolicy[9].push_back(make_pair("40037", "租购并举"));
	m_mapStagePolicy[9].push_back(make_pair("40038", "垃圾分类"));
	m_mapStagePolicy[9].push_back(make_pair("40039", "医保异地结算"));
	m_mapStagePolicy[9].push_back(make_pair("40040", "大病保险"));
	m_mapStagePolicy[10].push_back(make_pair("40041", "全面二孩"));
	m_mapStagePolicy[10].push_back(make_pair("40042", "幼有所育"));
	m_mapStagePolicy[10].push_back(make_pair("40043", "老有所养"));
	m_mapStagePolicy[10].push_back(make_pair("40044", "失信联合惩戒"));
	m_mapStagePolicy[10].push_back(make_pair("40045", "全民健身"));

	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN62))->SetRange(0, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN63))->SetRange(0, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN64))->SetRange(0, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN65))->SetRange(0, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN66))->SetRange(0, 5);

	((CComboBox*)GetDlgItem(IDC_STAGE))->SetCurSel(0);

	LoadConfig();
	OnCbnSelchangeStage();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// CPolicyDlg message handlers

string CPolicyDlg::GetTextField(int nID)
{
	CString sField;
	((CEdit*)GetDlgItem(nID))->GetWindowText(sField);
	return CT2A(sField.GetBuffer());
}

void CPolicyDlg::ShowWindow(int nTitleID, int nPolicyID, int nSpinID, BOOL bShow)
{
	((CStatic*)GetDlgItem(nTitleID))->ShowWindow(bShow);
	((CEdit*)GetDlgItem(nPolicyID))->ShowWindow(bShow);
	((CSpinButtonCtrl*)GetDlgItem(nSpinID))->ShowWindow(bShow);
}

int CPolicyDlg::GetPolicyStage(const string &sPolicyId)
{
	for (auto it = m_mapStagePolicy.begin(); it != m_mapStagePolicy.end(); it++)
	{
		for (size_t i = 0; i < it->second.size(); i++)
		{
			const pair<string, string> &policyInfo = it->second[i];
			if (policyInfo.first == sPolicyId)
			{
				return it->first - 1;
			}
		}
	}
	return 0;
}

void CPolicyDlg::LoadConfig()
{
	vector<vector<string> > vConfig = Config::GetInstance()->ParseConfig(PolicyConfig);
	if (vConfig.size() > 0)
	{
		const vector<string> &vField = vConfig[0];
		if (vField.size() >= 2)
		{
			((CComboBox*)GetDlgItem(IDC_STAGE))->SetCurSel(GetPolicyStage(vField[0]));
			((CEdit*)GetDlgItem(IDC_POLICY1))->SetWindowText(CA2T(vField[1].c_str()));
		}
	}
	if (vConfig.size() > 1)
	{
		const vector<string> &vField = vConfig[1];
		if (vField.size() >= 2)
		{
			((CEdit*)GetDlgItem(IDC_POLICY2))->SetWindowText(CA2T(vField[1].c_str()));
		}
	}
	if (vConfig.size() > 2)
	{
		const vector<string> &vField = vConfig[2];
		if (vField.size() >= 2)
		{
			((CEdit*)GetDlgItem(IDC_POLICY3))->SetWindowText(CA2T(vField[1].c_str()));
		}
	}
	if (vConfig.size() > 3)
	{
		const vector<string> &vField = vConfig[3];
		if (vField.size() >= 2)
		{
			((CEdit*)GetDlgItem(IDC_POLICY4))->SetWindowText(CA2T(vField[1].c_str()));
		}
	}
	if (vConfig.size() > 4)
	{
		const vector<string> &vField = vConfig[4];
		if (vField.size() >= 2)
		{
			((CEdit*)GetDlgItem(IDC_POLICY5))->SetWindowText(CA2T(vField[1].c_str()));
		}
	}
}

void CPolicyDlg::OnCbnSelchangeStage()
{
	ShowWindow(IDC_POLICY_TITLE4, IDC_POLICY4, IDC_SPIN65, FALSE);
	ShowWindow(IDC_POLICY_TITLE5, IDC_POLICY5, IDC_SPIN66, FALSE);

	int curSel = ((CComboBox*)GetDlgItem(IDC_STAGE))->GetCurSel();
	vector<pair<string, string> > vPolicy = m_mapStagePolicy[curSel + 1];
	if (vPolicy.size() > 0)
	{
		((CStatic*)GetDlgItem(IDC_POLICY_TITLE1))->SetWindowText(CA2T(vPolicy[0].second.c_str()));
		ShowWindow(IDC_POLICY_TITLE1, IDC_POLICY1, IDC_SPIN62, TRUE);
	}
	if (vPolicy.size() > 1)
	{
		((CStatic*)GetDlgItem(IDC_POLICY_TITLE2))->SetWindowText(CA2T(vPolicy[1].second.c_str()));
		ShowWindow(IDC_POLICY_TITLE2, IDC_POLICY2, IDC_SPIN63, TRUE);
	}
	if (vPolicy.size() > 2)
	{
		((CStatic*)GetDlgItem(IDC_POLICY_TITLE3))->SetWindowText(CA2T(vPolicy[2].second.c_str()));
		ShowWindow(IDC_POLICY_TITLE3, IDC_POLICY3, IDC_SPIN64, TRUE);
	}
	if (vPolicy.size() > 3)
	{
		((CStatic*)GetDlgItem(IDC_POLICY_TITLE4))->SetWindowText(CA2T(vPolicy[3].second.c_str()));
		ShowWindow(IDC_POLICY_TITLE4, IDC_POLICY4, IDC_SPIN65, TRUE);
	}
	if (vPolicy.size() > 4)
	{
		((CStatic*)GetDlgItem(IDC_POLICY_TITLE5))->SetWindowText(CA2T(vPolicy[4].second.c_str()));
		ShowWindow(IDC_POLICY_TITLE5, IDC_POLICY5, IDC_SPIN66, TRUE);
	}
}

void CPolicyDlg::OnBnClickedOk()
{
	int curSel = ((CComboBox*)GetDlgItem(IDC_STAGE))->GetCurSel();
	vector<pair<string, string> > vPolicy = m_mapStagePolicy[curSel + 1];
	vector<vector<string> > vConfig;
	if (vPolicy.size() > 0)
	{
		vector<string> vField;
		vField.push_back(vPolicy[0].first);
		vField.push_back(GetTextField(IDC_POLICY1));
		vConfig.push_back(vField);
	}
	if (vPolicy.size() > 1)
	{
		vector<string> vField;
		vField.push_back(vPolicy[1].first);
		vField.push_back(GetTextField(IDC_POLICY2));
		vConfig.push_back(vField);
	}
	if (vPolicy.size() > 2)
	{
		vector<string> vField;
		vField.push_back(vPolicy[2].first);
		vField.push_back(GetTextField(IDC_POLICY3));
		vConfig.push_back(vField);
	}
	if (vPolicy.size() > 3)
	{
		vector<string> vField;
		vField.push_back(vPolicy[3].first);
		vField.push_back(GetTextField(IDC_POLICY4));
		vConfig.push_back(vField);
	}
	if (vPolicy.size() > 4)
	{
		vector<string> vField;
		vField.push_back(vPolicy[4].first);
		vField.push_back(GetTextField(IDC_POLICY5));
		vConfig.push_back(vField);
	}
	Config::GetInstance()->SavePolicyConfig(vConfig);

	CDialogEx::OnOK();
}
