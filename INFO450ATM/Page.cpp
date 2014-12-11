#include "Page.h"


Page::Page()
{
}

Page::~Page()
{
}

void Page::AddLine(string lineText)
{
	if (collectionOfLines.size() < (maximumNumberOfLines + 1))
	{
		collectionOfLines.push_back(lineText);
	}	
}

string Page::GetLine(unsigned int lineNumber)
{
	if (lineNumber < collectionOfLines.size())
	{
		return collectionOfLines[lineNumber];
	}
	else
	{
		return "";
	}
}

unsigned int Page::GetMaximumNumberOfLines()
{
	return this->maximumNumberOfLines;
}

unsigned int Page::GetNumberOfLines()
{
	return this->collectionOfLines.size();
}