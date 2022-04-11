#pragma once
#include <string>
//#include "TText.h"

using namespace std;

struct TNode;

struct TMem {
	TNode* pFirst, * pFree, * pLast;
};

struct TNode {
	char str[81];
	TNode* pNext, * pDown;
	static TMem mem;
	bool flag;

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
	static void initMem(int s = 100)
	{
		mem.pFirst = (TNode*)new char[sizeof(TNode)];
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
	//static void cleanMem(TText& txt);
};


//void TNode::cleanMem(TText& txt)
//{
//	TNode* p = mem.pFree;
//	while (p) {
//		p->flag = true;
//		p = p->pNext;
//	}
//	for (txt.reset(); !txt.isEnd(); txt.goNext()) {
//		txt.setFlag();
//	}
//	p = mem.pFirst;
//	while (p <= mem.pLast) {
//		if (!p->cleanMem) {
//			delete p;
//		}
//		p++;
//	}
//}