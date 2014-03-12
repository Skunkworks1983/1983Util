#ifndef LOGGER_H_
#define LOGGER_H_
// CSTDLIB
#include <stdarg.h>
#include <stdlib.h>

class SendableChooser;

class Logger {
public:
	enum Level {
		kSevere, kWarning, kDiagnostic, kInfo, kConfig, kFine, kFiner, kFinest
	};
private:
	static Level minLogLevel;
	static SendableChooser *chooser;
	Logger();
	virtual ~Logger();
	inline static char* logLevelToName(Level level) {
		switch (level) {
		case kSevere:
			return "SEVERE";
		case kWarning:
			return "WARNING";
		case kDiagnostic:
			return "DIAG";
		case kInfo:
			return "INFO";
		case kConfig:
			return "CONFIG";
		case kFine:
			return "FINE";
		case kFiner:
			return "FINER";
		case kFinest:
			return "FINEST";
		default:
			return "UNKNOWN";
		}
	}
public:
	static inline void setLoggingLevel(Level level) {
		minLogLevel = level;
	}
	static void log(Level level, char *src, char *fmt, ...);
	static SendableChooser *createLogLevelChooser();
};

#endif /* LOGGER_H_ */
