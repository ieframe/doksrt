#ifndef WIN32_H
#define WIN32_H

#include <windows.h>
#include <tlhelp32.h>

DWORD process_id(char *const window);
void module_info(DWORD id, MODULEENTRY32 *module);
HANDLE process_open(DWORD id);
BOOL process_alive(HANDLE handle);

#endif