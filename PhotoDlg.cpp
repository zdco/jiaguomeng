// PhotoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "JiaGuoMeng.h"
#include "PhotoDlg.h"
#include "afxdialogex.h"

#include "Config.h"

// CPhotoDlg dialog

IMPLEMENT_DYNAMIC(CPhotoDlg, CDialogEx)

CPhotoDlg::CPhotoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PHOTO, pParent)
{

}

CPhotoDlg::~CPhotoDlg()
{
}

void CPhotoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PHOTO_TREE, m_ctrlPhotoTree);
}


BEGIN_MESSAGE_MAP(CPhotoDlg, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_PHOTO_TREE, &CPhotoDlg::OnNMClickPhotoTree)
	ON_BN_CLICKED(ID_ALL_SELECT, &CPhotoDlg::OnBnClickedAllSelect)
	ON_BN_CLICKED(IDOK, &CPhotoDlg::OnBnClickedOk)
END_MESSAGE_MAP()


BOOL CPhotoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//初始化时SetCheck无效的解决办法
	m_ctrlPhotoTree.ModifyStyle(TVS_CHECKBOXES, 0);
	m_ctrlPhotoTree.ModifyStyle(0, TVS_CHECKBOXES);

	set<int> setId;
	vector<vector<string> > vConfig = Config::GetInstance()->ParseConfig(PhotoConfig);
 	for (size_t i = 0; i < vConfig.size(); i++)
	{
		const vector<string> &vField = vConfig[i];
		if (vField.size() >= 1)
		{
			int nId = atoi(vField[0].c_str());
			setId.insert(nId);
		}
	}

	bool bParentCheck = false;
	HTREEITEM hParentNode = NULL;
	vConfig = Config::GetInstance()->ParseConfig(PhotoNameData);
	for (size_t i = 0; i < vConfig.size(); i++)
	{
		const vector<string> &vField = vConfig[i];
		if (vField.size() >= 2)
		{
			int nId = atoi(vField[0].c_str());
			if (nId % 100 == 0)
			{//根节点
				hParentNode = m_ctrlPhotoTree.InsertItem(CA2T(vField[1].c_str()), 0, 0);
				m_ctrlPhotoTree.SetItemData(hParentNode, nId);
				m_vTree.push_back(hParentNode);
				if (setId.count(nId) > 0)
				{
					m_ctrlPhotoTree.SetCheck(hParentNode, TRUE);
					bParentCheck = true;
				}
				else
				{
					bParentCheck = false;
				}
			}
			else if (hParentNode != NULL)
			{//子节点
				HTREEITEM hNode = m_ctrlPhotoTree.InsertItem(CA2T(vField[1].c_str()), 0, 0, hParentNode, TVI_LAST);
				m_ctrlPhotoTree.SetItemData(hNode, nId);
				m_vTree.push_back(hNode);
				if (setId.count(nId) > 0)
				{
					m_ctrlPhotoTree.SetCheck(hNode, TRUE);
					if (!bParentCheck)
					{//父节点未选中时才展开
						m_ctrlPhotoTree.Expand(hParentNode, TVE_EXPAND);
					}
				}
			}
		}
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// CPhotoDlg message handlers


void CPhotoDlg::OnNMClickPhotoTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	CPoint point;
	UINT nFlag;
	GetCursorPos(&point);
	m_ctrlPhotoTree.ScreenToClient(&point);
	HTREEITEM hSelectItem = m_ctrlPhotoTree.HitTest(point, &nFlag);
	if (hSelectItem == NULL)
	{
		return;
	}

	if (nFlag & TVHT_ONITEMSTATEICON)
	{
		m_ctrlPhotoTree.Expand(hSelectItem, TVE_EXPAND);

		BOOL bCheck = !m_ctrlPhotoTree.GetCheck(hSelectItem);
		//为了一致化树形控件的选中状态，需设置当前选中项的复选框为改变后的状态
		m_ctrlPhotoTree.SetCheck(hSelectItem, bCheck);

		//一致化树形控件复选框状态
		ConsistentChildCheck(hSelectItem);
		ConsistentParentCheck(hSelectItem);

		//将当前选中项的复选框状态复原，MFC会自动响应复选框状态的改变绘制
		m_ctrlPhotoTree.SetCheck(hSelectItem, !bCheck);
	}
	*pResult = 0;
}

void CPhotoDlg::ConsistentChildCheck(HTREEITEM hTreeItem)
{
	//获取当前选中项的选择复选框状态
	BOOL bCheck = m_ctrlPhotoTree.GetCheck(hTreeItem);

	//如果当前节点存在子节点，则一致化子节点状态
	if (m_ctrlPhotoTree.ItemHasChildren(hTreeItem))
	{
		//依次一致化子节点的子节点状态
		HTREEITEM hChildItem = m_ctrlPhotoTree.GetChildItem(hTreeItem);
		while (hChildItem != NULL)
		{
			m_ctrlPhotoTree.SetCheck(hChildItem, bCheck);
			ConsistentChildCheck(hChildItem);

			hChildItem = m_ctrlPhotoTree.GetNextItem(hChildItem, TVGN_NEXT);
		}
	}
}

void CPhotoDlg::ConsistentParentCheck(HTREEITEM hTreeItem)
{
	//获取当前选中项的父节点，如果父节点为空则返回，否则处理父节点状态
	HTREEITEM hParentItem = m_ctrlPhotoTree.GetParentItem(hTreeItem);
	if (hParentItem != NULL)
	{
		//依次判断当前选中项的父节点的各个子节点的状态
		HTREEITEM hChildItem = m_ctrlPhotoTree.GetChildItem(hParentItem);
		while (hChildItem != NULL)
		{
			//如果父节点有一个子节点未被选中，则父节点设置为未选中状态，同时递归处理父节点的父节点
			if (m_ctrlPhotoTree.GetCheck(hChildItem) == FALSE)
			{
				m_ctrlPhotoTree.SetCheck(hParentItem, FALSE);
				return ConsistentParentCheck(hParentItem);
			}

			//获取父节点的下一个子节点
			hChildItem = m_ctrlPhotoTree.GetNextItem(hChildItem, TVGN_NEXT);
		}

		//如果父节点的所有子节点都被选中，则父节点设置为选中状态，同时递归处理父节点的父节点
		m_ctrlPhotoTree.SetCheck(hParentItem, TRUE);
		return ConsistentParentCheck(hParentItem);
	}
}

void CPhotoDlg::OnBnClickedAllSelect()
{
	CString sBtText;
	GetDlgItem(ID_ALL_SELECT)->GetWindowText(sBtText);
	bool bSelectAll = (sBtText == L"全选");
	for (size_t i = 0; i < m_vTree.size(); i++)
	{
		if (bSelectAll)
		{
			m_ctrlPhotoTree.SetCheck(m_vTree[i], TRUE);
		}
		else
		{
			m_ctrlPhotoTree.SetCheck(m_vTree[i], FALSE);
		}
	}

	if (bSelectAll)
	{
		GetDlgItem(ID_ALL_SELECT)->SetWindowText(L"取消全选");
	}
	else
	{
		GetDlgItem(ID_ALL_SELECT)->SetWindowText(L"全选");
	}
}


void CPhotoDlg::OnBnClickedOk()
{
	vector<vector<string> > vConfig;
	for (size_t i = 0; i < m_vTree.size(); i++)
	{
		HTREEITEM hNode = m_vTree[i];
		if (m_ctrlPhotoTree.GetCheck(hNode))
		{
			vector<string> vField;
			int nId = m_ctrlPhotoTree.GetItemData(hNode);
			char buff[10];
			_itoa_s(nId, buff, 10);
			vField.push_back(buff);
			vConfig.push_back(vField);
		}
	}
	Config::GetInstance()->SavePhotoConfig(vConfig);

	CDialogEx::OnOK();
}
