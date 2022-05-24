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
#define z 122
#define x 120
#define c 99
#define v 118
#define p 112
#define f 102
#define m 109
#define s 115

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

	do {
		cout << endl;
		cout << "HOME - Go fist line" << endl;
		cout << "RIGHT - Go next line" << endl;
		cout << "DOWN - Go down line" << endl;
		cout << "UP - Go previous line" << endl;
		cout << "z - Insert next line" << endl;
		cout << "x - Insert next section" << endl;
		cout << "c - Insert down line" << endl;
		cout << "v - Insert down section" << endl;
		cout << "INS - Delete next line" << endl;
		cout << "DEL - Delete down line" << endl;
		cout << "p - Print" << endl;
		cout << "m - Clean mem" << endl;
		cout << "f - Print free" << endl;
		cout << "s - Save into a file" << endl;
		char* str = new char[100];
		ch = _getch();
		if (ch == 0xE0) ch = _getch();
		if (ch == ESC) break;
		if (ch != ENTER) ch = _getch();
		switch (ch) {
		case ENTER:
			break;
		case HOME: {
			text.goFirstLine(); 
			break;
		}
		case DOWN: {
			text.goDownLine();
			break; 
		}
		case NEXT: {
			text.goNextLine(); 
			break; 
		}
		case UP: {
			text.goPrevLine();
			break;
		}
		case z: {
			cout << "¬ведите строку" << endl;
			cin.getline(str,100);
			text.insNextLine(str);
			break;
		}
		case x: {
			cout << "¬ведите строку" << endl;
			cin.getline(str, 100);
			text.insNextSection(str);
			break;
		}
		case c: {
			cout << "¬ведите строку" << endl;
			cin.getline(str, 100);
			text.insDownLine(str);
			break;
		}
		case v: {
			cout << "¬ведите строку" << endl;
			cin.getline(str, 100);
			text.insDownSection(str);
			break;
		}
		case INS: {
			text.delNextLine();
			break;
		}
		case DEL: {
			text.delDownLine();
			break;
		}
		case p: {
			text.print();
			break;
		}
		case m: {
			TNode::cleanMem(text);
			break;
		}
		case f: {
			cout << "—вободные: " << endl;
			TNode::printFree();
			break;
		}
		case s: {
			ofstream ofs("TestText.txt", ios::trunc);
			text.printFileMain(ofs);
			break;
		}
		}
	} while (ch != ESC);



	//TText text2 = text.copy();

	//

	/* First
	 Second
	 Third*/
}