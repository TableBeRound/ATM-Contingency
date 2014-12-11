#ifndef PAGE_H
#define PAGE_H

#include <string>
#include <vector>

using namespace std;

#pragma once
class Page
{
private:
	unsigned int maximumNumberOfLines = 10;
	vector<string> collectionOfLines;

public:
	Page();
	~Page();

	void AddLine(string lineText);
	unsigned int GetMaximumNumberOfLines();
	string GetLine(unsigned int lineNumber);
	unsigned int GetNumberOfLines();
};

#endif