#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include "command_def.h"
#include "com_vars.h"
#include "server.h"
using namespace std;

void display_client_help()
{
	cout << "----> show <msg>   - Display a Message Box with <msg> on client's system" << endl;
	cout << "----> exit         - Go back" << endl;
	cout << "----> disconnect   - Disconnect the current client" << endl;
	cout << "----> username     - Display Client PC's username" << endl;
	cout << "----> help         - Display this help message" << endl;
}

void display_admin_help()
{
	cout << " Commands:" << endl;
	cout << "--> show clients - Display all the connected clients" << endl;
	cout << "--> client <id>  - To Open Client Interacting Panel for that Client" << endl;
	cout << "--> quit         - End this program" << endl;
	cout << "--> help         - Display this help message" << endl;
}

void show_clients()
{
	cout << " S.No." << string(15, ' ') << "ID" << string(40, ' ') << "Username" << endl;
	for(int i=0;i < client_array.size();i++)
	{
		cout << " " << i << string(15, ' ') << client_array[i]->get_client_id() << string(10, ' ') << client_array[i]->get_username() << endl;
	}
}

