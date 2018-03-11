#include "LevelHistory.h"
#include "Statistic.h"

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
  Statistic       lStats;
  int i=0;
	lMsg += "<p>  ";
	for (std::deque<int>::iterator it = mLevels.begin();it != mLevels.end();++it)
	{
    lStats.add(*it);
		lMsg += String(*it) + ",";
    if(i > 20)
    {
      i=0;
      lMsg += "</p>\n";
      lMsg += "<p>  ";
    }
    i++;
  }
	lMsg += "</p>\n";
 
  lMsg += "<p>Min.........:" + String( lStats.minimum(),1 ) + "</p>\n";
  lMsg += "<p>Max:........:" + String( lStats.maximum(),1 ) + "</p>\n";
  lMsg += "<p>Average.....:" + String( lStats.average(),1) + "</p>\n";
  lMsg += "<p>Variance....:" + String( lStats.variance(),1) + "</p>\n";
  lMsg += "<p>Std Dev.....:" + String( lStats.pop_stdev(),1) + "</p>\n";
  lMsg += "<p>Alarm Low...:" + String( ( lStats.average() - 4 * lStats.pop_stdev() ),1) + "</p>\n";
  lMsg += "<p>Alarm High..:" + String( ( lStats.average() + 4 * lStats.pop_stdev() ),1) + "</p>\n";
	return lMsg;
}
