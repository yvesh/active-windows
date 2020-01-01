#include "windowwindows.h"

#include <windows.h>
#include <atlstr.h>
#include <string>

void windowwindows::getActiveWindow(Napi::Object& obj) {
	char window_title[256];

	HWND foreground_window = GetForegroundWindow();
	GetWindowText(foreground_window, window_title, sizeof(window_title));

	DWORD pid;
	GetWindowThreadProcessId(foreground_window, &pid);

	// Process
	LPWSTR process_filename = new WCHAR[MAX_PATH];
	DWORD charsCarried = MAX_PATH;

	HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_QUERY_INFORMATION, false, pid);

	QueryFullProcessImageNameW(hProc, 0, process_filename, &charsCarried);

	std::string fullpath = CW2A(process_filename);

	const size_t last_slash_idx = fullpath.find_last_of("\\/");

	if (std::string::npos != last_slash_idx) {
		fullpath.erase(0, last_slash_idx + 1);
	}

	obj.Set("os", "windows");
	obj.Set("windowClass", fullpath);
	obj.Set("windowName", window_title);
	obj.Set("windowDesktop", "0");
	obj.Set("windowType", "0");
	obj.Set("windowPid", std::to_string(pid));
	obj.Set("idleTime", "0");
}

Napi::Object windowwindows::getActiveWindowWrapped(const Napi::CallbackInfo& info)
{
	Napi::Env env = info.Env();

	Napi::Object obj = Napi::Object::New(env);
	windowwindows::getActiveWindow(obj);

	return obj;
}

Napi::Object windowwindows::Init(Napi::Env env, Napi::Object exports)
{
	exports.Set(
		"getActiveWindow", Napi::Function::New(env, windowwindows::getActiveWindowWrapped)
	);

	return exports;
}
