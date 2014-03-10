#include "Logger.h"
#include <stdarg.h>
#include <stdio.h>

Logger::Level Logger::minLogLevel = Logger::kFinest;

Logger::Logger() {
}

Logger::~Logger() {
}

void Logger::log(Level level, char *src, char *fmt, ...) {
	if (level <= minLogLevel) {
		va_list args;
		va_start(args, fmt);
		char formatted[250];
		vsprintf(formatted, fmt, args);
		printf("[%s] (%s):\t%s\n", Logger::logLevelToName(level), src, formatted);
		va_end(args);
	}
}
