#include <iostream>
#include <string.h>

using namespace std;

class errorLog
	{
		private:
			FILE* fa;
			string logFileName;
			void fileCreate();
			const char* getTime();
		public:	
			errorLog();
			errorLog(string);
			void insertLog(string);
			FILE* getLogFile();
			void changeLogFile(string);
	};
	
class ScriptManager
	{
		private:
			FILE* script;
			errorLog log;
			int* intvariablesList;
			string* intVariablesName;
			int intVariablesI;
			string ScriptName;
					
			int numbOfInstructions;
			void LoadScript(string);
			void NumbOfInstructions();
			int SearchVariable();
		public:
			ScriptManager(string);
			void RunScript();
			void CloseScript();
	};

