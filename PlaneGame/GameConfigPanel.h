#pragma once
#include "resource.h"

// CGameConfigPanel �Ի���

class CGameConfigPanel : public CDialogEx
{
	DECLARE_DYNAMIC(CGameConfigPanel)

public:
	CGameConfigPanel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameConfigPanel();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
