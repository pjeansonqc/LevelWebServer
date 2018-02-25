/* LevelHistory class helps Sump pump level analysis
*  using Arduino core for ESP8266 WiFi chip
*  by Patrick Jeanson 
*  
*/
#ifndef LEVEL_HISTORY_H
#define LEVEL_HISTORY_H
#define GS_SERIAL_LOG_1         // Print to Serial only server response
#define GS_SERIAL_LOG_2       //  Print to Serial client commands and server response

#include "arduino.h"
#include <deque>


class LevelHistory
{
public:
	LevelHistory( unsigned int iSize=10);
	void addLevel(int iLevel);
	String getHtmlStatus();
	String getDebugStatus();
protected:
	
private:
	
	std::deque<int>  mLevels;      // the readings from the analog input
	unsigned int mMaxNumberOfLevels;
};
#endif // LEVEL_HISTORY_H
