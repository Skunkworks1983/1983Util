#ifndef __ANALOGRANGE_IO_BUTTON_H
#define __ANALOGRANGE_IO_BUTTON_H
#include "WPILib.h"

class AnalogRangeIOButton: public Button {
private:
	double lowThreshold, highThreshold;
	int port;
public:
	AnalogRangeIOButton(int port, double lowThreshold, double highThreshold);
	virtual ~AnalogRangeIOButton();
	virtual bool Get();
};

#endif

