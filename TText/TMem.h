#pragma once
#include <string>
#include "TNode.h"

using namespace std;

struct TNode;

struct TMem {
	TNode* pFirst, * pFree, * pLast;
};