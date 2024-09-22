#include "pch.h"
#include "handler.h"
#include <cstring>

HANDLEER::HANDLEER(CString &target){
	text = target;
	afterhand = TEXT("");
	readfile();
	handlerer();
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
	if (note == TEXT("[Deci") || note == TEXT("[deci")) return dealdeci(tar);
	if (note == TEXT("[Pred") || note == TEXT("[pred")) return dealpred(tar);
	if (note == TEXT("[Subt") || note == TEXT("[subt")) return dealSubt(tar);
	if (note == TEXT("[Stic") || note == TEXT("[stic")) return dealSubt(tar);
	if (note == TEXT("[Mult") || note == TEXT("[mult")) return dealSubt(tar);
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
		rp = tar.Find(rt, lp);
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