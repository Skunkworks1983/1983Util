#ifndef __STALLABLE_MOTOR_H_
#define __STALLABLE_MOTOR_H_
#include "WPILib.h"

class StallableMotor: public SpeedController {
private:
	SpeedController *backend;
	Encoder *stallEncoder;
	float cacheSpeed;
	UINT8 cacheSyncGroup;
	double stallStart;
	double stallTimeThreshold;
	double stallTimeRefresh;
	bool stalled;
	int stalledCount;
public:
	static std::vector<StallableMotor*> motors;
	static void updateControllers();
	
	StallableMotor(SpeedController *backend, Encoder *stallEncoder,
			double stallTimeTreshold = 100, double stallTimeRefresh = 1000);
	~StallableMotor();
	virtual void Set(float speed, UINT8 syncGroup = 0);
	virtual float Get();
	virtual void Disable();
	bool isStalled();
	void updateController();
	void PIDWrite(float speed);
};

#endif
