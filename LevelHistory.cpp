#include "LevelHistory.h"


LevelHistory::LevelHistory( unsigned int iSize/*=10*/) : 
mLevels(),
mMaxNumberOfLevels(iSize)
{
	
}

void LevelHistory::addLevel(int iValue)
{
	mLevels.push_back(iValue);
	if(mLevels.size() > mMaxNumberOfLevels)
	{
		mLevels.pop_front();
	}
}



String LevelHistory::getDebugStatus()
{
	String lMsg="Levels History:\n";
	lMsg += "  values:";
	for (std::deque<int>::iterator it = mLevels.begin();it != mLevels.end();++it)
	{
		lMsg += String(*it) + ",";
	}
	lMsg += "\n";
	return lMsg;
}

String LevelHistory::getHtmlStatus()
{
	String lMsg="<h1>Readings:</h1>";

	lMsg += "<p>  ";
	for (std::deque<int>::iterator it = mLevels.begin();it != mLevels.end();++it)
	{
		lMsg += String(*it) + ",";
	}
	lMsg += "</p>\n";
	return lMsg;
}
