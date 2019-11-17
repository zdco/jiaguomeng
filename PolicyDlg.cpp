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

	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN62))->SetRange(0, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN63))->SetRange(0, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN64))->SetRange(0, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN65))->SetRange(0, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN66))->SetRange(0, 5);

	LoadPolicyData();
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
	for (auto it = m_mapPolicyStage.begin(); it != m_mapPolicyStage.end(); it++)
	{
		for (size_t i = 0; i < it->second.size(); i++)
		{
			if (it->second[i] == sPolicyId)
			{
				return it->first - 1;
			}
		}
	}
	return 0;
}

void CPolicyDlg::LoadPolicyData()
{
	//加载政策名称
	vector<vector<string> > vConfig = Config::GetInstance()->ParseConfig(PolicyNameData);
	for (size_t i = 0; i < vConfig.size(); i++)
	{
		const vector<string> &vField = vConfig[i];
		if (vField.size() >= 2)
		{
			m_mapPolicyName[vField[0]] = vField[1];
		}
	}

	//加载政策ID
	map<string, string> mapPolicyId;
	vConfig = Config::GetInstance()->ParseConfig(PolicyBuffData);
	for (size_t i = 0; i < vConfig.size(); i++)
	{
		const vector<string> &vField = vConfig[i];
		if (vField.size() >= 2)
		{
			mapPolicyId[vField[0]] = vField[1];
		}
	}

	//加载政策阶段
	vConfig = Config::GetInstance()->ParseConfig(PolicyStageData);
	for (size_t i = 0; i < vConfig.size(); i++)
	{
		const vector<string> &vField = vConfig[i];
		if (vField.size() >= 2)
		{
			m_mapPolicyStage[atoi(vField[0].c_str())].push_back(mapPolicyId[vField[1]]);
		}
	}

	for (auto it = m_mapPolicyStage.begin(); it != m_mapPolicyStage.end(); it++)
	{
		CString str;
		str.Format(L"第 %d 阶段", it->first);
		((CComboBox*)GetDlgItem(IDC_STAGE))->AddString(str);
	}
	((CComboBox*)GetDlgItem(IDC_STAGE))->SetCurSel(0);
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
	vector<string> vPolicy = m_mapPolicyStage[curSel + 1];
	if (vPolicy.size() > 0)
	{
		((CStatic*)GetDlgItem(IDC_POLICY_TITLE1))->SetWindowText(CA2T(m_mapPolicyName[vPolicy[0]].c_str()));
		ShowWindow(IDC_POLICY_TITLE1, IDC_POLICY1, IDC_SPIN62, TRUE);
	}
	if (vPolicy.size() > 1)
	{
		((CStatic*)GetDlgItem(IDC_POLICY_TITLE2))->SetWindowText(CA2T(m_mapPolicyName[vPolicy[1]].c_str()));
		ShowWindow(IDC_POLICY_TITLE2, IDC_POLICY2, IDC_SPIN63, TRUE);
	}
	if (vPolicy.size() > 2)
	{
		((CStatic*)GetDlgItem(IDC_POLICY_TITLE3))->SetWindowText(CA2T(m_mapPolicyName[vPolicy[2]].c_str()));
		ShowWindow(IDC_POLICY_TITLE3, IDC_POLICY3, IDC_SPIN64, TRUE);
	}
	if (vPolicy.size() > 3)
	{
		((CStatic*)GetDlgItem(IDC_POLICY_TITLE4))->SetWindowText(CA2T(m_mapPolicyName[vPolicy[3]].c_str()));
		ShowWindow(IDC_POLICY_TITLE4, IDC_POLICY4, IDC_SPIN65, TRUE);
	}
	if (vPolicy.size() > 4)
	{
		((CStatic*)GetDlgItem(IDC_POLICY_TITLE5))->SetWindowText(CA2T(m_mapPolicyName[vPolicy[4]].c_str()));
		ShowWindow(IDC_POLICY_TITLE5, IDC_POLICY5, IDC_SPIN66, TRUE);
	}
}

void CPolicyDlg::OnBnClickedOk()
{
	int curSel = ((CComboBox*)GetDlgItem(IDC_STAGE))->GetCurSel();
	vector<string> vPolicy = m_mapPolicyStage[curSel + 1];
	vector<vector<string> > vConfig;
	if (vPolicy.size() > 0)
	{
		vector<string> vField;
		vField.push_back(vPolicy[0]);
		vField.push_back(GetTextField(IDC_POLICY1));
		vConfig.push_back(vField);
	}
	if (vPolicy.size() > 1)
	{
		vector<string> vField;
		vField.push_back(vPolicy[1]);
		vField.push_back(GetTextField(IDC_POLICY2));
		vConfig.push_back(vField);
	}
	if (vPolicy.size() > 2)
	{
		vector<string> vField;
		vField.push_back(vPolicy[2]);
		vField.push_back(GetTextField(IDC_POLICY3));
		vConfig.push_back(vField);
	}
	if (vPolicy.size() > 3)
	{
		vector<string> vField;
		vField.push_back(vPolicy[3]);
		vField.push_back(GetTextField(IDC_POLICY4));
		vConfig.push_back(vField);
	}
	if (vPolicy.size() > 4)
	{
		vector<string> vField;
		vField.push_back(vPolicy[4]);
		vField.push_back(GetTextField(IDC_POLICY5));
		vConfig.push_back(vField);
	}
	Config::GetInstance()->SavePolicyConfig(vConfig);

	CDialogEx::OnOK();
}
