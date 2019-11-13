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

	m_mapStagePolicy[1].push_back(make_pair("40001", "һ��һ·����"));
	m_mapStagePolicy[1].push_back(make_pair("40002", "����ó��������"));
	m_mapStagePolicy[1].push_back(make_pair("40003", "����Э����չ"));
	m_mapStagePolicy[2].push_back(make_pair("40004", "ȫ����ĸ�"));
	m_mapStagePolicy[2].push_back(make_pair("40005", "ȫ�������ι�"));
	m_mapStagePolicy[2].push_back(make_pair("40006", "�ƽ��˹�"));
	m_mapStagePolicy[2].push_back(make_pair("40007", "��������"));
	m_mapStagePolicy[3].push_back(make_pair("40008", "����ǿ��"));
	m_mapStagePolicy[3].push_back(make_pair("40009", "�Ż�Ӫ�̻���"));
	m_mapStagePolicy[3].push_back(make_pair("40010", "��˰����"));
	m_mapStagePolicy[3].push_back(make_pair("40011", "�ջݽ���"));
	m_mapStagePolicy[4].push_back(make_pair("40012", "���ͳ���"));
	m_mapStagePolicy[4].push_back(make_pair("40013", "�������"));
	m_mapStagePolicy[4].push_back(make_pair("40014", "��׼��ƶ"));
	m_mapStagePolicy[4].push_back(make_pair("40015", "��һ���˹�����"));
	m_mapStagePolicy[5].push_back(make_pair("40016", "���챣��ս"));
	m_mapStagePolicy[5].push_back(make_pair("40017", "��Ӭ���Ժ�"));
	m_mapStagePolicy[5].push_back(make_pair("40018", "ɨ�ڳ���"));
	m_mapStagePolicy[5].push_back(make_pair("40019", "ƽ���й�"));
	m_mapStagePolicy[5].push_back(make_pair("40020", "�����й�"));
	m_mapStagePolicy[6].push_back(make_pair("40021", "������+"));
	m_mapStagePolicy[6].push_back(make_pair("40022", "�����й�"));
	m_mapStagePolicy[6].push_back(make_pair("40023", "�ӳ���"));
	m_mapStagePolicy[6].push_back(make_pair("40024", "��������"));
	m_mapStagePolicy[6].push_back(make_pair("40025", "���������ļ�ֵ��"));
	m_mapStagePolicy[7].push_back(make_pair("40026", "˫һ������"));
	m_mapStagePolicy[7].push_back(make_pair("40027", "����ǿ��"));
	m_mapStagePolicy[7].push_back(make_pair("40028", "�����Ž�"));
	m_mapStagePolicy[7].push_back(make_pair("40029", "��Լ��Դ"));
	m_mapStagePolicy[7].push_back(make_pair("40030", "ǿ���˾�"));
	m_mapStagePolicy[8].push_back(make_pair("40031", "��˰�ĸ�"));
	m_mapStagePolicy[8].push_back(make_pair("40032", "���ڴ�ҵ���ڴ���"));
	m_mapStagePolicy[8].push_back(make_pair("40033", "��Ȩ����"));
	m_mapStagePolicy[8].push_back(make_pair("40034", "�����ƶȸĸ�"));
	m_mapStagePolicy[8].push_back(make_pair("40035", "�Ļ�����"));
	m_mapStagePolicy[9].push_back(make_pair("40036", "�ﻧ������"));
	m_mapStagePolicy[9].push_back(make_pair("40037", "�⹺����"));
	m_mapStagePolicy[9].push_back(make_pair("40038", "��������"));
	m_mapStagePolicy[9].push_back(make_pair("40039", "ҽ����ؽ���"));
	m_mapStagePolicy[9].push_back(make_pair("40040", "�󲡱���"));
	m_mapStagePolicy[10].push_back(make_pair("40041", "ȫ�����"));
	m_mapStagePolicy[10].push_back(make_pair("40042", "��������"));
	m_mapStagePolicy[10].push_back(make_pair("40043", "��������"));
	m_mapStagePolicy[10].push_back(make_pair("40044", "ʧ�����ϳͽ�"));
	m_mapStagePolicy[10].push_back(make_pair("40045", "ȫ����"));

	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN62))->SetRange(0, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN63))->SetRange(0, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN64))->SetRange(0, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN65))->SetRange(0, 5);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN66))->SetRange(0, 5);

	((CComboBox*)GetDlgItem(IDC_STAGE))->SetCurSel(0);

	LoadConfig();
	OnCbnSelchangeStage();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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
