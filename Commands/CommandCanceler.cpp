#include "CommandCanceler.h"

#include "Commands/Command.h"
#include "Commands/Scheduler.h"

CommandCanceler::CommandCanceler(Command *sys) :
	Command("CommandCanceler") {
	this->cancel = sys;
}

CommandCanceler::~CommandCanceler() {
}

void CommandCanceler::Initialize() {
	Scheduler::GetInstance()->Remove(cancel);
}

void CommandCanceler::Execute() {
}

bool CommandCanceler::IsFinished() {
	return true;
}

void CommandCanceler::End() {
}

void CommandCanceler::Interrupted() {
}
