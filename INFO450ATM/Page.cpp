#include "Page.h"


Page::Page(string header, string footer, int maxNumberOfLines)
{
	this->header = header;
	this->footer = footer;
	this->maximumNumberOfLines = maximumNumberOfLines;
}

Page::~Page()
{
}

void Page::AddLine(string lineText)
{
	collectionOfLines.push_back(lineText);
}
