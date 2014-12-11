#ifndef PAGE_H
#define PAGE_H

#include <string>
#include <vector>

using namespace std;

#pragma once
class Page
{
public:
	string header = "";
	string footer = "";
	int maximumNumberOfLines = 0;
	vector<string> collectionOfLines;

	Page(string header, string footer, int maxNumberOfLines);
	~Page();

	void AddLine(string lineText);
};

#endif