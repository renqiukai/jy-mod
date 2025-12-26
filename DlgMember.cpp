// DlgMember.cpp : 实现文件
//

#include "stdafx.h"
#include "JYMod.h"
#include "DlgMember.h"
#include "afxdialogex.h"


// CDlgMember 对话框

IMPLEMENT_DYNAMIC(CDlgMember, CDialogEx)

CDlgMember::CDlgMember(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMember::IDD, pParent)
	, m_strFileName(_T(""))
{
	m_mapMember[0x000] = "主角";
	m_mapMember[0x001] = "胡斐";
	m_mapMember[0x002] = "程灵素";
	m_mapMember[0x003] = "";
	m_mapMember[0x004] = "";
	m_mapMember[0x005] = "张三丰";
	m_mapMember[0x006] = "";
	m_mapMember[0x007] = "";
	m_mapMember[0x008] = "";
	m_mapMember[0x009] = "张无忌";
	m_mapMember[0x00A] = "";
	m_mapMember[0x00B] = "";
	m_mapMember[0x00C] = "";
	m_mapMember[0x00D] = "";
	m_mapMember[0x00E] = "";
	m_mapMember[0x00F] = "";
	m_mapMember[0x010] = "胡青牛";
	m_mapMember[0x011] = "王难姑";
	m_mapMember[0x012] = "成昆";
	m_mapMember[0x013] = "";
	m_mapMember[0x014] = "";
	m_mapMember[0x015] = "";
	m_mapMember[0x016] = "";
	m_mapMember[0x017] = "";
	m_mapMember[0x018] = "";
	m_mapMember[0x019] = "蓝凤凰";
	m_mapMember[0x01A] = "任我行";
	m_mapMember[0x01B] = "东方不败";
	m_mapMember[0x01C] = "平一指";
	m_mapMember[0x01D] = "田伯光";
	m_mapMember[0x01E] = "";
	m_mapMember[0x01F] = "";
	m_mapMember[0x020] = "";
	m_mapMember[0x021] = "";
	m_mapMember[0x022] = "";
	m_mapMember[0x023] = "令狐冲";
	m_mapMember[0x024] = "林平之";
	m_mapMember[0x025] = "狄云";
	m_mapMember[0x026] = "石破天";
	m_mapMember[0x027] = "";
	m_mapMember[0x028] = "";
	m_mapMember[0x029] = "";
	m_mapMember[0x02A] = "";
	m_mapMember[0x02B] = "";
	m_mapMember[0x02C] = "岳老三";
	m_mapMember[0x02D] = "薛慕华";
	m_mapMember[0x02E] = "丁春秋";
	m_mapMember[0x02F] = "阿紫";
	m_mapMember[0x030] = "游坦之";
	m_mapMember[0x031] = "虚竹";
	m_mapMember[0x032] = "乔锋";
	m_mapMember[0x033] = "慕容复";
	m_mapMember[0x034] = "";
	m_mapMember[0x035] = "段誉";
	m_mapMember[0x036] = "袁承志";
	m_mapMember[0x037] = "郭靖";
	m_mapMember[0x038] = "";
	m_mapMember[0x039] = "黄药师";
	m_mapMember[0x03A] = "杨过";
	m_mapMember[0x03B] = "小龙女";
	m_mapMember[0x03C] = "欧阳锋";
	m_mapMember[0x03D] = "欧阳克";
	m_mapMember[0x03E] = "金轮法王";
	m_mapMember[0x03F] = "程瑛";
	m_mapMember[0x040] = "周伯通";
	m_mapMember[0x041] = "一灯";
	m_mapMember[0x042] = "";
	m_mapMember[0x043] = "";
	m_mapMember[0x044] = "";
	m_mapMember[0x045] = "";
	m_mapMember[0x046] = "";
	m_mapMember[0x047] = "";
	m_mapMember[0x048] = "";
	m_mapMember[0x049] = "";
	m_mapMember[0x04A] = "";
	m_mapMember[0x04B] = "";
	m_mapMember[0x04C] = "王语嫣";
}

CDlgMember::~CDlgMember()
{
}

void CDlgMember::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMember, CDialogEx)
END_MESSAGE_MAP()


// CDlgMember 消息处理程序


BOOL CDlgMember::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ReadMember();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


int CDlgMember::ReadMember(void)
{
	if (m_strFileName.IsEmpty())
	{
		return -2;
	}

	CStdioFile f1;
	if(!f1.Open(m_strFileName, CFile::modeRead | CFile::typeBinary)) 
	{
		TRACE(_T("Unable to open file\n"));
		return -1;
	}

	f1.Seek(26, CFile::begin);
	USHORT usMember[5] = {0};
	f1.Read(&usMember[0] + 0, 2);
	f1.Read(&usMember[0] + 1, 2);
	f1.Read(&usMember[0] + 2, 2);
	f1.Read(&usMember[0] + 3, 2);
	f1.Read(&usMember[0] + 4, 2);
	
	SetMember(0,usMember[0]);
	SetMember(1,usMember[1]);
	SetMember(2,usMember[2]);
	SetMember(3,usMember[3]);
	SetMember(4,usMember[4]);

	f1.Close();
	return 0;
}


int CDlgMember::SaveMember(void)
{
	return 0;
}


CString CDlgMember::GetMemberName(USHORT usMember)
{
	return m_mapMember[usMember];
}


int CDlgMember::SetMember(int iPos, USHORT usMember)
{
	CString strMemberName = GetMemberName(usMember);
	GetDlgItem(IDC_COMBO1 + iPos)->SetWindowText(strMemberName);
	GetDlgItem(IDC_MFCMASKEDEDIT1 + iPos)->SetWindowText(strMemberName);
	return 0;
}
