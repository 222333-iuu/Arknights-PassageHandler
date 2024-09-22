
// 剧情处理Dlg.h: 头文件
//

#pragma once
#include "CEXPLORER1.h"
#include "MsHTML.h"
#include "handler.h"
// C剧情处理Dlg 对话框
class C剧情处理Dlg : public CDialogEx
{
// 构造
public:
	C剧情处理Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEXPLORER1 m_webbrowser;
	CString m_url;
	afx_msg void OnBnClickedButton1();
	COleVariant noArg;
	IHTMLDocument2* m_pDocument2;
	void OnDocumentComplete(LPDISPATCH pDisp, VARIANT* URL); //作为下方获取选中文本的辅助
	CString GetSelectedText();//获取选中文本
	afx_msg void OnBnClickedButton2();
	DECLARE_EVENTSINK_MAP()
	void DocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT* URL);
	void SetIEZoomPercent(int nZoomPercent);
	friend HANDLE;
	afx_msg void OnBnClickedRadio1();
	CButton m_needend;
	CString ReadCopyBoard();
	void WriteCopyBoard(CString strData);
	afx_msg void OnBnClickedButton3();
	CString m_adddescription;
	afx_msg void OnBnClickedRadio3();
	CButton m_isjuqing;
	afx_msg void OnBnClickedButton4();
	CButton m_boxnotice;
	afx_msg void OnBnClickedButton5();
	CString m_text;
	CEdit m_readfile;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CButton m_res_file;
	CButton m_res_web;
	afx_msg void OnEnChangeEdit3();
	CStatic m_intro;
};
