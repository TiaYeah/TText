#include <iostream>
#include "TText.h"
#include <fstream>
#include <locale>

TMem TNode::mem;

using namespace std;

void main()
{
	setlocale(LC_ALL, "Russian");

	TText text;
	ifstream ifs("TestText.txt");

	text.setFirst(text.readRec(ifs));
	text.reset();/*
	text.insDownLine((char*)"First.First");
	text.goDownLine();
	text.insDownLine((char*)"First.First.First");
	text.goDownLine();
	text.insNextLine((char*)"First.First.Second");*/



	text.print();
}