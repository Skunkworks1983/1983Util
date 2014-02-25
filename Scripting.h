#ifndef __SCRIPTING_H
#define __SCRIPTING_H

class SendableChooser;
class Command;
class Autonomous;

/**
 * Starts an arbitrary command.
 */
class ScriptRunner {
public:
	virtual void startCommand() = 0;
	virtual ~ScriptRunner() {
	}
};
/**
 * Starts an arbitrary command with the command parameter.
 */
class ScriptCommand: public ScriptRunner {
private:
	Command *local;
public:
	ScriptCommand(Command *start);
	virtual ~ScriptCommand();
	virtual void startCommand();
};
/**
 * Loads and starts an arbitrary autonomous command.
 */
class ScriptLoader: public ScriptRunner {
private:
	char *fileName;
public:
	ScriptLoader(char *fName);
	virtual ~ScriptLoader();
	virtual void startCommand();
};

class Scripting {
public:
	/**
	 * @brief Returns a file's contents
	 * 
	 * Returns a char array containing the contents of the location file.
	 * size is modified by the function to return the size of the file.
	 * @param file Location of the file
	 * @param size Is modified by the function to return the file size.
	 * @return File contents
	 */
	static char *readFromFile(char *file, int &size);

	static Autonomous *createCommand(int size, char *rawData);
	
	/**
	 * @brief Creates a SendableChooser from a folder of autonomous files
	 * 
	 * Creates a SendableChooser.  The options are all of the files in the locations folder.
	 * Calling GetSelected returns a char array, which is the absolute path of the file selected.
	 * @param scriptLocations The absolute path to the folder containing script locations.  Requries trailing slash
	 * @return The SendableChooser (GetSelected returns a char array)
	 */
	static SendableChooser *generateAutonomousModes(char *scriptLocations);
};
#endif
