#include "SumpPumpLevel.h"


int SumpPumpLevel::getSample()
{
	return (4096 - analogRead(mInputPin) );
}


SumpPumpLevel::SumpPumpLevel( unsigned int iSize/*=10*/) : 
mReadings(),  
mReadIndex(0),              // the index of the current reading
mTotal(0),                  // the running mTotal
mAverage(0),                // the average
mRawReadPort(A13),
mInputPin(A3),  //Pin A3
mMinRead(0),
mMaxRead(4095),
mNumReadingsMax(iSize)
{
	mReadings.resize(mNumReadingsMax, 0);
}



void SumpPumpLevel::execute(void)
{
	int lRawRead = 0;
	int lRead = 0; // Reading remapped from 0 to 100
	// read from the sensor:
	lRawRead = getSample();
	// Re-Scale to 0-100%
	if (mMaxRead - mMinRead != 0)
	{
		lRead = map(lRawRead, mMinRead, mMaxRead, 0, 100);
	}
	// Remove from total the old sample
	mTotal -= mReadings[mReadIndex];
	// add the new reading to the mTotal:
	mTotal += lRead;
	//Store the new reading
	mReadings[mReadIndex] = lRead;
	// advance to the next position in the array:
	++mReadIndex;
	// if we're at the end of the array...
	if (mReadIndex >= (int)mReadings.size())
	{
		// ...wrap around to the beginning:
		mReadIndex = 0;
	}
	// calculate the average:
	mAverage = mTotal / (int)mReadings.size();
	// send it to the computer as ASCII digits
}
int SumpPumpLevel::getLevel()
{
	return mAverage;
}

String SumpPumpLevel::getDebugStatus()
{
	String lMsg="Readings:\n";
	lMsg += "  min.....:" + String(mMinRead) + "\n";
	lMsg += "  max.....:" + String(mMaxRead) + "\n";
	lMsg += "  Total...:" + String(mTotal) + "\n";
	lMsg += "  Average.:" + String(mAverage) + "\n";
	for (std::vector<int>::iterator it = mReadings.begin();it != mReadings.end();++it)
	{
		lMsg += String(*it) + ",";
	}
	lMsg += "\n";
	return lMsg;
}

String SumpPumpLevel::getHtmlStatus()
{
	String lMsg="<h1>Readings:</h1>";
	// lMsg += "<p>  min.....:" + String(mMinRead) + "</p>\n";
	// lMsg += "<p>  max.....:" + String(mMaxRead) + "</p>\n";
	// lMsg += "<p>  Total...:" + String(mTotal)   + "</p>\n";
	lMsg += "<p>  Level.:" + String(mAverage) + "</p>\n";
	lMsg += "<p>    last levels:";
	for (std::vector<int>::iterator it = mReadings.begin();it != mReadings.end();++it)
	{
		lMsg += String(*it) + ",";
	}
	lMsg += "</p>\n";
	return lMsg;
}
