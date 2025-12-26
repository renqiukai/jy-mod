// DlgRes.cpp : 实现文件
//

#include "stdafx.h"
#include "JYMod.h"
#include "DlgRes.h"
#include "afxdialogex.h"


// CDlgRes 对话框

IMPLEMENT_DYNAMIC(CDlgRes, CDialogEx)

CDlgRes::CDlgRes(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRes::IDD, pParent)
{

}

CDlgRes::~CDlgRes()
{
}

void CDlgRes::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgRes, CDialogEx)
END_MESSAGE_MAP()


// CDlgRes 消息处理程序
