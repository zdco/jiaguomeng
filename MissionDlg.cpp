// MissionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "JiaGuoMeng.h"
#include "MissionDlg.h"
#include "afxdialogex.h"

#include "Config.h"
#include "Building.h"


// CMissionDlg dialog

IMPLEMENT_DYNAMIC(CMissionDlg, CDialogEx)

CMissionDlg::CMissionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MISSION, pParent)
{

}

CMissionDlg::~CMissionDlg()
{
}

void CMissionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMissionDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_CITY_STATUS, &CMissionDlg::OnCbnSelchangeCityStatus)
	ON_BN_CLICKED(IDOK, &CMissionDlg::OnBnClickedOk)
END_MESSAGE_MAP()


BOOL CMissionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	LoadConfig();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// CMissionDlg message handlers

void CMissionDlg::LoadConfig()
{
	unordered_map<string, string> mapMissionName = Config::GetInstance()->GetMissionName();
	for (auto it = mapMissionName.begin(); it != mapMissionName.end(); it++)
	{
		((CComboBox*)GetDlgItem(IDC_CITY_STATUS))->AddString(CA2T(it->second.c_str()));
	}

	((CComboBox*)GetDlgItem(IDC_CITY_STATUS))->SetCurSel(0);

	int index = 0;
	m_mapMissionBuff = Config::GetInstance()->GetMissionBuff();
	for (auto it = m_mapMissionBuff.begin(); it != m_mapMissionBuff.end(); it++)
	{
		m_mapMissionToIndex[it->first] = index;
		m_mapIndexToMission[index] = it->first;
		++index;
	}

	vector<vector<string> > vConfig = Config::GetInstance()->ParseConfig(MissionConfig);
	if (!vConfig.empty())
	{
		const vector<string> &vField = vConfig[0];
		if (vField.size() >= 2)
		{
			string sMissionId = vField[0];
			m_sCurBuffId = vField[1];
			((CComboBox*)GetDlgItem(IDC_CITY_STATUS))->SetCurSel(m_mapMissionToIndex[sMissionId]);
		}
	}

	OnCbnSelchangeCityStatus();
}

string CMissionDlg::BuffToString(const vector<pair<string, double> > &vBuff)
{
	ostringstream os;
	for (size_t i = 0; i < vBuff.size(); i++)
	{
		const pair<string, double> &buff = vBuff[i];
		if (buff.first == CategorySupply)
		{
			os << "供货";
		}
		else if (buff.first == CategoryAll)
		{
			os << "所有建筑";
		}
		else if (buff.first == CategoryOnline)
		{
			os << "在线时所有建筑";
		}
		else if (buff.first == CategoryOffline)
		{
			os << "离线时所有建筑";
		}
		else if (buff.first == CategoryResidence)
		{
			os << "住宅建筑";
		}
		else if (buff.first == CategoryBusiness)
		{
			os << "商业建筑";
		}
		else if (buff.first == CategoryIndustrial)
		{
			os << "工业建筑";
		}
		else
		{
			Building* building = Config::GetInstance()->GetBuilding(buff.first);
			if (building)
			{
				os << building->GetName();
			}
		}
		os << "收入增加" << (int)(buff.second * 100) << "%；";
	}
	return os.str();
}

void CMissionDlg::ResetCityStatus()
{
	((CButton*)GetDlgItem(IDC_CITY_STATUS1))->ShowWindow(FALSE);
	((CButton*)GetDlgItem(IDC_CITY_STATUS1))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_CITY_STATUS2))->ShowWindow(FALSE);
	((CButton*)GetDlgItem(IDC_CITY_STATUS2))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_CITY_STATUS3))->ShowWindow(FALSE);
	((CButton*)GetDlgItem(IDC_CITY_STATUS3))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_CITY_STATUS4))->ShowWindow(FALSE);
	((CButton*)GetDlgItem(IDC_CITY_STATUS4))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_CITY_STATUS5))->ShowWindow(FALSE);
	((CButton*)GetDlgItem(IDC_CITY_STATUS5))->SetCheck(FALSE);
}

void CMissionDlg::OnCbnSelchangeCityStatus()
{
	ResetCityStatus();

	unordered_map<string, vector<pair<string, double> > > mapBuffStatus = Config::GetInstance()->GetBuffStatus();
	int curSel = ((CComboBox*)GetDlgItem(IDC_CITY_STATUS))->GetCurSel();
	string sMissionId = m_mapIndexToMission[curSel];
	vector<string> vMissionBuff = m_mapMissionBuff[sMissionId];
	if (vMissionBuff.size() > 0)
	{
		auto it = mapBuffStatus.find(vMissionBuff[0]);
		if (it != mapBuffStatus.end())
		{
			((CStatic*)GetDlgItem(IDC_CITY_STATUS1))->SetWindowText(CA2T(BuffToString(it->second).c_str()));
			((CButton*)GetDlgItem(IDC_CITY_STATUS1))->ShowWindow(TRUE);
			((CButton*)GetDlgItem(IDC_CITY_STATUS1))->SetCheck(TRUE);
		}
	}

	if (vMissionBuff.size() > 1)
	{
		auto it = mapBuffStatus.find(vMissionBuff[1]);
		if (it != mapBuffStatus.end())
		{
			((CStatic*)GetDlgItem(IDC_CITY_STATUS2))->SetWindowText(CA2T(BuffToString(it->second).c_str()));
			((CButton*)GetDlgItem(IDC_CITY_STATUS2))->ShowWindow(TRUE);
			if (m_sCurBuffId == it->first)
			{
				((CButton*)GetDlgItem(IDC_CITY_STATUS1))->SetCheck(FALSE);
				((CButton*)GetDlgItem(IDC_CITY_STATUS2))->SetCheck(TRUE);
			}
		}
	}
	if (vMissionBuff.size() > 2)
	{
		auto it = mapBuffStatus.find(vMissionBuff[2]);
		if (it != mapBuffStatus.end())
		{
			((CStatic*)GetDlgItem(IDC_CITY_STATUS3))->SetWindowText(CA2T(BuffToString(it->second).c_str()));
			((CButton*)GetDlgItem(IDC_CITY_STATUS3))->ShowWindow(TRUE);
			if (m_sCurBuffId == it->first)
			{
				((CButton*)GetDlgItem(IDC_CITY_STATUS1))->SetCheck(FALSE);
				((CButton*)GetDlgItem(IDC_CITY_STATUS3))->SetCheck(TRUE);
			}
		}
	}
	if (vMissionBuff.size() > 3)
	{
		auto it = mapBuffStatus.find(vMissionBuff[3]);
		if (it != mapBuffStatus.end())
		{
			((CStatic*)GetDlgItem(IDC_CITY_STATUS4))->SetWindowText(CA2T(BuffToString(it->second).c_str()));
			((CButton*)GetDlgItem(IDC_CITY_STATUS4))->ShowWindow(TRUE);
			if (m_sCurBuffId == it->first)
			{
				((CButton*)GetDlgItem(IDC_CITY_STATUS1))->SetCheck(FALSE);
				((CButton*)GetDlgItem(IDC_CITY_STATUS4))->SetCheck(TRUE);
			}
		}
	}
	if (vMissionBuff.size() > 4)
	{
		auto it = mapBuffStatus.find(vMissionBuff[4]);
		if (it != mapBuffStatus.end())
		{
			((CStatic*)GetDlgItem(IDC_CITY_STATUS5))->SetWindowText(CA2T(BuffToString(it->second).c_str()));
			((CButton*)GetDlgItem(IDC_CITY_STATUS5))->ShowWindow(TRUE);
			if (m_sCurBuffId == it->first)
			{
				((CButton*)GetDlgItem(IDC_CITY_STATUS1))->SetCheck(FALSE);
				((CButton*)GetDlgItem(IDC_CITY_STATUS5))->SetCheck(TRUE);
			}
		}
	}
}

void CMissionDlg::OnBnClickedOk()
{
	int curSel = ((CComboBox*)GetDlgItem(IDC_CITY_STATUS))->GetCurSel();
	string sMissionId = m_mapIndexToMission[curSel];
	vector<vector<string> > vConfig;
	vector<string> vField;
	vField.push_back(sMissionId);
	if (((CButton*)GetDlgItem(IDC_CITY_STATUS1))->GetCheck())
	{
		vField.push_back(m_mapMissionBuff[sMissionId][0]);
	}
	else if (((CButton*)GetDlgItem(IDC_CITY_STATUS2))->GetCheck())
	{
		vField.push_back(m_mapMissionBuff[sMissionId][1]);
	}
	else if (((CButton*)GetDlgItem(IDC_CITY_STATUS3))->GetCheck())
	{
		vField.push_back(m_mapMissionBuff[sMissionId][2]);
	}
	else if (((CButton*)GetDlgItem(IDC_CITY_STATUS4))->GetCheck())
	{
		vField.push_back(m_mapMissionBuff[sMissionId][3]);
	}
	else if (((CButton*)GetDlgItem(IDC_CITY_STATUS5))->GetCheck())
	{
		vField.push_back(m_mapMissionBuff[sMissionId][4]);
	}
	vConfig.push_back(vField);
	Config::GetInstance()->SaveMissionConfig(vConfig);
	CDialogEx::OnOK();
}
