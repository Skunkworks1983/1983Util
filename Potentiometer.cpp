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

void Potentiometer::UpdateTable() {
	if (m_table != NULL) {
		m_table->PutNumber("Value", GetAngle());
	}
}

Potentiometer *Potentiometer::setVoltageToAngle(float a, float b, float c) {
	this->a = a;
	this->b = b;
	this->c = c;
	return this;
}

float Potentiometer::GetRawAngle() {
	float volts = backend->GetVoltage();
	return (this->a * volts * volts) + (this->b*volts) + this->c;
}

float Potentiometer::GetAngle() {
	float volts = backend->GetAverageVoltage();
	return (this->a * volts * volts) + (this->b*volts) + this->c;
}

double Potentiometer::PIDGet() {
	return GetAngle();
}

void Potentiometer::StartLiveWindowMode() {
}

void Potentiometer::StopLiveWindowMode() {
}

std::string Potentiometer::GetSmartDashboardType() {
	return "Gyro";
}

void Potentiometer::InitTable(ITable *subTable) {
	m_table = subTable;
	UpdateTable();
}

ITable * Potentiometer::GetTable() {
	return m_table;
}
