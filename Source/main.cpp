#include <iostream>
#include <conio.h>
#include "ScriptManager.h"

using namespace std;

main() 
	{
		char nome[200];
		cout << "Inserisci il nome dello script da caricare (Nome + Estensione): ";
		cin >> nome;
		try
			{
				ScriptManager Script(nome);	
				Script.RunScript();
				Script.CloseScript();			
			}
		catch(const char* msg)
			{
				cout << msg;
			}
		getch();
	}
