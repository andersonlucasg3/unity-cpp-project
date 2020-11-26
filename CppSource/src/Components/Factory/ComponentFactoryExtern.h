#pragma once

class string;
struct intptr_t;

extern "C"
{
    intptr_t CreateCustomClassHandle(const string &clsName);
    void InvokeNativeAwake(intptr_t handle);
    void InvokeNativeStart(intptr_t handle);
}