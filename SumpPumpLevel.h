/* SumpPumpLevel class helps Sump pump level analysis
*  using Arduino core for ESP8266 WiFi chip
*  by Patrick Jeanson 
*  
*/
#ifndef SUMPPUMPLEVEL_H
#define SUMPPUMPLEVEL_H
#define GS_SERIAL_LOG_1         // Print to Serial only server response
#define GS_SERIAL_LOG_2       //  Print to Serial client commands and server response

#include "arduino.h"
#include <vector>

class SumpPumpLevel
{
public:
	SumpPumpLevel( unsigned int iSize=10);
	int getLevel();
	void execute(void);
	String getHtmlStatus();
	String getError(){return String(" ");}
	String getDebugStatus();
protected:
	
private:
	int getSample();
	// Define the number of samples to keep track of. The higher the number, the
	// more the readings will be smoothed, but the slower the output will respond to
	// the input. Using a constant rather than a normal variable lets us use this
	// value to determine the size of the readings array.
	unsigned int    mNumReadingsMax;
	std::vector<int>  mReadings;      // the readings from the analog input
	int mReadIndex;              // the index of the current reading
	int mTotal;                  // the running total
	int mAverage;                // the average
	int mRawReadPort;
	int mInputPin;  //Pin A3
	int mMinRead;
	int mMaxRead;


};
#endif // SUMPPUMPLEVEL_H
