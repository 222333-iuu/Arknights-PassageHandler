#pragma once

#ifndef __AFXWIN_H__
#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif
#include "pch.h"
#include "resource.h"		// 主符号
#include "CEXPLORER1.h"
#include "MsHTML.h"
#include <fstream>
using namespace std;

class HANDLEER {
	CString text;
	CStringArray store, fileres;
	CString fileloca = TEXT("./data/check.ini");
	void handlerer();
	CString dealline(CString tar);
	void readfile();
	bool check(CString tar);
	CString dealname(CString tar);
	CString dealdeci(CString tar);
	CString dealpred(CString tar);
	CString dealdoctor(CString tar);
	CString dealSubt(CString tar);
	CString dealStic(CString tar);
	CString dealmult(CString tar);
	CString dealAnim(CString tar);
	CString FindAndCut(CString tar, CString lt, CString rt = TEXT(""));
	void writefile();
public:
	HANDLEER(CString &target);
	CString afterhand;
	int linenum = 0;
};