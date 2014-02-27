#include "AnalogPot.h"

#include "AnalogChannel.h"
#include "LiveWindow/LiveWindow.h"

#include "../Time.h"

void AnalogPot::InitAnalogPot(uint8_t moduleNumber, uint32_t channel) {
	backend = new AnalogChannel(moduleNumber, channel);

	LiveWindow::GetInstance()->AddSensor("Encoder", backend->GetModuleNumber(),
			backend->GetChannel(), this);

	// Default to just voltage
	this->a = 0;
	this->b = 1;
	this->c = 0;

	pTime = GetAngle();
	pAngle = getCurrentMillis();
	for (int i = 0; i < ANALOG_POT_AVERAGE_LENGTH; i++) {
		this->pRate[i] = 0;
	}
}

AnalogPot::AnalogPot(uint8_t moduleNumber, uint32_t channel) {
	InitAnalogPot(moduleNumber, channel);
}

AnalogPot::AnalogPot(uint32_t channel) {
	InitAnalogPot(GetDefaultAnalogModule(), channel);
}

void AnalogPot::setVoltageToAngle(float a, float b, float c) {
	this->a = a;
	this->b = b;
	this->c = c;
}

float AnalogPot::GetRawAngle() {
	float volts = backend->GetVoltage();
	return (this->a * volts * volts) + (this->b * volts) + this->c;
}

float AnalogPot::GetAngle() {
	float volts = backend->GetAverageVoltage();
	return (this->a * volts * volts) + (this->b * volts) + this->c;
}

/**
 * Units per second
 */
float AnalogPot::GetRate() {
	float pAngle = this->pAngle;
	this->pAngle = GetAngle();

	float pTime = this->pTime;
	this->pTime = getCurrentMillis();

	float totalRate = 0;
	float totalCounts = 0;
	for (int i = 1; i < ANALOG_POT_AVERAGE_LENGTH; i++) {
		this->pRate[i - 1] = this->pRate[i];
		totalCounts += i;
		totalRate += this->pRate[i - 1] * (float) i;
	}
	{
		this->pRate[ANALOG_POT_AVERAGE_LENGTH - 1] = (1000.0 * (GetAngle()
				- pAngle) / (getCurrentMillis() - pTime));
		totalRate += this->pRate[ANALOG_POT_AVERAGE_LENGTH - 1]
				* (float) ANALOG_POT_AVERAGE_LENGTH;
		totalCounts += ((float) ANALOG_POT_AVERAGE_LENGTH);
	}
	return totalRate / totalCounts;
}

double AnalogPot::PIDGet() {
	return GetAngle();
}

void AnalogPot::StartLiveWindowMode() {
}

void AnalogPot::StopLiveWindowMode() {
}

std::string AnalogPot::GetSmartDashboardType() {
	return "Encoder";
}

void AnalogPot::InitTable(ITable *subTable) {
	m_table = subTable;
	UpdateTable();
}

ITable * AnalogPot::GetTable() {
	return m_table;
}

void AnalogPot::UpdateTable() {
	if (m_table != NULL) {
		m_table->PutNumber("Speed", GetRate());
		m_table->PutNumber("Distance", GetAngle());
		m_table->PutNumber("Distance per Tick", backend->GetAverageVoltage());
	}
}
