#pragma once
#include <iostream>
#include <fstream>
#include "TStack.h"
#include "TNode.h"

using namespace std;

class TText
{
	TNode* pFirst, * pCurr;
	TStack<TNode*> st;
public:
	TText(){}
	TText(TNode* p) 
	{
		pFirst = p;
	}

	void setFirst(TNode* _pFirst)
	{
		pFirst = _pFirst;
	}

	void goNextLine()
	{
		if (pCurr)
		{
			st.Push(pCurr);
			pCurr = pCurr->pNext;
		}
	}

	void goDownLine() 
	{
		if (pCurr)
		{
			st.Push(pCurr);
			pCurr = pCurr->pDown;
		}
	}

	void goFirstLine()
	{
		pCurr = pFirst;
		st.ClearStack();
	}

	void goPrevLine()
	{
		if (pCurr)
			pCurr = st.Pop();
		else throw - 1;
	}

	void insNextLine(char* str)
	{
		if (pCurr)
		{
			TNode* newStr = new TNode(str);
			newStr->pNext = pCurr->pNext;
			pCurr->pNext = newStr;
		}
	}

	void insNextSection(char* str)
	{
		if (pCurr)
		{
			TNode* newStr = new TNode(str);
			newStr->pDown = pCurr->pNext;
			pCurr->pNext = newStr;
		}
	}

	void insDownLine(char* str)
	{
		if (pCurr)
		{
			TNode* newStr = new TNode(str);
			newStr->pNext = pCurr->pDown;
			pCurr->pDown = newStr;
		}
	}

	void insDownSection(char* str)
	{
		if (pCurr)
		{
			TNode* newStr = new TNode(str);
			newStr->pDown = pCurr->pDown;
			pCurr->pDown = newStr;
		}
	}

	void delNextLine()
	{
		if (pCurr)
		{
			if (pCurr->pNext)
			{
				TNode* del = pCurr->pNext;
				pCurr->pNext = del->pNext;
				delete del;
			}
		}
	}

	void delDownLine()
	{
		if (pCurr)
		{
			if (pCurr->pDown)
			{
				TNode* del = pCurr->pDown;
				pCurr->pDown = del->pNext;
				delete del;
			}
		}
	}

	TNode* readRec(ifstream& ifs)
	{
		TNode* pHead = nullptr, * tmp = nullptr;
		char buf[81];
		while (!ifs.eof())
		{
			ifs.getline(buf, 80, '\n');
			if (buf[0] == '}') {
				break;
			}
			else if (buf[0] == '{') {
				tmp->pDown = readRec(ifs);
			}
			else {
				TNode* p = new TNode(buf);
				if (!pHead) {
					pHead = tmp = p;
				}
				else {
					tmp->pNext = p;
					tmp = p;
				}
			}
		}
		return pHead;
	}

	void read(char* fn)
	{
		ifstream ifs(fn);
		pFirst = readRec(ifs);
	}

	void printRec(TNode* p , int tab)
	{
		if (p) {
			if (p == pCurr) {
				cout << p->str << "<" << endl;
			}
			else { cout << p->str << endl; }
			if (p->pDown) {
				tab++;
				for (int i = 0; i < tab - 1; i++)
				{
					cout << "  ";
				}
				cout << '{' << endl;
				for (int i = 0; i < tab; i++)
				{
					cout << "  ";
				}
				printRec(p->pDown, tab);
				for (int i = 0; i < tab - 1; i++)
				{
					cout << "  ";
				}
				cout << '}' << endl;
				tab--;
			}
			if (p->pNext) {
				for (int i = 0; i < tab; i++)
				{
					cout << "  ";
				}
				printRec(p->pNext, tab);
			}
		}
	}

	void print()
	{
		printRec(pFirst, 0);
		cout << endl;
	}

	void printFile(TNode* p, ofstream& os)
	{
		if (p) {
			os << p->str << endl;
			if (p->pDown) {
				os << '{' << endl;
				printFile(p->pDown, os);
				os << '}' << endl;
			}
			if (p->pNext) {
				printFile(p->pNext, os);
			}
		}
	}

	void printFileMain(ofstream& os)
	{
		printFile(pFirst, os);
	}

	void reset()
	{
		st.ClearStack();
		pCurr = pFirst;
		st.Push(pCurr);
		if (pCurr->pNext) {
			st.Push(pCurr->pNext);
		} 
		if (pCurr->pDown) {
			st.Push(pCurr->pDown);
		}
	}

	void goNext()
	{
		pCurr = st.Pop();
		if (pCurr->pNext) {
			st.Push(pCurr->pNext);
		}
		if (pCurr->pDown) {
			st.Push(pCurr->pDown);
		}
	}

	bool isEnd()
	{
		return (st.IsEmpty());
	}

	void setFlag() {
		pCurr->flag = true;
	}

	TText* copy()
	{
		return new TText(pFirst->copyNode(pFirst));
	}
};

