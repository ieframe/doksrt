#include "win32.h"
#include <assert.h>

DWORD process_id(char *const window)
{
    HWND handle;
    DWORD id;

    handle = FindWindowA(NULL, window);
    assert(handle != NULL);

    GetWindowThreadProcessId(handle, &id);
    return id;
}

void module_info(DWORD id, MODULEENTRY32 *module)
{
    HANDLE handle;

    handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, id);
    assert(handle != INVALID_HANDLE_VALUE);

    module->dwSize = sizeof(MODULEENTRY32);
    Module32First(handle, module);

    CloseHandle(handle);
}

HANDLE process_open(DWORD id)
{
    HANDLE handle;

    handle = OpenProcess(SYNCHRONIZE|PROCESS_VM_OPERATION|PROCESS_VM_READ|PROCESS_VM_WRITE, FALSE, id);
    assert(handle != NULL);

    return handle;
}

/* https://stackoverflow.com/a/1591371 */
BOOL process_alive(HANDLE handle)
{
    DWORD event;

    event = WaitForSingleObject(handle, 0);

    return event == WAIT_TIMEOUT;
}