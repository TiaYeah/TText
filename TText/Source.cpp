#include <iostream>
#include "TText.h"
#include <fstream>
#include <locale>
#include <conio.h>	
#define HOME	71
#define DOWN	80
#define NEXT	77
#define UP	72
#define ESC	27
#define INS	82
#define DEL	83
#define ENTER	13

TMem TNode::mem;

using namespace std;

void main()
{
	TNode::initMem();
	setlocale(LC_ALL, "Russian");

	TText text;
	char ch;
	ifstream ifs("TestText.txt");

	text.setFirst(text.readRec(ifs));
	text.reset();
	text.insDownLine("First.First");
	text.goDownLine();
	text.insDownLine("First.First.First");
	text.goDownLine();
	text.insDownLine("First.First.Second");

	text.print();
	/*do {
		cout << ">,v,^, Home, Ins, Del, Enter, Esc";
		ch = _getch();
		if (ch == 0xE0) ch = _getch();
		if (ch == ESC) break;
		if (ch != ENTER) ch = _getch();
		switch (ch) {
		case ENTER:
			break;
		case HOME:text.goFirstLine(); break;
		case DOWN:text.goDownLine(); break;
		case NEXT:text.goNextLine(); break;
		case UP:  text.goPrevLine(); break;
		case INS:
			break;
		case DEL:
			break;

		}
	} while (ch != ESC);*/


	//TText text2 = text.copy();

	ofstream ofs("TestText.txt", ios::trunc);
	text.printFileMain(ofs);

	/* First
	 Second
	 Third*/

	TNode::printFree();
}