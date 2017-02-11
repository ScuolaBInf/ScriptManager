#include <iostream>
#include <string.h>
#include <conio.h>
#include <ctime>
#include "ScriptManager.h"

using namespace std;


errorLog::errorLog()
	{
		
	}
	
errorLog::errorLog(string logFileName)
	{
		changeLogFile(logFileName);
	}

void errorLog::insertLog(string msg)
	{
		fa = fopen(logFileName.c_str(), "a");
		fprintf(fa, "%s %s", getTime(), msg.c_str());
		fprintf(fa, "%c", '\n');
		fclose(fa);	
	}
	
void errorLog::changeLogFile(string logFileName)
	{
		this -> logFileName = logFileName;
		fileCreate();		
	}	
	
FILE* errorLog::getLogFile()
	{
		return this -> fa;
	}
	
void errorLog::fileCreate()
	{
		fa = fopen(this -> logFileName.c_str(), "a");
		fclose(fa);		
	}
	
const char* errorLog::getTime()
	{
		time_t ct;
		ct = time(NULL);
		string data = ctime(&ct);
		data[24] = ':';
		return data.c_str();
	}

/***********************************************************************************************************************/

ScriptManager::ScriptManager(string ScriptName)
	{
		LoadScript(ScriptName);
		NumbOfInstructions();
		this -> intvariablesList = new int[200];
		this -> intVariablesName = new string[200];
		this -> intVariablesI = 0;
		log.changeLogFile("../Log/logfile.log");
	}

void ScriptManager::RunScript()
	{
		log.insertLog("Avvio Scipt");
		char istrction[200];

		while(!feof(this -> script))
			{
				fscanf(script, "%s", istrction);				
				if (strcmp(istrction, "start") == 0)
					{
						cout << "Script Start: " << endl << endl;
					}
				else if (strcmp(istrction, "output:") == 0)
					{
						bool fixbug = false;
						fscanf(script, "%s", istrction);
						for (int j = 0; j < intVariablesI; j++)
							{
								if (strcmp(intVariablesName[j].c_str(), istrction) == 0)
									{
										cout << intvariablesList[j] << endl;
										fixbug = true;
									}
							}
						if (fixbug != true)
							{
								printf ("\t");
								cout << istrction << ' ';
							}
					}
				else if (strcmp(istrction, "IntInput:") == 0)
					{
						fscanf(script, "%s", istrction);
						intVariablesName[intVariablesI] = istrction;
						cin >> intvariablesList[intVariablesI];
						intVariablesI++;
					}
				else if (strcmp(istrction, "IntDeclared:") == 0)
					{
						fscanf(script, "%s", istrction);
						intVariablesName[intVariablesI] = istrction;
						intVariablesI++;
					}
				else if (strcmp(istrction, "Operand+:") == 0)
					{
						intvariablesList[SearchVariable()] = intvariablesList[SearchVariable()] + intvariablesList[SearchVariable()]; 
					}
				else if (strcmp(istrction, "Operand-:") == 0)
					{
						intvariablesList[SearchVariable()] = intvariablesList[SearchVariable()] - intvariablesList[SearchVariable()]; 
					}
				else if (strcmp(istrction, "Operand*:") == 0)
					{
						intvariablesList[SearchVariable()] = intvariablesList[SearchVariable()] * intvariablesList[SearchVariable()]; 
					}
				else if (strcmp(istrction, "Operand/:") == 0)
					{
						intvariablesList[SearchVariable()] = intvariablesList[SearchVariable()] / intvariablesList[SearchVariable()]; 
					}
				else if (strcmp(istrction, "IntAssign:") == 0)
					{
						int num;
						fscanf(script, "%d", &num);
						intvariablesList[SearchVariable()] = num;
					}
				else if (strcmp(istrction, "end") == 0)
					{
						cout << endl << "End Script.";
						return;
					}
				else if (strcmp(istrction, "if>") == 0)
					{
						int righe;
						fscanf(script, "%d", &righe);
						if (intvariablesList[SearchVariable()] <= intvariablesList[SearchVariable()])
							{
								for (int a = 0; a < righe + 1; a++)
									{
										fscanf(script, "%s", istrction);
									}
							}	
					}
				else if (strcmp(istrction, "if<") == 0)
					{
						int righe;
						fscanf(script, "%d", &righe);
						if (intvariablesList[SearchVariable()] >= intvariablesList[SearchVariable()])
							{
								for (int a = 0; a < righe + 1; a++)
									{
										fscanf(script, "%s", istrction);
									}
							}	
					}
			}
	}
	
void ScriptManager::LoadScript(string ScriptName)
	{
		this -> script = fopen(ScriptName.c_str(), "r");
		if (script == NULL)
			{
				throw "Script not Load";
			}
	}

void ScriptManager::NumbOfInstructions()
	{
		char istrction[200];
		this -> numbOfInstructions = 0;
		while(!feof(this -> script))
			{
				fscanf(script, "%s", istrction);
				this -> numbOfInstructions++;
			} 
		fseek(script, 0, SEEK_SET);
	}
	
void ScriptManager::CloseScript()
	{
		fclose(this -> script);
		log.insertLog("Script Chiuso");
	}

int ScriptManager::SearchVariable()
	{
		char istrction[200];
		int i;
		fscanf(script, "%s", istrction);
		for (i = 0; i < intVariablesI; i++)
			{
				if (strcmp(intVariablesName[i].c_str(), istrction) == 0)
					{
						break;
					}	
			}
		return i;
	}
