#ifndef __POTENTIOMETER_H
#define __POTENTIOMETER_H

#include "PIDSource.h"
#include "LiveWindow/LiveWindowSendable.h"

class AnalogChannel;

class Potentiometer : public PIDSource, public LiveWindowSendable {
private:
	AnalogChannel *backend;
	float a, b, c;

	ITable *m_table;

	void InitPotentiometer(uint8_t moduleNumber, uint32_t channel);
public:
	Potentiometer(uint8_t moduleNumber, uint32_t channel);
	Potentiometer(uint32_t channel);

	/**
	 * Coeffecients for something of the form "angle = av^2 + bv + c"
	 */
	Potentiometer *setVoltageToAngle(float a, float b, float c);

	float GetAngle();
	float GetRawAngle();

	double PIDGet();

	void UpdateTable();
	void StartLiveWindowMode();
	void StopLiveWindowMode();
	std::string GetSmartDashboardType();
	void InitTable(ITable *subTable);
	ITable * GetTable();
};
#endif
