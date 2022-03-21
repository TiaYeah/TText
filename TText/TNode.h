#pragma once
#include <string>

struct TNode
{
	char str[81];
	TNode* pNext, * pDown;
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
	}
};