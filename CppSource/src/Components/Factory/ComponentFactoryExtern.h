#pragma once

class string;
struct intptr_t;

extern "C"
{
    __decl  long long CreateCustomClassHandle(const char *clsName, const char *gameObjectName);
    void InvokeNativeAwake(intptr_t handle);
    void InvokeNativeStart(intptr_t handle);
}