#include "Potentiometer.h"

#include "AnalogChannel.h"
#include "LiveWindow/LiveWindow.h"

void Potentiometer::InitPotentiometer(uint8_t moduleNumber, uint32_t channel) {
	backend = new AnalogChannel(moduleNumber, channel);

	LiveWindow::GetInstance()->AddSensor("Gyro", backend->GetModuleNumber(),
			backend->GetChannel(), this);

	// Default to just voltage
	this->a = 0;
	this->b = 1;
	this->c = 0;
}

void AnalogPot::UpdateTable() {
	if (m_table != NULL) {
		m_table->PutNumber("Value", GetAngle());
	}
}

void AnalogPot::setVoltageToAngle(float a, float b, float c) {
	this->a = a;
	this->b = b;
	this->c = c;
	return this;
}

float AnalogPot::GetRawAngle() {
	float volts = backend->GetVoltage();
	return (this->a * volts * volts) + (this->b*volts) + this->c;
}

float AnalogPot::GetAngle() {
	float volts = backend->GetAverageVoltage();
	return (this->a * volts * volts) + (this->b*volts) + this->c;
}

double AnalogPot::PIDGet() {
	return GetAngle();
}

void AnalogPot::StartLiveWindowMode() {
}

void AnalogPot::StopLiveWindowMode() {
}

std::string AnalogPot::GetSmartDashboardType() {
	return "Gyro";
}

void AnalogPot::InitTable(ITable *subTable) {
	m_table = subTable;
	UpdateTable();
}

ITable * AnalogPot::GetTable() {
	return m_table;
}
