
// 剧情处理Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "剧情处理.h"
#include "剧情处理Dlg.h"
#include "afxdialogex.h"
#include <afxwin.h>
#include <shlguid.h>
#include <atlbase.h>
#include <atlconv.h>
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#pragma warning(disable : 4996)

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C剧情处理Dlg 对话框



C剧情处理Dlg::C剧情处理Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
	, m_url(_T(""))
	, m_adddescription(_T(""))
	, m_text(_T(""))
	, linenum(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C剧情处理Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_webbrowser);
	DDX_Text(pDX, IDC_EDIT1, m_url);
	DDX_Control(pDX, IDC_RADIO1, m_needend);
	DDX_Text(pDX, IDC_EDIT2, m_adddescription);
	DDX_Control(pDX, IDC_RADIO3, m_isjuqing);
	DDX_Control(pDX, IDC_CHECK1, m_boxnotice);
	DDX_Text(pDX, IDC_EDIT3, m_text);
	DDX_Control(pDX, IDC_EDIT3, m_readfile);
	DDX_Control(pDX, IDC_RADIO6, m_res_file);
	DDX_Control(pDX, IDC_RADIO5, m_res_web);
	DDX_Control(pDX, IDC_TEXT, m_intro);
	DDX_Text(pDX, IDC_LINENUM, linenum);
}

BEGIN_MESSAGE_MAP(C剧情处理Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_DROPFILES()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C剧情处理Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &C剧情处理Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_RADIO1, &C剧情处理Dlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_BUTTON3, &C剧情处理Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_RADIO3, &C剧情处理Dlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_BUTTON4, &C剧情处理Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &C剧情处理Dlg::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT3, &C剧情处理Dlg::OnEnChangeEdit3)
	ON_STN_CLICKED(IDC_LINENUM, &C剧情处理Dlg::OnStnClickedLinenum)
END_MESSAGE_MAP()


// C剧情处理Dlg 消息处理程序

BOOL C剧情处理Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_webbrowser.Navigate(TEXT("https://prts.wiki/w/%E5%89%A7%E6%83%85%E4%B8%80%E8%A7%88"), &noArg, &noArg, &noArg, &noArg);
	m_webbrowser.put_Silent(TRUE);
	SetIEZoomPercent(90);
	OnBnClickedButton5();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C剧情处理Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C剧情处理Dlg::OnPaint()
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
HCURSOR C剧情处理Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C剧情处理Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CString url = m_url, rurl;
	if (m_needend.GetCheck()) {
		int index = url.Find(TEXT(" 行动前"));
		if (index != -1) {
			url = url.Left(index);
			url += TEXT("/BEG");
		}
		else {
			index = url.Find(TEXT(" 行动后"));
			if (index != -1) {
				url = url.Left(index);
				url += TEXT("/END");
			}
			else url += TEXT("/NBT");
		}
		index = url.Find(TEXT(" "));
		url.Replace(TEXT(" "), TEXT("_"));
	}
	rurl = TEXT("https://prts.wiki/index.php?title=");
	rurl += url;
	rurl += TEXT("&action=edit");
	m_webbrowser.Navigate(rurl, &noArg, &noArg, &noArg, &noArg);
}

void C剧情处理Dlg::OnDocumentComplete(LPDISPATCH pDisp, VARIANT* URL)
{
	if (!pDisp)
		return;

	CComQIPtr<IWebBrowser2> spWebBrowser = pDisp;
	if (spWebBrowser)
	{
		CComPtr<IDispatch> spDisp;
		HRESULT hr = spWebBrowser->get_Document(&spDisp);
		if (SUCCEEDED(hr) && spDisp)
		{
			hr = spDisp->QueryInterface(&m_pDocument2);
		}
	}
}

CString C剧情处理Dlg::GetSelectedText()
{
	CString strResult;
	if (m_pDocument2)
	{
		CComPtr<IHTMLSelectionObject> spSelection;
		HRESULT hr = m_pDocument2->get_selection(&spSelection);
		if (SUCCEEDED(hr) && spSelection)
		{
			CComPtr<IDispatch> spRange;
			hr = spSelection->createRange(&spRange);
			if (SUCCEEDED(hr) && spRange)
			{
				CComQIPtr<IHTMLElement> spElement = spRange;
				if (spElement)
				{
					CComPtr<IHTMLElement> spParentElement;
					hr = spElement->get_parentElement(&spParentElement);
					if (SUCCEEDED(hr) && spParentElement)
					{
						CComBSTR bstrText;
						hr = spParentElement->get_innerText(&bstrText);
						if (SUCCEEDED(hr))
						{
							strResult = bstrText;
						}
					}
				}
				else
				{
					CComQIPtr<IHTMLTxtRange> spTxtRange = spRange;
					if (spTxtRange)
					{
						CComBSTR bstrText;
						hr = spTxtRange->get_text(&bstrText);
						if (SUCCEEDED(hr))
						{
							strResult = bstrText;
						}
					}
				}
			}
		}
	}
	return strResult;
}

void C剧情处理Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString result;
	if (m_res_web.GetCheck()) result = GetSelectedText();
	else UpdateData(true), result = m_text;
	HANDLEER hand(result);
	WriteCopyBoard(hand.afterhand);
	CString sendmessage = m_url;
	char len[10];
	sprintf(len, "%d", hand.linenum);
	sendmessage += len;
	sendmessage += TEXT("\n剧情处理完成，已复制到剪贴板");
	if (m_boxnotice.GetCheck()) MessageBox(sendmessage);
	OnBnClickedButton5();
}

BEGIN_EVENTSINK_MAP(C剧情处理Dlg, CDialogEx)
	ON_EVENT(C剧情处理Dlg, IDC_EXPLORER1, 259, C剧情处理Dlg::DocumentCompleteExplorer1, VTS_DISPATCH VTS_PVARIANT)
END_EVENTSINK_MAP()


void C剧情处理Dlg::DocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT* URL)
{
	// TODO: 在此处添加消息处理程序代码
	OnDocumentComplete(pDisp, URL);

}

void C剧情处理Dlg::SetIEZoomPercent(int nZoomPercent)
{
	CRegKey regKey;
	LONG lResult = regKey.Open(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Internet Explorer\\Zoom"));
	if (lResult == ERROR_SUCCESS)
	{
		regKey.SetDWORDValue(_T("ZoomFactor"), nZoomPercent);
	}
}

void C剧情处理Dlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
}

CString C剧情处理Dlg::ReadCopyBoard() {
	CString displayData;
	if (!IsClipboardFormatAvailable(CF_TEXT))return displayData;
	if (!OpenClipboard())return displayData;
	HGLOBAL hglb = GetClipboardData(CF_TEXT);
	if (hglb != NULL)
	{
		char* lptstr = (char*)GlobalLock(hglb);
		if (lptstr != NULL)
		{
			displayData = CString(lptstr);
			GlobalUnlock(hglb);
		}
	}
	CloseClipboard();
	return displayData;

}

void C剧情处理Dlg::WriteCopyBoard(CString strData) {
	int len = strData.GetLength();

	if (len <= 0) return;
	if (!OpenClipboard()) return; // 传入NULL表示使用当前窗口的剪贴板  
	EmptyClipboard();

	// 为Unicode字符串分配内存（注意使用宽字符类型）  
	HGLOBAL hglbCopy = GlobalAlloc(GMEM_MOVEABLE, (len + 1) * sizeof(wchar_t));
	if (hglbCopy == NULL)
	{
		CloseClipboard();
		return;
	}

	// 使用宽字符指针  
	wchar_t* lpwstrCopy = (wchar_t*)GlobalLock(hglbCopy);
	// 直接从CString复制到宽字符指针（无需转换）  
	wcscpy(lpwstrCopy, strData.GetString());
	GlobalUnlock(hglbCopy);

	// 设置剪贴板数据为Unicode文本  
	SetClipboardData(CF_UNICODETEXT, hglbCopy);
	CloseClipboard();
}

void C剧情处理Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_url = ReadCopyBoard();
	UpdateData(false);
	OnBnClickedButton1();
}

void C剧情处理Dlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
}

void C剧情处理Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CString word = TEXT("文本源自明日方舟WIKI （如果有问题请在下方评论区提醒，会尽快改正）\n");
	UpdateData(true);
	word += m_adddescription;
	if (m_isjuqing.GetCheck()) word += TEXT("\n可通过该文集查看更多主线及活动剧情\n");
	else word += TEXT("\n可通过该文集查看更多干员密录\n");
	word += TEXT("==============================\n");
	WriteCopyBoard(word);
}

void C剧情处理Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	m_webbrowser.Navigate(TEXT("https://prts.wiki/w/%E5%89%A7%E6%83%85%E4%B8%80%E8%A7%88"), &noArg, &noArg, &noArg, &noArg);
	m_webbrowser.put_Silent(TRUE);
	m_needend.SetCheck(true);
	m_isjuqing.SetCheck(true);
	m_boxnotice.SetCheck(true);
	DragAcceptFiles(true);
	m_readfile.ShowWindow(false);
	m_res_web.SetCheck(true);
	m_res_file.EnableWindow(false);
	m_res_file.SetCheck(false);
	m_intro.ShowWindow(true);
	m_url = TEXT("");
	m_adddescription = TEXT("");
	linenum = TEXT("字数:0");
	m_text = TEXT("");
	UpdateData(false);
}

void C剧情处理Dlg::OnDropFiles(HDROP hDropInfo)
{
	CDialogEx::OnDropFiles(hDropInfo);

	UINT nFileCount = DragQueryFile(hDropInfo, -1, NULL, 0);

	if (nFileCount > 0)
	{
		CString strFilePath;
		LPTSTR filePath = strFilePath.GetBuffer(MAX_PATH);
		DragQueryFile(hDropInfo, 0, filePath, MAX_PATH);
		strFilePath.ReleaseBuffer();

		CFile file;
		if (file.Open(filePath, CFile::modeRead))
		{
			DWORD dwFileLength = static_cast<DWORD>(file.GetLength());
			std::vector<char> fileContent(dwFileLength + 1);
			file.Read(&fileContent[0], dwFileLength);
			fileContent[dwFileLength] = '\0'; // 确保以null结尾  

			// 假设文件是UTF-8编码的  
			int len = MultiByteToWideChar(CP_UTF8, 0, &fileContent[0], -1, NULL, 0);
			std::vector<wchar_t> wideString(len + 1);
			MultiByteToWideChar(CP_UTF8, 0, &fileContent[0], -1, &wideString[0], len);
			wideString[len] = L'\0'; // 确保以null结尾  

			// 在编辑控件中显示内容  
			m_text = m_text + TEXT("\n\n") + strFilePath + TEXT("\n") + wideString.data();
			linenum.Format(_T("字数:%d"), m_text.GetLength());
			UpdateData(false);
			file.Close();
		}

		m_readfile.ShowWindow(true);
		m_res_file.EnableWindow(true);
		m_res_web.SetCheck(false);
		m_res_file.SetCheck(true);
		m_intro.ShowWindow(true);
	}

	DragFinish(hDropInfo);
}



void C剧情处理Dlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void C剧情处理Dlg::OnStnClickedLinenum()
{
	// TODO: 在此添加控件通知处理程序代码
}
