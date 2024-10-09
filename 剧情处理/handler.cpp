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
#include <cstring>

HANDLEER::HANDLEER(CString &target){
	text = target;
	afterhand = TEXT("");
	readfile();
	handlerer();
	writefile();
}

void HANDLEER::handlerer() {
	int index = 0, emptyline = 0;
	CString takeout;
	while (index < text.GetLength()) {
		takeout = text.Tokenize(TEXT("\n"), index);
		store.Add(takeout);
	}
	for (int i = 0; i < store.GetSize(); i++) {
		CString aft = dealline(store.GetAt(i));
		if (aft.Find(TEXT("<i>")) != -1)
			aft = FindAndCut(aft, TEXT("<i>"), TEXT("</i>"));
		if (aft == TEXT("")) emptyline++;
		else {
			if (emptyline > 7) afterhand += "//\n";
			emptyline = 0;
			afterhand += aft;
			afterhand += "\n";
			linenum++;
		}
		if (emptyline == 1) afterhand += "\n";
	}
}

CString HANDLEER::dealline(CString tar) {
	CString note = tar.Left(5), ans = TEXT("");
	if (check(note)) return ans;
	tar = dealdoctor(tar);
	if (note == TEXT("[name") || note == TEXT("[Name")) return dealname(tar);
	else if (note == TEXT("[Deci") || note == TEXT("[deci")) return dealdeci(tar);
	else if (note == TEXT("[Pred") || note == TEXT("[pred")) return dealpred(tar);
	else if (note == TEXT("[Subt") || note == TEXT("[subt")) return dealSubt(tar);
	else if (note == TEXT("[Stic") || note == TEXT("[stic")) return dealStic(tar);
	else if (note == TEXT("[Mult") || note == TEXT("[mult")) return dealmult(tar);
	else if (note == TEXT("[anim") || note == TEXT("[Anim")) return dealAnim(tar);
	else if (tar.Find(TEXT("[")) != -1){
		INT_PTR nRes;
		nRes = MessageBox(NULL, tar, _T("出现未知的前缀，按“是”加入删除列表，“否”删除但不加入，“取消”不删除"), MB_YESNOCANCEL | MB_ICONINFORMATION);
		if (nRes == IDYES) {
			fileres.Add(note);
			return ans;
		}
		else if (nRes == IDNO) return ans;
	}
	return tar;
}

bool HANDLEER::check(CString tar) {
	for (int i = 0; i < fileres.GetSize(); i++) {
		if (tar == fileres.GetAt(i)) return true;
	}
	return false;
}

void HANDLEER::readfile() {
	ifstream ifs;
	ifs.open(fileloca, ios::in);
	string temp;
	while (ifs >> temp) {
		CString temp2(temp.c_str());
		fileres.Add(temp2);
	}
	ifs.close();
}

void HANDLEER::writefile() {
	ofstream ofs;
	ofs.open(fileloca, ios::out);
	string temp;
	for (int i = 0; i < fileres.GetSize(); i++) {
		string temp = (CT2A)fileres[i];
		ofs << temp << "\n";
	}
	ofs.close();
}

CString HANDLEER::dealname(CString tar) {
	CString ans = TEXT("");
	ans += FindAndCut(tar, _T("e="), _T("]"));
	ans += TEXT(" ");
	ans += FindAndCut(tar, _T("]"));
	return ans;
}

CString HANDLEER::dealdeci(CString tar) {
	CString ans = TEXT("");
	ans += TEXT("可选项： ");
	ans += FindAndCut(tar,TEXT("options="),TEXT(", v"));
	ans += TEXT(" 对应选项：");
	ans += FindAndCut(tar, TEXT("values="), TEXT(")]"));
	return ans;
}

CString HANDLEER::FindAndCut(CString tar, CString lt, CString rt) {
	int lp, rp;
	CString ans = TEXT("");
	lp = tar.Find(lt);
	if (rt.GetLength()) {
		rp = tar.Find(rt, lp + 1);
		ans = tar.Mid(lp + lt.GetLength() + 1, rp - lp - lt.GetLength() - 2);
	}
	else ans = tar.Mid(lp + lt.GetLength());
	return ans;
}

CString HANDLEER::dealpred(CString tar) {
	CString ans = TEXT("");
	ans += TEXT("选项");
	ans += FindAndCut(tar, TEXT("references="), TEXT(")]"));
	ans += TEXT("选后对应的内容");
	return ans;
}

CString HANDLEER::dealdoctor(CString tar) {
	CString rep = TEXT("{@nickname}");
	int loca = tar.Find(rep);
	if (loca == -1) return tar;
	CString ans = tar.Left(loca);
	ans += "博士";
	ans += tar.Mid(loca + rep.GetLength());
	return ans;
}

CString HANDLEER::dealSubt(CString tar) {
	CString ans = TEXT("");
	if (tar.Find(TEXT("text=")) == -1) return ans;
	ans = FindAndCut(tar, TEXT("text="), TEXT(", x="));
	return ans;
}

CString HANDLEER::dealStic(CString tar) {
	CString ans = TEXT("");
	if (tar.Find(TEXT("text=")) == -1) return ans;
	ans = FindAndCut(tar, TEXT("text="), TEXT(", x="));
	return ans;
}

CString HANDLEER::dealmult(CString tar) {
	CString ans = TEXT("");
	if (tar.Find(TEXT("me=")) == -1) return ans;
	ans += FindAndCut(tar, _T("me="), _T(")]"));
	ans += TEXT(" ");
	ans += FindAndCut(tar, _T(")]"));
	return ans;
}

CString HANDLEER::dealAnim(CString tar) {
	CString ans = TEXT("");
	if (tar.Find(TEXT("e)]")) == -1) return ans;
	tar = FindAndCut(tar, _T("e)]"));
	while (tar.GetLength()) {
		tar = tar.Mid(4);
		ans += FindAndCut(tar, TEXT(""), TEXT("/>"));
		int a = tar.Find(TEXT("</>")) + 3;
		tar = tar.Mid(a);
		if (tar.GetLength()) ans += TEXT("\n");
	}
	return ans;
}