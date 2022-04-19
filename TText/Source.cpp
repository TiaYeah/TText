#include <iostream>
#include "TText.h"
#include <fstream>
#include <locale>

TMem TNode::mem;

using namespace std;

void main()
{
	TNode::initMem();
	setlocale(LC_ALL, "Russian");

	TText text;
	ifstream ifs("TestText.txt");

	text.setFirst(text.readRec(ifs));
	text.reset();
	text.insDownLine("First.First");
	text.goDownLine();
	text.insDownLine("First.First.First");
	text.goDownLine();
	text.insDownLine("First.First.Second");



	text.print();
}