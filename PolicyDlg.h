#pragma once


// CPolicyDlg dialog

#include <map>
#include <vector>
#include <string>

using namespace std;

class CPolicyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPolicyDlg)

public:
	CPolicyDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPolicyDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POLICY };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeStage();
	afx_msg void OnBnClickedOk();

private:
	string GetTextField(int nID);
	void ShowWindow(int nTitleID, int nPolicyID, int nSpinID, BOOL bShow);
	int GetPolicyStage(const string &sPolicyId);
	void LoadPolicyData();
	void LoadConfig();

private:
	map<string, string> m_mapPolicyName; //政策名称
	map<int, vector<string> > m_mapPolicyStage; //阶段对应政策ID
};
