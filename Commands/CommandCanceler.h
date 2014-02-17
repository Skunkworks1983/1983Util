#ifndef __CMD_COMMANDCANCEL_H
#define __CMD_COMMANDCANCEL_H

#include "Commands/Command.h"

class Subsystem;
class CommandCanceler: public Command {
private:
	Command *cancel;
public:
	CommandCanceler(Command *cancel);
	~CommandCanceler();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
