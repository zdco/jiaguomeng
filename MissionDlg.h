#pragma once


// CMissionDlg dialog

#include <unordered_map>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class CMissionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMissionDlg)

public:
	CMissionDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMissionDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MISSION };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCityStatus();
	afx_msg void OnBnClickedOk();

private:
	void LoadConfig();
	string BuffToString(const vector<pair<string, double> > &vBuff);
	void ResetCityStatus();

private:
	string m_sCurBuffId;
	unordered_map<string, vector<string> > m_mapMissionBuff;
	unordered_map<string, int> m_mapMissionToIndex;
	unordered_map<int, string> m_mapIndexToMission;

};
