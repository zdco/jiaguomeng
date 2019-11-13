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

	//��ʼ��ʱSetCheck��Ч�Ľ���취
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
			{//���ڵ�
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
			{//�ӽڵ�
				HTREEITEM hNode = m_ctrlPhotoTree.InsertItem(CA2T(vField[1].c_str()), 0, 0, hParentNode, TVI_LAST);
				m_ctrlPhotoTree.SetItemData(hNode, nId);
				m_vTree.push_back(hNode);
				if (setId.count(nId) > 0)
				{
					m_ctrlPhotoTree.SetCheck(hNode, TRUE);
					if (!bParentCheck)
					{//���ڵ�δѡ��ʱ��չ��
						m_ctrlPhotoTree.Expand(hParentNode, TVE_EXPAND);
					}
				}
			}
		}
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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
		//Ϊ��һ�»����οؼ���ѡ��״̬�������õ�ǰѡ����ĸ�ѡ��Ϊ�ı���״̬
		m_ctrlPhotoTree.SetCheck(hSelectItem, bCheck);

		//һ�»����οؼ���ѡ��״̬
		ConsistentChildCheck(hSelectItem);
		ConsistentParentCheck(hSelectItem);

		//����ǰѡ����ĸ�ѡ��״̬��ԭ��MFC���Զ���Ӧ��ѡ��״̬�ĸı����
		m_ctrlPhotoTree.SetCheck(hSelectItem, !bCheck);
	}
	*pResult = 0;
}

void CPhotoDlg::ConsistentChildCheck(HTREEITEM hTreeItem)
{
	//��ȡ��ǰѡ�����ѡ��ѡ��״̬
	BOOL bCheck = m_ctrlPhotoTree.GetCheck(hTreeItem);

	//�����ǰ�ڵ�����ӽڵ㣬��һ�»��ӽڵ�״̬
	if (m_ctrlPhotoTree.ItemHasChildren(hTreeItem))
	{
		//����һ�»��ӽڵ���ӽڵ�״̬
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
	//��ȡ��ǰѡ����ĸ��ڵ㣬������ڵ�Ϊ���򷵻أ��������ڵ�״̬
	HTREEITEM hParentItem = m_ctrlPhotoTree.GetParentItem(hTreeItem);
	if (hParentItem != NULL)
	{
		//�����жϵ�ǰѡ����ĸ��ڵ�ĸ����ӽڵ��״̬
		HTREEITEM hChildItem = m_ctrlPhotoTree.GetChildItem(hParentItem);
		while (hChildItem != NULL)
		{
			//������ڵ���һ���ӽڵ�δ��ѡ�У��򸸽ڵ�����Ϊδѡ��״̬��ͬʱ�ݹ鴦���ڵ�ĸ��ڵ�
			if (m_ctrlPhotoTree.GetCheck(hChildItem) == FALSE)
			{
				m_ctrlPhotoTree.SetCheck(hParentItem, FALSE);
				return ConsistentParentCheck(hParentItem);
			}

			//��ȡ���ڵ����һ���ӽڵ�
			hChildItem = m_ctrlPhotoTree.GetNextItem(hChildItem, TVGN_NEXT);
		}

		//������ڵ�������ӽڵ㶼��ѡ�У��򸸽ڵ�����Ϊѡ��״̬��ͬʱ�ݹ鴦���ڵ�ĸ��ڵ�
		m_ctrlPhotoTree.SetCheck(hParentItem, TRUE);
		return ConsistentParentCheck(hParentItem);
	}
}

void CPhotoDlg::OnBnClickedAllSelect()
{
	CString sBtText;
	GetDlgItem(ID_ALL_SELECT)->GetWindowText(sBtText);
	bool bSelectAll = (sBtText == L"ȫѡ");
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
		GetDlgItem(ID_ALL_SELECT)->SetWindowText(L"ȡ��ȫѡ");
	}
	else
	{
		GetDlgItem(ID_ALL_SELECT)->SetWindowText(L"ȫѡ");
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
