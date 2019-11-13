
// JiaGuoMengDlg.h : ͷ�ļ�
//

#pragma once

#include <vector>
#include <string>

using namespace std;

// CJiaGuoMengDlg �Ի���
class CJiaGuoMengDlg : public CDialogEx
{
// ����
public:
	CJiaGuoMengDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_JIAGUOMENG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
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

	afx_msg void OnBnClickedPolicy();
	afx_msg void OnBnClickedPhoto();
	afx_msg void OnBnClickedMission();
	afx_msg void OnBnClickedStart();

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
};
