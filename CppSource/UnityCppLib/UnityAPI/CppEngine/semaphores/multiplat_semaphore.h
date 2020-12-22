#pragma once

#if defined(__APPLE__) || defined(__MACH__)

#include <semaphore.h>

#else

#include "UnityAPI/NetFramework/System.h"

#define O_CREAT 1

using namespace System;

typedef int sem_t;

sem_t *sem_open(string_c name, int createMode);
void sem_close(sem_t *semaphore);
void sem_unlink(string_c semaphore);
void sem_wait(sem_t *semaphore);
void sem_post(sem_t *semaphore);


#endif