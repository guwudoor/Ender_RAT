#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <strsafe.h>

class Registry
{
	HKEY key;
	DWORD TotalKeys;
	DWORD lenValueKey = 1000;
	LPWSTR ValueofKey;
	LPWSTR RegStr;
	LPWSTR FileName;
	char *ad_path;
	char *curr_path;
public:
	Registry();
	~Registry();
	bool check_reg_key();
	bool set_reg_key();
	bool is_in_ad();
	void move_to_ad();
};