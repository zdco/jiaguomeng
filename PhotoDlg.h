#pragma once
#include "afxcmn.h"

#include <vector>

using namespace std;

// CPhotoDlg dialog

class CPhotoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPhotoDlg)

public:
	CPhotoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPhotoDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHOTO };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_ctrlPhotoTree;
	afx_msg void OnNMClickPhotoTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedAllSelect();
	afx_msg void OnBnClickedOk();

private:
	void ConsistentChildCheck(HTREEITEM hTreeItem);
	void ConsistentParentCheck(HTREEITEM hTreeItem);

private:
	vector<HTREEITEM> m_vTree;
};
