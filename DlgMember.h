#pragma once
#include "afxtempl.h"


// CDlgMember 对话框

class CDlgMember : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMember)

public:
	CDlgMember(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMember();

// 对话框数据
	enum { IDD = IDD_DLG_MEMBER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_strFileName;
	int ReadMember(void);
	int SaveMember(void);
	CString GetMemberName(USHORT usMember);
	int SetMember(int iPos, USHORT usMember);
	CMap<int, int, CString, CString> m_mapMember;
};
