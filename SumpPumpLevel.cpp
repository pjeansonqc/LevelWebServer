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
mMinRead(1023),
mMaxRead(0),
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
	mMinRead = _min(lRawRead, mMinRead);
	mMaxRead = _max(lRawRead, mMaxRead);
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

String SumpPumpLevel::getStatus()
{
	String lMsg="";
	lMsg += "  Average.:" + String(mAverage) + "\n";

	lMsg += "\n";
	return lMsg;
}
