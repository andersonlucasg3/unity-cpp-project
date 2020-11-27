#pragma once

typedef void (__stdcall *UnitySendMessageFunc)(const char *gameObjectName, const char *methodName, const char *message);

UnitySendMessageFunc UnitySendMessage = nullptr;

extern "C" {
    void SetUnitySendMessageMethod(UnitySendMessageFunc func);
}

void SetUnitySendMessageMethod(UnitySendMessageFunc func) {
    UnitySendMessage = func;
}
