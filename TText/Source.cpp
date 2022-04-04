#include <iostream>
#include "TText.h"
#include <fstream>
#include <locale>

using namespace std;

void main()
{
	setlocale(LC_ALL, "Russian");

	TText text;
	ifstream ifs("TestText.txt");

	text.setFirst(text.readRec(ifs));
	text.reset();
	text.insDownLine((char*)"First.First");



	text.print();
}