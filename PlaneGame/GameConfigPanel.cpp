// GameConfigPanel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PlaneGame.h"
#include "GameConfigPanel.h"
#include "afxdialogex.h"


// CGameConfigPanel �Ի���

IMPLEMENT_DYNAMIC(CGameConfigPanel, CDialogEx)

CGameConfigPanel::CGameConfigPanel(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CGameConfigPanel::~CGameConfigPanel()
{
}

void CGameConfigPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameConfigPanel, CDialogEx)
END_MESSAGE_MAP()


// CGameConfigPanel ��Ϣ�������


BOOL CGameConfigPanel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
