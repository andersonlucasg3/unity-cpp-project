#include "multiplat_semaphore.h"

#include <windows.h>

#define MAX_SEM_COUNT 10

sem_t *sem_open(string_c name, int) {
    return static_cast<sem_t *>(CreateSemaphore(nullptr, MAX_SEM_COUNT, MAX_SEM_COUNT, name));
}

void sem_close(sem_t *semaphore) {
    CloseHandle(semaphore);
}

void sem_unlink(string_c semaphore) {
    // placeholder only
}

void sem_wait(sem_t *semaphore) {
    WaitForSingleObject(semaphore, 0L);
}

void sem_post(sem_t *semaphore) {
    ReleaseSemaphore(semaphore, 1, nullptr);
}
