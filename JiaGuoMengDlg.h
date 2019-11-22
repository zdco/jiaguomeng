
// JiaGuoMengDlg.h : 头文件
//

#pragma once

#include <vector>
#include <string>

#include "Calc.h"

using namespace std;

#define WM_CALC_FINISH (WM_USER + 1)

// CJiaGuoMengDlg 对话框
class CJiaGuoMengDlg : public CDialogEx
{
// 构造
public:
	CJiaGuoMengDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_JIAGUOMENG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnCalcFinish(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedMwCalc();
	afx_msg void OnBnClickedGjgfCalc();
	afx_msg void OnBnClickedPfCalc();
	afx_msg void OnBnClickedXxgyCalc();
	afx_msg void OnBnClickedJmlCalc();
	afx_msg void OnBnClickedRcgyCalc();
	afx_msg void OnBnClickedHyyfCalc();
	afx_msg void OnBnClickedZsxlCalc();
	afx_msg void OnBnClickedKzbsCalc();
	afx_msg void OnBnClickedFxggCalc();
	afx_msg void OnBnClickedBldCalc();
	afx_msg void OnBnClickedXxCalc();
	afx_msg void OnBnClickedFzdCalc();
	afx_msg void OnBnClickedWjdCalc();
	afx_msg void OnBnClickedCscCalc();
	afx_msg void OnBnClickedTscCalc();
	afx_msg void OnBnClickedSmzxCalc();
	afx_msg void OnBnClickedJyzCalc();
	afx_msg void OnBnClickedMszCalc();
	afx_msg void OnBnClickedMtzsCalc();
	afx_msg void OnBnClickedMccCalc();
	afx_msg void OnBnClickedZzcCalc();
	afx_msg void OnBnClickedScCalc();
	afx_msg void OnBnClickedDcCalc();
	afx_msg void OnBnClickedSpcCalc();
	afx_msg void OnBnClickedGtcCalc();
	afx_msg void OnBnClickedFzcCalc();
	afx_msg void OnBnClickedLjcCalc();
	afx_msg void OnBnClickedQejxCalc();
	afx_msg void OnBnClickedRmsyCalc();
	afx_msg void OnBnClickedMxggCalc();
	afx_msg void OnBnClickedZmkdCalc();
	afx_msg void OnBnClickedYygCalc();
	afx_msg void OnBnClickedQgmyCalc();

	afx_msg void OnBnClickedPolicy();
	afx_msg void OnBnClickedPhoto();
	afx_msg void OnBnClickedMission();
	afx_msg void OnBnClickedStart();

	void HandleCalcData(const multimap<double, unordered_map<string, double> > &mapTotalProfit, const int &nCost);

private:
	void EnableTextField(int nStarID, int nLevelID, int nCalcID);
	string GetTextField(int nID);
	void SetTextField(int nID, const string &sField);
	string GetCheckField(int nID);
	void SetCheckField(int nID, const string &sField);
	vector<string> GetBuildingField(const string &sId, int nStartID, int nLevelID, int nCalcID);
	void SetBuildingField(int nStarID, int nLevelID, int nCalcID, const vector<string> &vField);
	void LoadeBuildingConfig();
	void SaveBuildingConfig();
	void LoadJiaguoConfig();
	void SaveJiaguoConfig();

private:
	Calc m_calc;
	string m_sCalcResult;
};
