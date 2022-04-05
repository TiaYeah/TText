#include "TNode.h"
#include "TStack.h"
#include <iostream>
#include <fstream>

using namespace std;

#pragma once
class TText
{
	TNode* pFirst, * pCurr;
	TStack<TNode*> st;
public:
	TText()
	{
		pFirst = pCurr = nullptr;
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
			pCurr = pCurr->pNext;
		}
	}

	void goFirstLine()
	{
		pCurr = pFirst;
		st.ClearStack();
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
			cout << p->str << endl;
			if (p->pDown) {
				cout << '{' << endl;
				tab++;
				for (int i = 0; i < tab; i++)
				{
					cout << "  ";
				}
				printRec(p->pDown, tab);
				tab--;
				cout << '}' << endl;
			}
			printRec(p->pNext, tab);
		}
	}

	void print()
	{
		printRec(pFirst, 0);
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
};

