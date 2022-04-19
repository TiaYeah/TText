#include "../TText/TNode.h"
#include "../TText/TText.h"

void TNode::cleanMem(TText& txt)
{
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
}