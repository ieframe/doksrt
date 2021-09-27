#include "win32.h"
#include "hash.h"
#include "game.h"
#include <stdio.h>
#include <assert.h>

int main(void)
{
    DWORD id;
    MODULEENTRY32 module;
    HANDLE process;

    uintptr_t game_static;
    int game_state;
    int game_restart;

    puts("Door Kickers Restart");
    puts("https://github.com/ieframe/doksrt\n");

    id = process_id("DoorKickers");
    printf("Process id: %ld\n", id);

    module_info(id, &module);
    printf("Base address: 0x%p\n", module.modBaseAddr);

    assert(djb2_file(module.szExePath) == DK_HASH);
    printf("Hash matches: 0x%x\n", DK_HASH);

    process = process_open(id);
    printf("Process handle: 0x%p\n", process);

    assert(ReadProcessMemory(process, module.modBaseAddr + DK_STATIC, &game_static, sizeof(uintptr_t), NULL));
    printf("Game struct address: 0x%x\n", game_static);

    game_restart = 4;

    while (process_alive(process)) {
        if (GetAsyncKeyState(0x52) & 0x01) {
            ReadProcessMemory(process, (uintptr_t *)(game_static + DK_OFFSET), &game_state, sizeof(int), NULL);
            if (game_state >= 4096)
                WriteProcessMemory(process, (uintptr_t *)(game_static + DK_OFFSET), &game_restart, sizeof(int), NULL);
        }
        Sleep(16);
    }

    return 0;
}