#ifndef __OVERRIDABLE_BUTTON_H
#define __OVERRIDABLE_BUTTON_H
#include "WPILib.h"

class OverridableButton : public Button {
private:
	Trigger *override;
	Trigger *button;
	bool lastState;
	bool overrideState;
public:
	OverridableButton(Trigger *override, Trigger *button, bool overrideState=true);
	virtual ~OverridableButton();
	virtual bool Get();
};

#endif

