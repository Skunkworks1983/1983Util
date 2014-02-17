#ifndef __STALLABLE_MOTOR_H
#define __STALLABLE_MOTOR_H
#include "WPILib.h"
#include "../Sensors/AnalogPot.h"

class StallableMotor : public SpeedController {
private:
	SpeedController *backend;
	Encoder *stallEncoder;
	AnalogPot *stallPot;
	float cacheSpeed;
	UINT8 cacheSyncGroup;
	double stallStart;
	double stallTimeThreshold;
	double stallTimeRefresh;
	double stallSpeed;
	bool stalled;
	int stalledCount;
public:
	static std::vector<StallableMotor*> motors;
	static void updateControllers();

	StallableMotor(SpeedController *backend, double stallSpeed = 0,
			double stallTimeTreshold = 100, double stallTimeRefresh = 1000);
	
	StallableMotor *setPotSource(AnalogPot *pot);
	StallableMotor *setEncoderSource(Encoder *pot);
	~StallableMotor();
	virtual void Set(float speed, UINT8 syncGroup = 0);
	virtual float Get();
	virtual void Disable();
	bool isStalled();
	void updateController();
	void PIDWrite(float speed);
};

#endif
