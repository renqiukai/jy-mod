
// JYModDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "JYMod.h"
#include "JYModDlg.h"
#include "afxdialogex.h"

#include <sstream>

#include "DlgMember.h"
//#include "uxtheme.h"
#include "SaveGRPFile.h"

//#pragma comment(lib, "uxtheme.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CJYModDlg 对话框




CJYModDlg::CJYModDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJYModDlg::IDD, pParent)
	, m_iManX(0)
	, m_iManY(0)
	, m_strSaveFile(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// 恢复编辑框内容
	CString editValue = AfxGetApp()->GetProfileString(_T("Settings"), _T("LastSaveFile"), _T("D:\\dos\\LEGEND\\R1.GRP"));
	m_strSaveFile = editValue;
}

void CJYModDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PLACE, m_cmPlace);
	DDX_Text(pDX, IDC_EDIT_MAN_X, m_iManX);
	DDV_MinMaxInt(pDX, m_iManX, 0, 999);
	DDX_Text(pDX, IDC_EDIT_MAN_Y, m_iManY);
	DDV_MinMaxInt(pDX, m_iManY, 0, 999);
	DDX_Control(pDX, IDC_EDIT_FILEPATH, m_editFilePath);
	DDX_Text(pDX, IDC_EDIT_FILEPATH, m_strSaveFile);
}

BEGIN_MESSAGE_MAP(CJYModDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SETFOCUS()
	ON_CBN_SELCHANGE(IDC_COMBO_PLACE, &CJYModDlg::OnCbnSelchangeComboPlace)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_POS, &CJYModDlg::OnBnClickedButtonSavePos)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON1, IDC_BUTTON111, &CJYModDlg::OnBnClickedButtonPlace)  
	ON_BN_CLICKED(IDC_BTN_OPENFILE, &CJYModDlg::OnBnClickedBtnOpenfile)
	ON_BN_CLICKED(IDC_BTN_RELOADPOS, &CJYModDlg::OnBnClickedBtnReloadpos)
	ON_BN_CLICKED(IDC_BTN_MEMBER, &CJYModDlg::OnBnClickedBtnMember)
END_MESSAGE_MAP()


// CJYModDlg 消息处理程序

BOOL CJYModDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_editFilePath.SetWindowText(m_strSaveFile);

	InitPlaceCB();

	ReloadPosition(m_strSaveFile);

	// Enable Visual Styles for this window (requires linking with uxtheme. lib)
	//SetWindowTheme(m_hWnd, L"Explorer", NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CJYModDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CJYModDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CJYModDlg::OnSetFocus(CWnd* pOldWnd)
{
	CDialogEx::OnSetFocus(pOldWnd);

	// TODO: 在此处添加消息处理程序代码

	UpdateData(true);
	ReloadPosition(m_strSaveFile);
}

#define ADDPOS(a,b,c) \
	item = m_cmPlace.AddString(a "," #b "," #c);\
	m_cmPlace.SetItemData(item, MAKELONG(b,c));



int CJYModDlg::InitPlaceCB(void)
{
	std::string content = ReadTextResource();
	AddRes2ComboBox(content, &m_cmPlace);
#if 0
	int item = 0;
	ADDPOS("河洛客栈",359,229);
	ADDPOS("龙门客栈",101,374);
	ADDPOS("有间客栈",78,141);
	ADDPOS("高升客栈",199,401);
	ADDPOS("悦来客栈",221,286);
	ADDPOS("冰火岛",103,16);
	ADDPOS("桃花岛",339,138);
	ADDPOS("渤泥岛",277,43);
	ADDPOS("灵蛇岛",187,63);
	ADDPOS("侠客岛",455,328);
	ADDPOS("万鳄岛",432,125);
	ADDPOS("冰蚕洞",22,449);
	ADDPOS("无量山洞",169,426);
	ADDPOS("神雕山洞",68,170);
	ADDPOS("昆仑仙境",22,440);
	ADDPOS("绝情谷底",132,254);
	ADDPOS("闯王宝藏",64,51);
	ADDPOS("沙漠废墟",53,219);
	ADDPOS("金蛇洞",193,293);
	ADDPOS("思过崖",187,301);
	ADDPOS("摩天崖",186,338);
	ADDPOS("藏宝洞",172,425);
	ADDPOS("狄云山洞",364,279);
	ADDPOS("沙漠山洞",75,226);
	ADDPOS("鸳鸯山洞",425,38);
	ADDPOS("大理宝藏",72,283);
	ADDPOS("破庙",19,181);
	ADDPOS("北丑居",49,111);
	ADDPOS("胡斐居",86,94);
	ADDPOS("程瑛居",295,422);
	ADDPOS("一灯居",314,370);
	ADDPOS("平一指居",215,196);
	ADDPOS("薛慕华居",192,261);
	ADDPOS("云鹤崖",17,15);
	ADDPOS("百花谷",159,270);
	ADDPOS("黑龙潭",309,352);
	ADDPOS("海边小屋",286,157);
	ADDPOS("主角居",357,235);
	ADDPOS("南贤居",388,325);
	ADDPOS("成昆居",19,249);
	ADDPOS("阎基居",396,374);
	ADDPOS("苗人凤居",223,187);
	ADDPOS("田伯光居",385,306);
	ADDPOS("洪七公居",169,210);
	ADDPOS("燕子坞",308,197);
	ADDPOS("梅庄",330,196);
	ADDPOS("白驼山",141,433);
	ADDPOS("福威镖局",369,258);
	ADDPOS("药王庄",323,317);
	ADDPOS("蝴蝶谷",238,219);
	ADDPOS("绝情谷",134,259);
	ADDPOS("擂鼓山",176,221);
	ADDPOS("金轮寺",103,397);
	ADDPOS("衡山派",355,376);
	ADDPOS("泰山派",193,139);
	ADDPOS("嵩山派",242,293);
	ADDPOS("崆峒派",160,314);
	ADDPOS("武当派",226,340);
	ADDPOS("青城派",185,370);
	ADDPOS("重阳宫",145,217);
	ADDPOS("五毒教",247,424);
	ADDPOS("铁掌山",302,343);
	ADDPOS("黑木崖",118,178);
	ADDPOS("凌霄城",166,404);
	ADDPOS("明教分舵",76,363);
	ADDPOS("天宁寺",329,237);
	ADDPOS("大轮寺",114,297);
	ADDPOS("恒山派",112,215);
	ADDPOS("华山派",193,301);
	ADDPOS("少林寺",247,300);
	ADDPOS("峨嵋派",215,408);
	ADDPOS("昆仑派",42,419);
	ADDPOS("古墓",144,218);
	ADDPOS("神龙教",141,113);
	ADDPOS("光明顶",68,397);
	ADDPOS("星宿海",132,410);
	ADDPOS("丐帮",229,256);
	ADDPOS("回族部落",120,343);
	ADDPOS("霹雳堂",409,217);
	ADDPOS("武道大会",192,295);
#endif

#if 0
	m_cmPlace.AddString(_T("河洛客栈,359,229"));
	m_cmPlace.AddString(_T("龙门客栈,101,374"));
	m_cmPlace.AddString(_T("有间客栈,78,141"));
	m_cmPlace.AddString(_T("高升客栈,199,401"));
	m_cmPlace.AddString(_T("悦来客栈,221,286"));
	m_cmPlace.AddString(_T("冰火岛,103,16"));
	m_cmPlace.AddString(_T("桃花岛,339,138"));
	m_cmPlace.AddString(_T("渤泥岛,277,43"));
	m_cmPlace.AddString(_T("灵蛇岛,187,63"));
	m_cmPlace.AddString(_T("侠客岛,455,328"));
	m_cmPlace.AddString(_T("万鳄岛,432,125"));
	m_cmPlace.AddString(_T("冰蚕洞,22,449"));
	m_cmPlace.AddString(_T("无量山洞,169,426"));
	m_cmPlace.AddString(_T("神雕山洞,68,170"));
	m_cmPlace.AddString(_T("昆仑仙境,22,440"));
	m_cmPlace.AddString(_T("绝情谷底,132,254"));
	m_cmPlace.AddString(_T("闯王宝藏,64,51"));
	m_cmPlace.AddString(_T("沙漠废墟,53,219"));
	m_cmPlace.AddString(_T("金蛇洞,193,293"));
	m_cmPlace.AddString(_T("思过崖,187,301"));
	m_cmPlace.AddString(_T("摩天崖,186,338"));
	m_cmPlace.AddString(_T("藏宝洞,172,425"));
	m_cmPlace.AddString(_T("狄云山洞,364,279"));
	m_cmPlace.AddString(_T("沙漠山洞,75,226"));
	m_cmPlace.AddString(_T("鸳鸯山洞,425,38"));
	m_cmPlace.AddString(_T("大理宝藏,72,283"));
	m_cmPlace.AddString(_T("破庙,19,181"));
	m_cmPlace.AddString(_T("北丑居,49,111"));
	m_cmPlace.AddString(_T("胡斐居,86,94"));
	m_cmPlace.AddString(_T("程瑛居,295,422"));
	m_cmPlace.AddString(_T("一灯居,314,370"));
	m_cmPlace.AddString(_T("平一指居,215,196"));
	m_cmPlace.AddString(_T("薛慕华居,192,261"));
	m_cmPlace.AddString(_T("云鹤崖,17,15"));
	m_cmPlace.AddString(_T("百花谷,159,270"));
	m_cmPlace.AddString(_T("黑龙潭,309,352"));
	m_cmPlace.AddString(_T("海边小屋,286,157"));
	m_cmPlace.AddString(_T("主角居,357,235"));
	m_cmPlace.AddString(_T("南贤居,388,325"));
	m_cmPlace.AddString(_T("成昆居,19,249"));
	m_cmPlace.AddString(_T("阎基居,396,374"));
	m_cmPlace.AddString(_T("苗人凤居,223,187"));
	m_cmPlace.AddString(_T("田伯光居,385,306"));
	m_cmPlace.AddString(_T("洪七公居,169,210"));
	m_cmPlace.AddString(_T("燕子坞,308,197"));
	m_cmPlace.AddString(_T("梅庄,330,196"));
	m_cmPlace.AddString(_T("白驼山,141,433"));
	m_cmPlace.AddString(_T("福威镖局,369,258"));
	m_cmPlace.AddString(_T("药王庄,323,317"));
	m_cmPlace.AddString(_T("蝴蝶谷,238,219"));
	m_cmPlace.AddString(_T("绝情谷,134,259"));
	m_cmPlace.AddString(_T("擂鼓山,176,221"));
	m_cmPlace.AddString(_T("金轮寺,103,397"));
	m_cmPlace.AddString(_T("衡山派,355,376"));
	m_cmPlace.AddString(_T("泰山派,193,139"));
	m_cmPlace.AddString(_T("嵩山派,242,293"));
	m_cmPlace.AddString(_T("崆峒派,160,314"));
	m_cmPlace.AddString(_T("武当派,226,340"));
	m_cmPlace.AddString(_T("青城派,185,370"));
	m_cmPlace.AddString(_T("重阳宫,145,217"));
	m_cmPlace.AddString(_T("五毒教,247,424"));
	m_cmPlace.AddString(_T("铁掌山,302,343"));
	m_cmPlace.AddString(_T("黑木崖,118,178"));
	m_cmPlace.AddString(_T("凌霄城,166,404"));
	m_cmPlace.AddString(_T("明教分舵,76,363"));
	m_cmPlace.AddString(_T("天宁寺,329,237"));
	m_cmPlace.AddString(_T("大轮寺,114,297"));
	m_cmPlace.AddString(_T("恒山派,112,215"));
	m_cmPlace.AddString(_T("华山派,193,301"));
	m_cmPlace.AddString(_T("少林寺,247,300"));
	m_cmPlace.AddString(_T("峨嵋派,215,408"));
	m_cmPlace.AddString(_T("昆仑派,42,419"));
	m_cmPlace.AddString(_T("古墓,144,218"));
	m_cmPlace.AddString(_T("神龙教,141,113"));
	m_cmPlace.AddString(_T("光明顶,68,397"));
	m_cmPlace.AddString(_T("星宿海,132,410"));
	m_cmPlace.AddString(_T("丐帮,229,256"));
	m_cmPlace.AddString(_T("回族部落,120,343"));
	m_cmPlace.AddString(_T("霹雳堂,409,217"));
	m_cmPlace.AddString(_T("武道大会,192,295"));
#endif
	return 0;
}

int CJYModDlg::SavePosition(CString strFile)
{
	UpdateData(true);
	CFile file;
	BOOL bOpen = file.Open(strFile, CFile::modeWrite|CFile::shareDenyNone|CFile::typeBinary);
	if (bOpen)
	{
		ULONGLONG l = file.GetLength();
		file.Seek(4,CFile::begin);
		USHORT usX = m_iManX, usY = m_iManY;
		file.Write(&usX, 2);
		file.Write(&usY, 2);
		file.Close();

		m_iManX = usX;
		m_iManY = usY;
		UpdateData(false);

		// 保存编辑框内容
		AfxGetApp()->WriteProfileString(_T("Settings"), _T("LastSaveFile"), strFile);
	}


	return 0;
}

int CJYModDlg::ReloadPosition(CString strFile)
{
	CFile file;
	BOOL bOpen = file.Open(strFile, CFile::modeRead|CFile::shareDenyNone|CFile::typeBinary);
	if (bOpen)
	{
		ULONGLONG l = file.GetLength();
		file.Seek(4,CFile::begin);
		USHORT usX,usY;
		file.Read(&usX, 2);
		file.Read(&usY, 2);
		file.Close();
		m_iManX = usX;
		m_iManY = usY;

		// 保存编辑框内容
		AfxGetApp()->WriteProfileString(_T("Settings"), _T("LastSaveFile"), strFile);
	}

	UpdateData(false);

	CString strPosName;
	for (int i = m_cmPlace.GetCount() - 1; i >= 0; i--)
	{
		DWORD dwData = m_cmPlace.GetItemData(i);
		int y = HIWORD(dwData);
		int x = LOWORD(dwData);
		int deltaX = (m_iManX-x);
		int deltaY = (m_iManY-y);
		if ((deltaX<=1)&&(deltaX>=-1)&&(deltaY<=1)&&(deltaY>=-1))
		{
			m_cmPlace.GetLBText(i, strPosName);
			break;
		}
	}
	GetDlgItem(IDC_STATIC_POS)->SetWindowText(strPosName);

	return 0;
}


void CJYModDlg::OnCbnSelchangeComboPlace()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strPlace;
	m_cmPlace.GetWindowText(strPlace);
	USHORT usX,usY;
	int iPos = strPlace.Find(_T(','));
	if (_stscanf_s(PCTSTR(strPlace) + iPos + 1, _T("%hu,%hu"), &usX, &usY) == 2)
	{
		m_iManX = usX;
		m_iManY = usY;
		UpdateData(false);
	}

	SavePosition(m_strSaveFile);
}


void CJYModDlg::OnBnClickedButtonSavePos()
{
	// TODO: 在此添加控件通知处理程序代码
	SavePosition(m_strSaveFile);
}


void CJYModDlg::OnBnClickedButtonPlace(UINT nID)
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd* pWnd = GetDlgItem(nID);
	if (pWnd != NULL)
	{
		CString strText;
		pWnd->GetWindowText(strText);
		if (!strText.IsEmpty())
		{
			CString strLBText;
			strText += ',';
			int len = strText.GetLength();
			for (int i = m_cmPlace.GetCount() - 1; i>=0 ; i--)
			{
				m_cmPlace.GetLBText(i, strLBText);
				if (strLBText.Left(len) == strText)
				{
					m_cmPlace.SetCurSel(i);
					OnCbnSelchangeComboPlace();
					break;
				}
			}
		}
	}
}


void CJYModDlg::OnBnClickedBtnOpenfile()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlgFile(TRUE,
		_T("*.grp"),
		_T("r1.grp"),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Save File(*.grp)|*.grp|All Files (*.*)|*.*||"));
	CString fileName;

	if (dlgFile.DoModal() == IDOK)
	{
		fileName = dlgFile.GetPathName();
		m_strSaveFile = fileName;
		m_editFilePath.SetWindowText(fileName);

		ReloadPosition(fileName);

		ReadPersonFromSaveFile(fileName);
		CString csv=dlgFile.GetFolderPath();
		csv += "\\人物属性.csv";
		ExportToCSV(csv);
	}
}


void CJYModDlg::OnBnClickedBtnReloadpos()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	ReloadPosition(m_strSaveFile);
}


void CJYModDlg::OnBnClickedBtnMember()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_strSaveFile.IsEmpty())
	{
		OnBnClickedBtnOpenfile();
	}


	CDlgMember dlg;
	dlg.m_strFileName = m_strSaveFile;
	dlg.DoModal();
}

// 用于去除字符串首尾空格和制表符
std::string Trim(const std::string& str)
{
	if (str.empty())
	{
		return "";
	}
	size_t first = str.find_first_not_of(" \t");
	if (first == std::string::npos)
	{
		return "";
	}
	size_t last = str.find_last_not_of(" \t");
	return str.substr(first, last - first + 1);
}

std::string CJYModDlg::ReadTextResource(void)
{
	HMODULE hModule = GetModuleHandle(NULL); // 获取当前模块句柄
	HRSRC hRes = FindResource(hModule, MAKEINTRESOURCE(IDR_TEXT_POS), "TEXT");
	if (!hRes)
	{
		return ""; // 资源未找到
	}

	HGLOBAL hGlobal = LoadResource(hModule, hRes);
	if (!hGlobal)
	{
		return ""; // 加载失败
	}

	DWORD size = SizeofResource(hModule, hRes);
	LPVOID pData = LockResource(hGlobal);
	if (!pData)
	{
		return ""; // 锁定失败
	}

	// 将资源数据复制到字符串中
	std::string content(static_cast<char*>(pData), size);
	return content;
}


int CJYModDlg::AddRes2ComboBox(std::string content, CComboBox* pBox)
{
	std::istringstream linesStream(content);
	std::string line;

	while (std::getline(linesStream, line))
	{
		std::string trimmedLine = Trim(line);
		if (trimmedLine.empty())
		{
			continue;
		}

		// 从后往前提取两个整数
		size_t lastSep = trimmedLine.find_last_of(" \t");
		if (lastSep == std::string::npos || lastSep == 0 || lastSep == trimmedLine.length() - 1)
		{
			continue;
		}

		std::string cStr = Trim(trimmedLine.substr(lastSep + 1));
		std::string remaining = Trim(trimmedLine.substr(0, lastSep));

		size_t prevSep = remaining.find_last_of(" \t");
		if (prevSep == std::string::npos || prevSep == 0 || prevSep == remaining.length() - 1)
		{
			continue;
		}

		std::string bStr = Trim(remaining.substr(prevSep + 1));
		std::string a = Trim(remaining.substr(0, prevSep));

		// 将字符串转换为整数
		int b = 0, c = 0;
		char bBuf[32] = {0}, cBuf[32] = {0};
		strcpy_s(bBuf, bStr.c_str());
		strcpy_s(cBuf, cStr.c_str());

		if (sscanf_s(bBuf, "%d", &b) != 1 || sscanf_s(cBuf, "%d", &c) != 1)
		{
			continue;
		}

		// 构造显示字符串

		CString displayText;
		CString strA(a.c_str());  // 自动适配 Unicode / ANSI
		displayText.Format(_T("%s,%d,%d"), (LPCTSTR)strA, b, c);

		// 添加到组合框
		int item = pBox->AddString(displayText);
		if (item != CB_ERR)
		{
			pBox->SetItemData(item, MAKELONG(b, c));
		}
	}
	return 0;
}
