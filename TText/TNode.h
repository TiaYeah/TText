//#pragma once
//#include <string>
//
//struct TNode
//{
//	char str[81];
//	TNode* pNext, * pDown;
//	TNode(char* _str = nullptr, TNode* _pNext = nullptr, TNode* _pDown = nullptr)
//	{
//		pNext = _pNext;
//		pDown = _pDown;
//		if (str)
//		{
//			strcpy(str, _str);
//		}
//		else {
//			str[0] = '\0';
//		}
//	}
//};

#pragma once

#include <iostream>
#include <string>
#include "TMem.h"
//#include "TText.h"

using namespace std;

class TText;

struct TNode {
	char str[81];
	TNode* pNext, * pDown;
	static TMem mem;
	bool flag;
public:
	TNode(char* _str = nullptr, TNode* _pNext = nullptr, TNode* _pDown = nullptr)
	{
		pNext = _pNext;
		pDown = _pDown;
		if (str)
		{
			strcpy(str, _str);
		}
		else {
			str[0] = '\0';
		}
		flag = false;
	}
	void* operator new(size_t size)
	{
		TNode* res = mem.pFree;
		if (res) {
			mem.pFree = mem.pFree->pNext;
		}
		return res;
	}

	void operator delete(void* del)
	{
		if (del) {
			TNode* delNode = (TNode*)del;
			TNode* pLastFree = mem.pFree;
			mem.pFree = delNode;
			mem.pFree->pNext = pLastFree;
		}
	}

	static void cleanMem(TText& txt);
	/*{
		TNode* p = mem.pFree;
		while (p) {
			p->flag = true;
			p = p->pNext;
		}
		for (txt.reset(); !txt.isEnd(); txt.goNext()) {
			txt.setFlag();
		}
		p = mem.pFirst;
		while (p <= mem.pLast) {
			if (!p->flag) {
				delete p;
				p->flag = true;
			}
			p++;
		}
	}*/

	static void initMem(int s = 30)
	{
		mem.pFirst = (TNode*)new char[sizeof(TNode) * s];
		mem.pFree = mem.pFirst;
		mem.pLast = mem.pFirst + s - 1;
		TNode* p = mem.pFirst;
		for (int i = 0; i < s - 1; i++) {
			p->pNext = p + 1;
			p = p->pNext;
			p->str[0] = '\0';
			p->flag = false;
		}
		mem.pLast->pNext = nullptr;
	}

	TNode* copyNode(TNode* p)
	{
		TNode* pN, * pD;
		if (p->pNext) {
			pN = copyNode(p->pNext);
		}
		if (p->pDown) {
			pD = copyNode(p->pDown);
		}
		TNode* res;
		res = new TNode(p->str, pN, pD);
		return res;
	}

	static void printFree()
	{
		TNode* p = mem.pFree;
		while (p) {
			if (p->str[0] != '\0')
				cout << p->str << endl;
			p = p->pNext;
		}
	}
};