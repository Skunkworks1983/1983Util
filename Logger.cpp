#include "Logger.h"
// CSTDLIB
#include <stdarg.h>
#include <stdio.h>
// WPILib
#include "SmartDashboard/SendableChooser.h"

Logger::Level Logger::minLogLevel = Logger::kFinest;
SendableChooser *Logger::chooser = NULL;

Logger::Logger() {
}

Logger::~Logger() {
}

void Logger::log(Level level, char *src, char *fmt, ...) {
	if (chooser != NULL) {
		int *obj = (int*) chooser->GetSelected();
		if (obj != NULL) {
			minLogLevel = (Logger::Level) *obj;
		}
	}
	if (level <= minLogLevel) {
		va_list args;
		va_start(args, fmt);
		char formatted[250];
		vsprintf(formatted, fmt, args);
		printf("[%s] (%s):\t%s\n", Logger::logLevelToName(level), src,
				formatted);
		va_end(args);
	}
}

SendableChooser *Logger::createLogLevelChooser() {
	if (chooser == NULL) {
		chooser = new SendableChooser();
		for (int l = Logger::kSevere; l < Logger::kFinest; l++) {
			chooser->AddObject(logLevelToName((Logger::Level) l), new int(l));
		}
		chooser->AddDefault(logLevelToName(Logger::kFinest), new int(Logger::kFinest));
	}
	return chooser;
}
